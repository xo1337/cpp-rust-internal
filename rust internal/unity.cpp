#include "modules.hpp"

namespace unity 
{
	namespace camera 
	{
		void* get_main()
		{
			return call<void*>(offsets::camera_get_main);
		}

		bool get_matrix(matrix4x4* output)
		{
			void* camera_ptr = get_main();
			if (!camera_ptr) return false;

			auto camera_unk1 = *(uint64_t*)((uint64_t)camera_ptr + 0x10);
			if (!camera_unk1) return false;

			*output = *(matrix4x4*)(camera_unk1 + offsets::camera_matrix);
			return true;
		}

		void get_position_Injected(void* _this, vector3* retval)
		{
			void(*do_get_pos)(void*, vector3*);

			do_get_pos = (decltype(do_get_pos))(base::game_assembly + offsets::camera_fn);
			if (!addr::valid(do_get_pos))
				return;

			do_get_pos(_this, retval);
		}
	}

	bool world_to_screen(vector3 location, ImVec2& return_value)
	{
		if (location.x == 0 && location.y == 0 && location.z == 0)
			return false;

		matrix4x4 view_matrix;
		if (!camera::get_matrix(&view_matrix))
			return false;

		vector3 trans_vec{ view_matrix._14, view_matrix._24, view_matrix._34 };
		vector3 right_vec{ view_matrix._11, view_matrix._21, view_matrix._31 };
		vector3 up_vec{ view_matrix._12, view_matrix._22, view_matrix._32 };

		float w = vector3::dot(trans_vec, location) + view_matrix._44;
		if (w < 0.098f) return false;

		float y = vector3::dot(up_vec, location) + view_matrix._42;
		float x = vector3::dot(right_vec, location) + view_matrix._41;

		float result_x = (base::winapi::window_size_x / 2) * (1.f + x / w);
		float result_y = (base::winapi::window_size_y / 2) * (1.f - y / w);

		if (result_x < 0 || result_x > base::winapi::window_size_x ||
			result_y < 0 || result_y > base::winapi::window_size_y)
			return false;

		return_value = ImVec2(result_x, result_y);
		return true;
	}

	bool get_bone_3d(BasePlayer_o* player, uint32_t id, vector3& output)
	{
		if (!addr::valid(player))
			return false;

		Model_o* model = player->fields.model;
		if (!addr::valid(model))
			return false;

		UnityEngine_Transform_array* transforms = model->fields.boneTransforms;
		if (!addr::valid(transforms))
			return false;

		auto transform = transforms->m_Items[id];
		if (!addr::valid(transform))
			return false;

		camera::get_position_Injected(transform, &output);

		return true;
	}

	bool get_bone(BasePlayer_o* player, uint32_t id, ImVec2& output)
	{
		vector3 location;
		if (!get_bone_3d(player, id, location))
			return false;

		return world_to_screen(location, output);
	}
}