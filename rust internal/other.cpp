#include "modules.hpp"

namespace modules 
{
	using namespace base;

	void fov_changer()
	{
		auto convar = unity::get_fields<ConVar_Graphics_c>(offsets::convar_graphics);
		if (!addr::valid(convar))
			return;


		if (misc::zoom && GetAsyncKeyState('X') & 0x8000)
			convar->static_fields->_fov = misc::zoom_amount;
		else
			convar->static_fields->_fov = misc::fov;
	}

	void fake_admin(bool enabled)
	{
		int flag = 4;

		int32_t flags = sdk::local_player->fields.playerFlags;
		flags = (enabled ? (flags | flag) : (flags & (~flag)));

		sdk::local_player->fields.playerFlags = flags;
	}

	void spiderman()
	{
		PlayerWalkMovement_o* movement = (PlayerWalkMovement_o*)sdk::local_player->fields.movement;
		if (!addr::valid(movement))
			return;

		movement->fields.groundAngle = 0;
		movement->fields.groundAngleNew = 0;
	}

	void infinite_jump()
	{
		PlayerWalkMovement_o* movement = (PlayerWalkMovement_o*)sdk::local_player->fields.movement;
		if (!addr::valid(movement))
			return;

		movement->fields.landTime = 0;
		movement->fields.jumpTime = 0;
		movement->fields.groundTime = 100000;
	}

	void fat_bullet()
	{
		if (!addr::valid(sdk::local_player))
			return;

		Item_o* current_item = sdk::get_current_item(sdk::local_player);
		if (!addr::valid(current_item))
			return;


		if (!addr::valid(current_item->fields.heldEntity.fields.ent_cached))
			return;

		// HeldEntity : BaseEntity

		// AttackEntity : HeldEntity

		// BaseProjectile : AttackEntity

		// BaseProjectile.createdprojectiles

		BaseProjectile_o* projectile = (BaseProjectile_o*)current_item->fields.heldEntity.fields.ent_cached;
		for (int i = 0; i < 8; i++)
		{
			auto item = projectile->fields.createdProjectiles->fields._items->m_Items[i];
			if (!addr::valid(item))
				continue;

			item->fields.thickness = 1.5f;
		}

		//current_item->fields.heldEntity.fields.ent_cached->fields.

		/*
		auto List = Read<DWORD64>(this->bp + O::createdprojectiles); //private List<Projectile> createdProjectiles;
		List = Read<DWORD64>(List + 0x10);
		for (int i = 0; i < 8; ++i)
		{
			UINT64 Item = Read<UINT64>(List + 0x20 + (i * 0x8));
			Write<float>(Item + 0x2C, 1.5f);
		}
		*/
	}

	void other(ImDrawList* draw_list, const ImVec2& size) 
	{	
		fov_changer();

		fake_admin(misc::fake_admin);

		if (misc::spiderman)
			spiderman();

		if (misc::infinite_jump)
			infinite_jump();

		if (misc::fat_bullet)
			fat_bullet();

		if (misc::spinbot && GetAsyncKeyState('C') & 0x8000) 
		{
			vector3 vector(100, rand() % 999 + -999, 100);
			sdk::local_player->fields.input->fields.bodyAngles.fields.x = vector.x;
			sdk::local_player->fields.input->fields.bodyAngles.fields.y = vector.y;
			sdk::local_player->fields.input->fields.bodyAngles.fields.z = vector.z;
		}
	}
}