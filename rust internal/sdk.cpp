#include "modules.hpp"

namespace sdk
{
	BasePlayer_o* get_local_player()
	{
		auto local = unity::get_fields<LocalPlayer_c>(offsets::local_player);
		if (!addr::valid((uint64_t)local))
			return nullptr;

		if (!addr::valid((uint64_t)local->static_fields))
			return nullptr;

		if (!addr::valid((uint64_t)local->static_fields->_Entity_k__BackingField))
			return nullptr;

		return local->static_fields->_Entity_k__BackingField;
	}

	std::pair<uint64_t, uint32_t> get_entity_list()
	{
		uint64_t base_entity = *(uint64_t*)(base::game_assembly + offsets::entity_list);
		if (!addr::valid(base_entity)) return {};

		auto unk1 = *(uintptr_t*)(base_entity + 0xb8);
		if (!addr::valid(unk1)) return {};

		unk1 = *(uint64_t*)(unk1 + 0x10);
		if (!addr::valid(unk1)) return {};

		auto client_entities = *(uintptr_t*)(*(uintptr_t*)(unk1 + 0x10) + 0x28);
		if (!addr::valid(client_entities)) return {};

		auto object_list = *(uintptr_t*)(client_entities + 0x18);
		if (!addr::valid(object_list)) return {};

		auto object_list_size = *(uint32_t*)(client_entities + 0x10);
		if (object_list_size <= 0) return {};

		return { object_list, object_list_size };
	}

	Item_o* get_current_item(BasePlayer_o* player)
	{
		if (!addr::valid(player))
			return nullptr;

		uint32_t active_id = player->fields.clActiveItem.fields.Value;
		if (!active_id) 
			return nullptr;

		auto list = player->fields.inventory->fields.containerBelt->fields.itemList;
		if (!addr::valid(list)) 
			return nullptr;

		uint32_t index = 0;
		for (uint32_t i = 0; i < 6; i++)
		{
			auto item = list->fields._items->m_Items[i];
			if (!addr::valid(item))
				continue;

			if (active_id == item->fields.uid.fields.Value)
			{
				index = i;
				break;
			}
		}

		auto item = list->fields._items->m_Items[index];
		if (!addr::valid(item))
			return nullptr;

		return item;
	}

	vector2 get_best_aim_angles(unity::bone_id bone_id)
	{
		vector2 angles{ -1, -1 };
		vector3 local_player_head_position;

		if (!unity::get_bone_3d(sdk::local_player, unity::bone_id::head, local_player_head_position))
			return {-1, -1};

		float best_aimbot_distance = base::aimbot::radius_size;
		std::vector<std::pair<BasePlayer_o*, ImVec2>> results;

		for (uint32_t i = 0; i < sdk::entity_list.second; i++)
		{
			auto current_object_ptr = *(uint64_t*)(sdk::entity_list.first + (0x20 + (i * 8)));
			if (!current_object_ptr) continue;

			auto base_object = *(uint64_t*)(current_object_ptr + 0x10);
			if (!base_object) continue;

			auto object = *(uint64_t*)(base_object + 0x30);
			if (!object) continue;

			auto tag = *(WORD*)(object + 0x54);
			if (!tag || tag != 6) continue;

			auto object_class = *(uint64_t*)(object + 0x30);
			if (!object_class) continue;

			auto entity = *(uint64_t*)(object_class + 0x18);
			if (!entity) continue;

			auto transform = *(uint64_t*)(object_class + 0x8);
			if (!transform) continue;

			auto visual_state = *(uint64_t*)(transform + 0x38);
			if (!visual_state) continue;

			vector3 object_location = *(vector3*)(visual_state + 0x90);

			BasePlayer_o* player = (BasePlayer_o*)(*(uint64_t*)(entity + 0x28));
			if (!addr::valid(player) || player == sdk::local_player) continue;

			if (!player->fields.playerModel)
				continue;

			if (player->fields._health <= 0)
				continue;

			if (base::misc::team_check && player->fields.currentTeam == sdk::local_player->fields.currentTeam)
				continue;

			ImVec2 player_location;
			if (!unity::get_bone(player, bone_id, player_location))
				continue;

			results.push_back({ player , player_location });
		}

		std::vector<std::pair<BasePlayer_o*, float>> distances;
		vector2 center((float)base::winapi::window_size_x / 2, (float)base::winapi::window_size_y/2);

		for (int i = 0; i < results.size(); i++)
		{
			const auto& it = results[i];
			float distance = abs(vector2::distance(center, vector2(it.second.x, it.second.y)));

			if (!(distance < FLT_MAX &&
				distance <= base::aimbot::radius_size)) 
				continue;

			distances.push_back({ results[i].first, distance });
		}

		float lowest = distances[0].second;
		int index = 0;

		for (int i = 0; i < distances.size(); i++) {
			if (lowest > distances[i].second) {
				lowest = distances[i].second;
				index = i;
			}
		}

		if (!(index >= 0 && index < distances.size()))
			return { -1, -1 };

		BasePlayer_o* player = distances[index].first;
		if (!addr::valid(player))
			return { -1, -1 };

		vector3 player_positon;
		if (!unity::get_bone_3d(player, bone_id, player_positon))
			return { -1, -1 };

		vector2 my_angles{ sdk::local_player->fields.input->fields.bodyAngles.fields.x, sdk::local_player->fields.input->fields.bodyAngles.fields.y };
		vector2 offset = base::calc_angles(local_player_head_position, player_positon) - my_angles;

		base::normalize_angles(offset.y, offset.x);
		offset /= (base::aimbot::smoothing <= 1 ? 1 : base::aimbot::smoothing);

		vector2 final_angle = my_angles + offset;
		base::normalize_angles(final_angle.y, final_angle.x);

		return final_angle;
	}
}