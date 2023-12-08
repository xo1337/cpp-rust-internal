#pragma once
#include "includes.hpp"

namespace base
{
	namespace d3d11
	{
		void on_style();

		void on_gui();

		inline std::function<void(ImDrawList*, const ImVec2&, const ImVec2&)> on_frame;

		bool init(IDXGISwapChain* swap_chain);
	};
}