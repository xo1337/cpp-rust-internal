#include "d3d11.hpp"

namespace base
{
	namespace d3d11
	{
		__forceinline bool on_present(IDXGISwapChain* swap_chain)
		{
			if (!gui::pointers_initialized)
			{
				if (SUCCEEDED(d3d::get_device(swap_chain, __uuidof(ID3D11Device), (PVOID*)&gui::d3d11_device)))
				{
					SAFE_CALL(d3d::get_immediate_context, gui::d3d11_device, &gui::d3d11_device_context);
					gui::d3d11_window = SAFE_CALL(d3d::get_hwnd, swap_chain);
					ID3D11Texture2D* back_buffer = nullptr;

					SAFE_CALL(d3d::get_buffer, swap_chain, 0, __uuidof(ID3D11Texture2D), (PVOID*)&back_buffer);
					SAFE_CALL(d3d::create_render_target_view, gui::d3d11_device, back_buffer, nullptr, &gui::d3d11_render_target_view);
					SAFE_CALL(d3d::release, back_buffer);

					gui::d3d11_wndproc = SAFE_CALL(winapi::fnSetWindowLongPtrA, gui::d3d11_window, GWLP_WNDPROC, (LONG_PTR)gui::message_handler);


					SAFE_CALL(ImGui::CreateContext, nullptr);
	
					base::d3d11::on_style();

					SAFE_CALL(ImGui_ImplWin32_Init, gui::d3d11_window);
			
					SAFE_CALL(ImGui_ImplDX11_Init, gui::d3d11_device, gui::d3d11_device_context);

					gui::pointers_initialized = true;
				}
				else { return false; }
			}

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ImGui::GetIO().MouseDrawCursor = gui::open;
			ImGui::GetIO().WantCaptureMouse = gui::open;

			if (gui::unload)
			{
				gui::hooked_vtable[3] = (uint64_t)gui::d3d11_detour_original;
				(**((PVOID**)gui::d3d11_unk1 + 1)) = gui::hooked_vtable;
			}

			if (gui::open)
				base::d3d11::on_gui();

			base::d3d11::on_frame(ImGui::GetBackgroundDrawList(), ImGui::GetIO().DisplaySize, ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2));

			ImGui::EndFrame();

			gui::d3d11_device_context->OMSetRenderTargets(1, &gui::d3d11_render_target_view, 0);
			ImGui::Render();

			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
			return true;
		}

		__forceinline void on_style()
		{
			auto& io = ImGui::GetIO();
			auto& style = ImGui::GetStyle();

			io.LogFilename = nullptr;
			io.IniFilename = nullptr;

			static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
			ImFontConfig icons_config;

			icons_config.MergeMode = true;
			icons_config.PixelSnapH = true;
			icons_config.OversampleH = 3;
			icons_config.OversampleV = 3;

			ImFontConfig m_rubik_font;
			m_rubik_font.FontDataOwnedByAtlas = false;

			ImFontConfig m_courbd_font;
			m_courbd_font.FontDataOwnedByAtlas = false;

			for (std::uint32_t i = 0; i < sizeof(rubik_font_data); i++)
				rubik_font_data[i] ^= (-0xf1);
			io.Fonts->AddFontFromMemoryTTF(const_cast<unsigned char*>(rubik_font_data), sizeof(rubik_font_data), 15.5, &m_rubik_font);
			io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 16.5f, &icons_config, icons_ranges);

			for (std::uint32_t i = 0; i < sizeof(courbd_font_data); i++)
				courbd_font_data[i] ^= (-0xf1);
			fonts::courbd = io.Fonts->AddFontFromMemoryTTF(const_cast<unsigned char*>(courbd_font_data), sizeof(courbd_font_data), 14.5f, &m_courbd_font);

