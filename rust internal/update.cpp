#include "modules.hpp"

namespace modules 
{
	bool update() 
	{
		if (!base::game_assembly ||
			!base::unity_player)
			return false;

		sdk::local_player = sdk::get_local_player();
		if (!addr::valid((uint64_t)sdk::local_player))
			return false;

		if (!sdk::local_player->fields.playerModel)
			return false;

		sdk::entity_list = sdk::get_entity_list();
		if (!addr::valid(sdk::entity_list.first) || sdk::entity_list.second <= 0)
			return false;

		return true;
	}
}