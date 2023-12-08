#pragma once
#include "syscaller.hpp"

namespace base
{
	namespace aimbot
	{
		inline bool enabled = false;
		inline bool visible_check = false;

		inline bool crosshair = false;
		inline float crosshair_color[4] = { 1, 1, 1, 1 };
		inline float crosshair_size = 6.5;

		inline bool radius = false;
		inline bool filled_radius = false;
		inline float radius_size = 150;
		inline float radius_color[4] = { 1, 1, 1, 1 };
		inline bool closest_bone = false;

		inline float smoothing = 20.0f;
		inline int key_bind = VK_XBUTTON2;

		inline int selected_bone = 0;
		inline int bone = 47; // head, neck, chest
	
	}

	namespace esp
	{
		inline bool enabled = true;

		inline bool boxes = false;
		inline bool boxes_filled = false;
		inline bool boxes_3d = false;
		inline float boxes_color[4] = { 1, 0, 0, 1 };

		inline bool corners = false;
		inline float corners_color[4] = { 1, 0,0, 1 };

		inline bool snaplines = false;
		inline float snaplines_color[4] = { 1, 1, 1, 1 };

		inline bool skeleton = true;
		inline float skeleton_color[4] = { 1, 1, 1, 1 };

		inline bool distance = true;
		inline float distance_color[4] = { 1, 1, 1, 1 };

		inline bool names = true;
		inline float names_color[4] = { 1, 1, 1, 1 };

		inline bool items = false;
		inline float items_color[4] = { 1, 1, 1, 1 };

		inline bool health_bar = true;
		inline bool visible_colors = false;

		inline bool weapon_name = true;
		inline float weapon_name_color[4] = { 1, 1, 0, 1 };

		inline float max_dist = 100.0f;
	}

	namespace misc
	{
		inline float fov = 110;
		
		inline float zoom_amount = 25;
		inline bool zoom = true;

		inline bool team_check = false;
		inline bool fake_admin = false;
		inline bool spiderman = true;
		inline bool infinite_jump = true;
		inline bool fat_bullet = false;
		inline bool spinbot = false;
	}

	namespace fonts
	{
		inline ImFont* courbd = nullptr;
	}
}