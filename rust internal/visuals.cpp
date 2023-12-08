#include "modules.hpp"

namespace modules
{
	void visuals(ImDrawList* draw_list, const ImVec2& size) 
	{
		vector3 local_player_location =
		{
			sdk::local_player->fields.playerModel->fields.position.fields.x,
			sdk::local_player->fields.playerModel->fields.position.fields.y,
			sdk::local_player->fields.playerModel->fields.position.fields.z
		};

		vector3 local_player_head_position;
		if (!unity::get_bone_3d(sdk::local_player, unity::bone_id::head, local_player_head_position))
			return;

		float best_aimbot_distance = base::aimbot::radius_size;
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

			int distance = (vector3::distance(local_player_location, object_location));
			if (distance > base::esp::max_dist)
				continue;

			std::string name = unity::convert_from_string(player->fields._displayName);
			char buffer[128];

			ImVec2 player_head;
			if (!unity::get_bone(player, unity::bone_id::head, player_head))
				continue;

			ImVec2 player_neck;
			if (!unity::get_bone(player, unity::bone_id::neck, player_neck))
				continue;

			ImVec2 player_root;
			if (!unity::world_to_screen(object_location, player_root))
				continue;

			float top = player_head.y;
			float bottom = player_root.y;
			float height = base::memory::_fabs(top - bottom) * 1.4f;
			float width = height / 2.f;
			float left = player_root.x - width / 2.f;
			float right = player_root.x + width / 2.f;

			/**
			bool (*line_of_sight)(vector3, vector3, int layerMask, __int64);
			line_of_sight = (decltype(line_of_sight))(base::game_assembly + 0x6A4240);

			const int ProjectileLineOfSightCheck = 2162688;
			const int Terrain = 8388608;

			int layers = static_cast<int>(ProjectileLineOfSightCheck|Terrain);

			//bool visible = line_of_sight(local_player_location, object_location, layers, 0);
			*/

			ImColor visible_color = ImColor(255, 0, 0); 

			if (base::aimbot::enabled)
			{
				if (GetAsyncKeyState(base::aimbot::key_bind) & 0x8000)
				{
					auto target = ImVec2{ player_head.x, player_head.y };
					auto distance = base::distance_2d(size.x / 2, size.y / 2, target.x, target.y);

					if (base::in_fov(size.x/2, size.y/2, base::aimbot::radius_size, target.x, target.y) 
						&& distance < best_aimbot_distance)
					{
						best_aimbot_distance = distance;
						draw_list->AddLine(ImVec2{ size.x / 2, size.y / 2 }, target, ImColor(255, 255, 0), 2.0f);

						vector3 player_positon;
						if (unity::get_bone_3d(player, unity::bone_id::head, player_positon))
						{
							vector2 my_angles{ sdk::local_player->fields.input->fields.bodyAngles.fields.x, sdk::local_player->fields.input->fields.bodyAngles.fields.y };
							vector2 offset = base::calc_angles(local_player_head_position, player_positon) - my_angles;


							base::normalize_angles(offset.y, offset.x);
							offset /= (base::aimbot::smoothing <= 0 ? 1 : base::aimbot::smoothing);

							vector2 final_angle = my_angles + offset;
							base::normalize_angles(final_angle.y, final_angle.x);


							sdk::local_player->fields.input->fields.bodyAngles.fields.x = final_angle.x;
							sdk::local_player->fields.input->fields.bodyAngles.fields.y = final_angle.y;
						}
					}
				}
			}

			if (base::esp::enabled)
			{
				if (base::esp::boxes)
				{
					base::draw_outlined_rect(draw_list, { left, bottom }, { right, bottom - height }, base::esp::visible_colors ? visible_color : base::convert_color(base::esp::boxes_color));
				}

				if (base::esp::boxes_filled)
				{
					draw_list->AddRectFilled({ left, bottom }, { right, bottom - height }, ImColor(0, 0, 0, 100));
				}

				if (base::esp::corners)
				{
					base::draw_corner_box(draw_list, { right, bottom }, { width, height }, base::esp::visible_colors ? visible_color : base::convert_color(base::esp::corners_color), 1);
				}

				if (base::esp::snaplines)
				{
					draw_list->AddLine({ (size.x / 2), size.y }, { player_root.x, player_root.y }, base::esp::visible_colors ? visible_color : base::convert_color(base::esp::snaplines_color));
				}

				if (base::esp::skeleton)
				{
					auto color = base::esp::visible_colors ? visible_color : base::convert_color(base::esp::skeleton_color);

					static std::vector<std::pair<uint32_t, uint32_t>> bones
					{
						{ unity::bone_id::head, unity::bone_id::neck },
						{ unity::bone_id::neck, unity::bone_id::l_upperarm },
						{ unity::bone_id::neck, unity::bone_id::r_upperarm },
						{ unity::bone_id::l_upperarm, unity::bone_id::l_forearm },
						{ unity::bone_id::r_upperarm, unity::bone_id::r_forearm },
						{ unity::bone_id::l_forearm, unity::bone_id::l_hand },
						{ unity::bone_id::r_forearm, unity::bone_id::r_hand },
						{ unity::bone_id::neck, unity::bone_id::spine1 },
						{ unity::bone_id::spine1, unity::bone_id::l_hip },
						{ unity::bone_id::spine1, unity::bone_id::r_hip },
						{ unity::bone_id::l_hip, unity::bone_id::l_knee },
						{ unity::bone_id::r_hip, unity::bone_id::r_knee },
						{ unity::bone_id::l_knee, 5 },
						{ unity::bone_id::r_ankle_scale, unity::bone_id::r_toe },
						{ unity::bone_id::r_knee, unity::bone_id::r_ankle_scale },
						{ 5, 4 }
					};

					for (auto& bone : bones)
					{
						ImVec2 first;
						if (!unity::get_bone(player, bone.first, first)) continue;

						ImVec2 second;
						if (!unity::get_bone(player, bone.second, second)) continue;

						draw_list->AddLine(first, second, color);
					}
				}

				if (base::esp::distance && !base::esp::names)
				{
					sprintf_s(buffer, xorstr_("%im"), (int)distance);
					base::draw_text(base::fonts::courbd, player_root.x - (ImGui::CalcTextSize(buffer).x / 2), bottom + 3.5f, base::esp::visible_colors ? visible_color : ImColor(255, 255, 255), buffer);
				}

				if (!base::esp::distance && base::esp::names)
				{
					sprintf_s(buffer, xorstr_("%s"), name.c_str());
					base::draw_text(base::fonts::courbd, player_root.x - (ImGui::CalcTextSize(buffer).x / 2), bottom + 3.5f, base::esp::visible_colors ? visible_color : ImColor(255, 255, 255), buffer);
				}

				if (base::esp::distance && base::esp::names)
				{
					sprintf_s(buffer, xorstr_("%s %im"), name.c_str(), (int)distance);
					base::draw_text(base::fonts::courbd, player_root.x - (ImGui::CalcTextSize(buffer).x / 2), bottom + 3.5f, base::esp::visible_colors ? visible_color : ImColor(255, 255, 255), buffer);
				}

				if (base::esp::weapon_name)
				{
					auto item = sdk::get_current_item(player);
					if (addr::valid(item)) {

						auto item_name = unity::convert_from_string(item->fields.info->fields.displayName->fields.english);
						if (item_name.empty())
							item_name = xorstr_("None");

						sprintf_s(buffer, xorstr_("%s"), item_name.c_str());
						base::draw_text(base::fonts::courbd, player_root.x - (ImGui::CalcTextSize(buffer).x / 2), bottom + 16.5f, base::esp::visible_colors ? visible_color : base::convert_color(base::esp::weapon_name_color), buffer);
					}
				}

				if (base::esp::health_bar)
				{
					float health_height = (height * (player->fields._health / 100.0f));
					int r = 255 - player->fields._health * 2.55;
					int g = player->fields._health * 2.55;

					draw_list->AddRect({ (left - 7), bottom }, ImVec2((left - 5), bottom - health_height), ImColor(0, 0, 0, 255), 0, 0, 2.5f);
					draw_list->AddRect({ (left - 6), bottom }, ImVec2((left - 6), bottom - health_height), ImColor(r, g, 0, 255), 0, 0, 1.5f);
				}
			}
		}
	}
}