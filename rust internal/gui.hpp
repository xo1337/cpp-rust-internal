#pragma once
#include "macros.hpp"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

namespace base
{
	namespace gui
	{
		typedef HWND d3d11_window_t;
		typedef WNDPROC d3d11_wndproc_t;
		typedef ID3D11Device* d3d11_device_t;
		typedef ID3D11DeviceContext* d3d11_device_context_t;
		typedef ID3D11RenderTargetView* d3d11_render_target_view_t;

		inline uint32_t tab = 0;
		inline bool open = false;
		inline bool unload = false;
		inline bool pointers_initialized = false;
		inline IDXGISwapChain* d3d11_swap_chain{};
		inline d3d11_window_t d3d11_window{};
		inline d3d11_wndproc_t d3d11_wndproc{};
		inline d3d11_device_t d3d11_device{};
		inline d3d11_device_context_t d3d11_device_context{};
		inline d3d11_render_target_view_t d3d11_render_target_view{};
		inline char* d3d11_unk1;
		inline uint64_t* d3d11_vtable;
		inline uint64_t hooked_vtable[4096];
		inline uint64_t dxgi_base;
		inline PIMAGE_NT_HEADERS dxgi_nt_headers;
		inline uint64_t dxgi_size;
		inline void(__fastcall* d3d11_detour_original)(void*);

		inline LRESULT __stdcall message_handler(HWND m_hwnd, UINT m_msg, WPARAM m_wparam, LPARAM m_lparam)
		{
			switch (m_msg)
			{
			case WM_KEYUP:
				switch (m_wparam)
				{
				case VK_DELETE:
					gui::open ^= 1;
					break;

				case VK_END:
					#if UNLOAD_CHEAT
						gui::unload = true;
					#endif
					break;
				}
				break;
			}

			if (open && !unload)
			{
				ImGui_ImplWin32_WndProcHandler(m_hwnd, m_msg, m_wparam, m_lparam);
				return TRUE;
			}

			static auto fnCallWindowProcA = reinterpret_cast<HRESULT(__stdcall*)(WNDPROC, HWND, UINT, WPARAM, LPARAM)>(0);
			if (!fnCallWindowProcA) {
				*(uintptr_t*)&fnCallWindowProcA = memory::get_export(xorstr_("user32.dll"), xorstr_("CallWindowProcA"));
			}

			return fnCallWindowProcA(d3d11_wndproc, m_hwnd, m_msg, m_wparam, m_lparam);
		}

		struct hover
		{
			std::string str;
			float tick;
			int index;
		};

		inline void hover_button(const int new_tab, const std::string& szIcon, const std::string& szLabel, std::string& text_to_display, float& tick, int& index, float y_padding = 0)
		{
			const int& length = szLabel.length();
			const ImVec2& text_size = ImGui::CalcTextSize(text_to_display.c_str());

			ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (text_size.x / 2));
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + y_padding);
			ImGui::TextColored((gui::tab == new_tab ? ImColor(255, 255, 255, 255) : ImColor(255, 255, 255, 50)), text_to_display.c_str());

			if (ImGui::IsItemClicked())
			{
				gui::tab = new_tab;
			}

			// if hovered, do the glow effect...
			if (ImGui::IsItemHovered())
			{
				// text_to_display != szLabel
				if (text_to_display.compare(szLabel))
				{
					text_to_display.resize(length);

					if (!(tick >= 15))
					{
						// don't change this :)
						tick += 1;
					}

					if (tick >= 15)
					{
						// change the characters via their index 
						text_to_display[index] = szLabel[index];

						if (index != length)
						{
							index++;
						}

						tick -= 3; // 3 = animation speed
					}
				}
			}
			else
			{
				// reset the data..
				tick = 0;
				index = 0;
				text_to_display = szIcon;
			}

			ImGui::NewLine();
		};
	}
}