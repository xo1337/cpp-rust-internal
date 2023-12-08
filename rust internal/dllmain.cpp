#include "includes.hpp"
#include "d3d11.hpp"
#include "modules.hpp"

namespace base 
{ 
	inline void on_init()
	{
		constexpr bool allocate_console = true;

		if (allocate_console)
		{
			memory::call(xorstr_("kernel32.dll"), xorstr_("AllocConsole"));
			freopen_s((FILE**)stdout, xorstr_("CONOUT$"), xorstr_("w"), stdout);
		}

		if (!winapi::initialize())
		{
			memory::popup(xorstr_("Failed creating API context."));
			return;
		}

		if (!d3d::initialize())
		{
			memory::popup(xorstr_("Failed creating D3D context."));
			return;
		}
		
		d3d11::on_frame = [](ImDrawList* draw, const ImVec2& size, const ImVec2& center)
		{
			if (aimbot::crosshair)
			{
				auto center = ImVec2(size.x / 2, size.y / 2);
				auto main = ImColor(aimbot::crosshair_color[0], aimbot::crosshair_color[1], aimbot::crosshair_color[2], aimbot::crosshair_color[3]);

				draw->AddLine(center, { center.x - aimbot::crosshair_size, center.y }, main, 2.0f);
				draw->AddLine(center, { center.x + aimbot::crosshair_size, center.y }, main, 2.0f);

				draw->AddLine(center, { center.x, center.y - aimbot::crosshair_size }, main, 2.0f);
				draw->AddLine(center, { center.x, center.y + aimbot::crosshair_size }, main, 2.0f);
			}

			if (aimbot::radius)
				draw->AddCircle({ size.x / 2, size.y / 2 }, aimbot::radius_size, ImColor(aimbot::radius_color[0], aimbot::radius_color[1], aimbot::radius_color[2], aimbot::radius_color[3]), 100, 2.0f);


			// global vars update local plr, ent list, etc
			if (!modules::update())
				return;

			// esp+aim
			modules::visuals(draw, size);
			// misc
			modules::other(draw, size);
		};

		game_assembly = memory::get_module(xorstr_("GameAssembly.dll"));
		unity_player = memory::get_module(xorstr_("UnityPlayer.dll"));

		const auto get_swap_chain = [&]()->const uint64_t
		{
			const auto offset = memory::pattern(xorstr_("UnityPlayer.dll"), xorstr_("48 8B 05 ? ? ? ? 80 B8 ? ? ? ? ? 75 ? 48 8B CB")).rva(3).add(7).sub(-1).get();

			return *reinterpret_cast<uint64_t*>(
				*reinterpret_cast<uint64_t*>(
					unity_player + /*0x1B38A38*/offset
				) + 0x320
			);
		};

		IDXGISwapChain* swap_chain = (IDXGISwapChain*)get_swap_chain();
		if (!swap_chain) return;

		winapi::window_size_x = *((DWORD*)swap_chain + 0x48);
		winapi::window_size_y = *((DWORD*)swap_chain + 0x49);

		if (!d3d11::init(swap_chain))
		{
			memory::popup(xorstr_("User interface will not be available."));
			return;
		}
	}
} 

__declspec(dllexport)
auto DllMain( void*, std::uint32_t reason, void* )->bool
{
	if (reason != DLL_PROCESS_ATTACH)
		return FALSE;

	base::on_init();
	return TRUE;
}