			style.WindowMinSize = ImVec2(400, 100);
			style.FrameBorderSize = 0;
			style.WindowRounding = 0;
			style.WindowPadding = ImVec2(16, 16);
			style.TabRounding = 0;
			style.ScrollbarRounding = 0;
			style.FramePadding = ImVec2(4, 4);
			style.FrameRounding = 0;
			style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
			style.Colors[ImGuiCol_TitleBg] = ImColor(227, 0, 40, 255);
			style.Colors[ImGuiCol_TitleBgActive] = ImColor(227, 0, 40, 255);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(15, 15, 15, 50);
			style.Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
			style.Colors[ImGuiCol_WindowBg] = ImColor(14, 14, 14, 255);
			style.Colors[ImGuiCol_Button] = ImColor(24, 25, 24, 255);
			style.Colors[ImGuiCol_ButtonActive] = ImColor(44, 44, 44, 255);
			style.Colors[ImGuiCol_ButtonHovered] = ImColor(44, 44, 44, 255);
			style.Colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255, 255);
			style.Colors[ImGuiCol_FrameBg] = ImColor(36, 37, 36, 255);
			style.Colors[ImGuiCol_FrameBgActive] = ImColor(36, 37, 36, 255);
			style.Colors[ImGuiCol_FrameBgHovered] = ImColor(36, 37, 36, 255);

			style.Colors[ImGuiCol_Header] = ImColor(23, 23, 23, 255);
			style.Colors[ImGuiCol_HeaderActive] = ImColor(26, 26, 26, 255);
			style.Colors[ImGuiCol_HeaderHovered] = ImColor(26, 26, 26, 255);

			style.Colors[ImGuiCol_ResizeGrip] = ImColor(51, 49, 50, 0);
			style.Colors[ImGuiCol_ResizeGripActive] = ImColor(54, 53, 55, 0);
			style.Colors[ImGuiCol_ResizeGripHovered] = ImColor(51, 49, 50, 0);
			style.Colors[ImGuiCol_SliderGrab] = ImColor(59, 59, 59);
			style.Colors[ImGuiCol_SliderGrabActive] = ImColor(59, 59, 59);
			style.Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 255);
			style.Colors[ImGuiCol_Separator] = ImColor(54, 54, 54);
			style.Colors[ImGuiCol_SeparatorActive] = ImColor(54, 54, 54);
			style.Colors[ImGuiCol_SeparatorHovered] = ImColor(54, 54, 54);
		}

		__forceinline void on_gui()
		{
			
			const auto checkbox_picker = [](const char* label, bool* value, float* color, bool space = false)
			{
				ImGui::PushID(label);
				ImGui::ColorEdit4(xorstr_("##checkbox_picker_"), color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip);
				ImGui::PopID();

				ImGui::SameLine();

				ImGui::Checkbox(label, value);
				if (space)
					ImGui::Spacing();
			};

			const auto slider_float = [](const char* label, float* value, float _min, float _max, float width = ImGui::GetContentRegionAvail().x)->void
			{
				ImGui::PushID(label);
				ImGui::PushItemWidth(width);
				ImGui::SliderFloat(xorstr_("##sliderfloat_"), value, _min, _max, label);
				ImGui::PopItemWidth();
				ImGui::PopID();
			};

			const auto slider_int = [](const char* label, int* value, int _min, int _max, float width = ImGui::GetContentRegionAvail().x)->void
			{
				ImGui::PushID(label);
				ImGui::PushItemWidth(width);
				ImGui::SliderInt(xorstr_("##sliderint_"), value, _min, _max, label);
				ImGui::PopItemWidth();
				ImGui::PopID();
			};

			ImGui::Begin(xorstr_("##khgjsdfkjshdfsdfsdf"), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);

			ImVec2 position{ ImGui::GetWindowPos() };
			ImVec2 size{ ImGui::GetWindowSize() };

			ImGui::GetForegroundDrawList()->AddRect(
				{ position.x - 1, position.y - 1 },
				{ position.x + size.x + 1, position.y + size.y + 1 },
				ImColor(255, 0, 0),
				0.0f
			);

			std::string text = xorstr_("xo1337 RUST INTERNAL");
			ImVec2 text_size = ImGui::CalcTextSize(text.c_str());

			ImGui::GetForegroundDrawList()->AddText(fonts::courbd, 22.0f, { position.x + (size.x / 2) - (ImGui::GetStyle().FramePadding.x * 4.0f + text_size.x / 2), position.y + 15 }, ImColor(255, 0, 0), text.c_str());
			ImGui::Dummy(ImVec2(0, 30.0f));

			ImGui::PushStyleColor(ImGuiCol_Separator, ImColor(255, 0, 0).Value);
			ImGui::Separator();
			ImGui::PopStyleColor();

			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
			if (ImGui::CollapsingHeader(xorstr_("Aimbot"))) 
			{
				ImGui::PushFont(fonts::courbd);
				ImGui::PushStyleColor(ImGuiCol_Border, ImColor(255, 0, 0).Value);
				
				ImGui::Checkbox(xorstr_("Enabled ##aimbot"), &aimbot::enabled);
				checkbox_picker(xorstr_("Crosshair"), &aimbot::crosshair, aimbot::crosshair_color);
				slider_float(xorstr_("Crosshair Size: %.1f"), &aimbot::crosshair_size, 6.5, 6.5 * 4);

				checkbox_picker(xorstr_("Radius"), &aimbot::radius, aimbot::radius_color);
				slider_float(xorstr_("Radius Size: %.1f"), &aimbot::radius_size, 0, (float)winapi::window_size_x);

				ImGui::Checkbox(xorstr_("Visible Check"), &aimbot::visible_check);
				ImGui::Checkbox(xorstr_("Closest Bone"), &aimbot::closest_bone);

				slider_float(xorstr_("Smoothing: %.1f"), &aimbot::smoothing, 0, 100);

				ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
				ImGui::Combo(xorstr_("##jhsdfkjsdfkhjsdjfsdf"), &aimbot::selected_bone, xorstr_("Head\0Neck\0Chest\0Pelvis\0Penis\0"));
				ImGui::PopItemWidth();

				ImGui::HotKey(xorstr_("BIND"), &aimbot::key_bind, ImVec2(ImGui::GetContentRegionAvail().x, 20.0f));

				ImGui::PopStyleColor();
				ImGui::PopFont();
			}

			ImGui::Spacing();

			if (ImGui::CollapsingHeader(xorstr_("Visuals"))) 
			{
				ImGui::PushFont(fonts::courbd);
				ImGui::PushStyleColor(ImGuiCol_Border, ImColor(255, 0, 0).Value);

				slider_float(xorstr_("Maximum Distance %.3f"), &esp::max_dist, 1, 200.0f);

				ImGui::Checkbox(xorstr_("Enabled ##visuals"), &esp::enabled);
				checkbox_picker(xorstr_("Boxes"), &esp::boxes, esp::boxes_color);
				checkbox_picker(xorstr_("Corners"), &esp::corners, esp::corners_color);
				checkbox_picker(xorstr_("Snapline"), &esp::snaplines, esp::snaplines_color);
				checkbox_picker(xorstr_("Skeleton"), &esp::skeleton, esp::skeleton_color);
				ImGui::Checkbox(xorstr_("Health"), &esp::health_bar);
				checkbox_picker(xorstr_("Distance"), &esp::distance, esp::distance_color);
				
				checkbox_picker(xorstr_("Names"), &esp::names, esp::names_color);
				checkbox_picker(xorstr_("Weapon"), &esp::weapon_name, esp::weapon_name_color);

				ImGui::PopStyleColor();
				ImGui::PopFont();
			}

			ImGui::Spacing();

			if (ImGui::CollapsingHeader(xorstr_("Other"))) 
			{
				ImGui::PushFont(fonts::courbd);
				ImGui::PushStyleColor(ImGuiCol_Border, ImColor(255, 0, 0).Value);

				ImGui::Checkbox(xorstr_("Team check"), &misc::team_check);
				ImGui::Checkbox(xorstr_("Fake Admin (Risky)"), &misc::fake_admin);
				ImGui::Checkbox(xorstr_("Spiderman"), &misc::spiderman);
				ImGui::Checkbox(xorstr_("Infinite Jump"), &misc::infinite_jump);
				ImGui::Checkbox(xorstr_("Spinbot (hold C)"), &misc::spinbot);
				ImGui::Checkbox(xorstr_("Zoom (hold X)"), &misc::zoom);

				ImGui::Checkbox(xorstr_("Fatbullet"), &misc::fat_bullet);

				ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
				ImGui::SliderFloat(xorstr_("##jsdfkshdfsdfsdfsdf"), &misc::fov, 10, 180, xorstr_("Field of view: %.1f"));
				ImGui::PopItemWidth();
				ImGui::Spacing();

				ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
				ImGui::SliderFloat(xorstr_("##slkdejrffhisdhfikjsdhfkhsfd"), &misc::zoom_amount, 10, 180, xorstr_("Zoom Amount: %.1f"));
				ImGui::PopItemWidth();
				ImGui::Spacing();

				ImGui::PopStyleColor();
				ImGui::PopFont();
			}

			ImGui::Spacing();

			if (ImGui::CollapsingHeader(xorstr_("Settings")))
			{
				ImGui::PushFont(fonts::courbd);
				ImGui::PushStyleColor(ImGuiCol_Border, ImColor(255, 0, 0).Value);

				ImGui::Text(xorstr_("Build Date: %s"), xorstr_(__DATE__));

				ImGui::PopStyleColor();
				ImGui::PopFont();
			}

			ImGui::PopStyleVar();
			ImGui::End();
		}

		__forceinline void __fastcall fake_present_hook(void* _this)
		{
			uint8_t* stack_base = (uint8_t*)__readgsqword(8) - sizeof(void*);
			*(void**)stack_base = stack_base - sizeof(void*);

			uint64_t retaddr = (uint64_t)(_ReturnAddress());
			if (retaddr >= gui::dxgi_base && retaddr <= (gui::dxgi_base + gui::dxgi_size))
			{
				on_present(gui::d3d11_swap_chain);
			}

			EnterCriticalSection((LPCRITICAL_SECTION)((char*)_this + 16));
		}	

		bool init(IDXGISwapChain* swap_chain)
		{
			if (!swap_chain)
				return false;

			gui::dxgi_base = memory::get_module(xorstr_("dxgi.dll"));
			if (!gui::dxgi_base)
				return false;

			gui::dxgi_nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(gui::dxgi_base + reinterpret_cast<PIMAGE_DOS_HEADER>(gui::dxgi_base)->e_lfanew);
			if (gui::dxgi_nt_headers->Signature != IMAGE_NT_SIGNATURE)
				return false;

			gui::dxgi_size = gui::dxgi_nt_headers->OptionalHeader.SizeOfImage;
			if (gui::dxgi_size <= 0)
				return false;

			gui::d3d11_swap_chain = swap_chain;

			gui::d3d11_unk1 = (char*)gui::d3d11_swap_chain + 0x40;
			if (!gui::d3d11_unk1)
				return false;

			uint64_t* vtable = (uint64_t*)(**((uint64_t**)gui::d3d11_unk1 + 1));
			if (!vtable)
				return false;

			uint64_t cdeviceLOEnter = vtable[3];
			gui::d3d11_detour_original = (decltype(gui::d3d11_detour_original))(cdeviceLOEnter);
			memory::_memcpy(&gui::hooked_vtable, vtable, 4096);

			gui::hooked_vtable[3] = (uint64_t)&fake_present_hook;
			(**((PVOID**)gui::d3d11_unk1 + 1)) = gui::hooked_vtable;

			return true;
		}
	}
}