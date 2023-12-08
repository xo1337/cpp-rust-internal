#pragma once

namespace offsets 
{
	// LocalPlayer_TypeInfo
	inline constexpr auto local_player = 53923288;
	// 48 8B 05 ? ? ? ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 00 48 83 C4 ? C3 CC CC 48 83 EC ? 80 3D ? ? ? ? ? 0F 29 74 24 ? 0F 28 F0 0F 29 7C 24 ? 0F 28 F9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? F3 0F 10 05

	// System_Collections_Generic_List_BaseGameMode__c*
	inline constexpr auto entity_list = 53752584;
	// 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 8B 88 ? ? ? ? 48 C7 41 ? ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 83 C1 ? E8 ? ? ? ? 48 8B 0D

	// UnityEngine.Camera$$get_main
	inline constexpr auto camera_get_main = 41944800;
	// 48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 83 C4 ? 48 FF E0 CC CC CC CC CC CC 40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B CB 48 83 C4 ? 5B 48 FF E0 CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B DA 48 8B F9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B D3 48 8B CF 48 8B 5C 24 ? 48 83 C4 ? 5F 48 FF E0 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57

	inline constexpr auto camera_matrix = 0x2e4; // you wont need to change this, since it literally hasn't changed for some time...

	// UnityEngine.Transform.get_position_Injected
	inline constexpr auto camera_fn = 0x2854D10;
	// 48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B DA 48 8B F9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B D3 48 8B CF 48 8B 5C 24 ? 48 83 C4 ? 5F 48 FF E0 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 33 C0 48 8B FA 48 89 01 48 8B D9 89 41 ? 48 8B 05 ? ? ? ? 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8B D3 48 8B CF FF D0 48 8B C3 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 33 C0
	
	// Graphics_TypeInfo
	inline constexpr auto convar_graphics = 53743944;
	// 48 8B 0D ? ? ? ? 48 8B 7B ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 33 C9 E8 ? ? ? ? 48 85 FF 0F 84 ? ? ? ? 85 C0
}