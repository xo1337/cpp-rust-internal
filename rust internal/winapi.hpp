#pragma once
#include "macros.hpp"
#include "syscaller.hpp"


#define ProbeForWriteGenericType(Ptr, Type) *(volatile Type *)(Ptr) = *(volatile Type *)(Ptr); 
#define ProbeForWriteLargeInteger(Ptr) ProbeForWriteGenericType(&((PLARGE_INTEGER)Ptr)->QuadPart, LONGLONG)
#define __PAIR16__(high, low) (((uint16) (high) << 8) | (uint8) (low))
#define __PAIR32__(high, low) (((uint32) (high) << 16) | (uint16)(low))
#define __PAIR64__(high, low) (((uint64) (high) << 32) | (uint32)(low))
#define __PAIR128__(high, low) (((uint128)(high) << 64) | (uint64)(low))
#define BYTEn(x, n) (*((BYTE*)&(x)+n))
#define WORDn(x, n) (*((WORD*)&(x)+n))
#define DWORDn(x, n) (*((DWORD*)&(x)+n))
#define WORD1(x) WORDn(x, 1)

namespace base
{ 
	namespace winapi 
	{
		inline uint32_t window_size_x = 0;
		inline uint32_t window_size_y = 0;

		inline BOOL(*oScreenToClient)(HWND, LPPOINT);

		inline bool initialize()
		{
			*(std::uint64_t*)&oScreenToClient = memory::get_export(xorstr_("user32.dll"), xorstr_("ScreenToClient"));
			return true;
		}

		inline SIZE_T* fnGetWin32ClientInfo()
		{
			return *(SIZE_T**)((uint64_t)NtCurrentTeb() + 0x800);
		}

		inline WNDPROC fnSetWindowLongPtrA(HWND hWnd, unsigned int nIndex, LONG_PTR dwNewLong)
		{
			return (WNDPROC)SetWindowLongPtrA(hWnd, nIndex, dwNewLong);
		}

		inline HWND NtUserGetForegroundWindow()
		{
			return GetForegroundWindow();
		}

		inline BOOL fnClientToScreen(HWND hWnd, LPPOINT lpPoint)
		{
			return ClientToScreen(hWnd, lpPoint);
		}

		inline BOOL fnScreenToClient(HWND hWnd, LPPOINT lpPoint)
		{
			return oScreenToClient(hWnd, lpPoint);
		}

		inline BOOL fnTrackMouseEvent(LPTRACKMOUSEEVENT lpEventTrack)
		{
			return TrackMouseEvent(lpEventTrack);
		}

		inline HCURSOR fnSetCursor(HCURSOR hCursor)
		{
			return SetCursor(hCursor);
		}

		inline BOOL fnSetCursorPos(int X, int Y)
		{
			return SetCursorPos(X, Y);
		}
	
		inline BOOL fnGetCursorPos(LPPOINT lpPoint)
		{
			return GetCursorPos(lpPoint);
		}

		inline BOOL fnGetClientRect(HWND hWnd, LPRECT lpRect)
		{
			RECT data;
			data.left = 0;
			data.right = window_size_x;
			data.bottom = window_size_y;
			data.top = 0;

			*lpRect = data;

			return ((data.right <= 0 || data.bottom <= 0) ? FALSE : TRUE);
		}

		inline HWND fnGetCapture()
		{
			return GetCapture();
		}

		inline HWND fnSetCapture(HWND hWnd)
		{
			return SetCapture(hWnd);
		}

		inline BOOL fnReleaseCapture()
		{
			return ReleaseCapture();
		}

		inline LONG fnNtQueryPerformanceCounter(PLARGE_INTEGER PerformanceCounter, PLARGE_INTEGER PerformanceFrequency)
		{
			LARGE_INTEGER PerfFrequency;

			ProbeForWriteLargeInteger(PerformanceCounter);
			if (PerformanceFrequency)
				ProbeForWriteLargeInteger(PerformanceFrequency);

			PerfFrequency.QuadPart = 0;

			if (PerformanceFrequency)
				*PerformanceFrequency = PerfFrequency;

			return 0;
		}

		inline BOOL fnQueryPerformanceFrequency(PLARGE_INTEGER lpFrequency)
		{
			LARGE_INTEGER Count;
			return (fnNtQueryPerformanceCounter(&Count, lpFrequency) == 0);
		}

		inline BOOL fnQueryPerformanceCounter(PLARGE_INTEGER lpPerformanceCount)
		{
			LARGE_INTEGER Frequency;
			return (fnNtQueryPerformanceCounter(lpPerformanceCount, &Frequency) == 0);
		}
	} 
}

namespace base { namespace d3d {
	
	inline std::uint64_t(*create_render_target_view_worker)(ID3D11Device*, ID3D11Resource*, const D3D11_RENDER_TARGET_VIEW_DESC*, const IID&, ...);

	inline bool initialize()
	{
		*(std::uint64_t*)&create_render_target_view_worker = memory::pattern(xorstr_("d3d11.dll"), xorstr_("48 8B C4 4C 89 48 ? 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 C7 40 ? ? ? ? ? 48 89 58 ? 48 89 70 ? 4D 8B F0")).get();
		return true;
	}

	inline HWND get_hwnd(IDXGISwapChain* _this)
	{
		return reinterpret_cast<HWND>(*((std::uint64_t*)_this + 0x1F));
	}

	// IDXGISwapChain::GetDevice
	inline HRESULT get_device(IDXGISwapChain* _this, const IID& a2, void** a3)
	{
		auto function = (***((__int64(__fastcall****)(std::uint64_t, const IID&, void**))_this + 0x13));
		return function(*((std::uint64_t*)_this + 0x13), a2, a3);
	}

	// IDXGISwapChain::GetBuffer
	inline HRESULT get_buffer(IDXGISwapChain* _this, int Buffer, const IID& riid, void** ppSurface)
	{
		unsigned int v6 = Buffer;
		int v9 = *((DWORD*)_this + 0x32);
		__int64(__fastcall*** v10)(std::uint64_t, const IID&, void**); // rcx

		if (v6 >= *((DWORD*)_this + 0x1EA))
		{
			v10 = (__int64(__fastcall***)(std::uint64_t, const IID&, void**)) * ((std::uint64_t*)_this + 0xDA);
		}
		else
		{
			v10 = (__int64(__fastcall***)(std::uint64_t, const IID&, void**)) * ((std::uint64_t*)_this + v6 + 0xC9);
			
		}

		if ((v9 & 0x80) != 0)
		{
			__int64 v20 = (__int64)(v10 + 9);
			if (!v10)
				v20 = 0x50;
			v10 = *(__int64(__fastcall****)(std::uint64_t, const IID&, void**))v20;
		}

		return (v10 != 0 ? (**v10)((__int64)v10, riid, ppSurface) : S_FALSE);
	}

	// ID3D11Device::CreateRenderTargetView
	inline HRESULT create_render_target_view(ID3D11Device* _this, ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
	{
		ID3D11Device* a1 = (ID3D11Device*)((std::uint64_t)_this - 0x10);
		ID3D11Resource* a2 = pResource;
		const auto a3 = pDesc;
		GUID a4 = __uuidof(ID3D11RenderTargetView);
		ID3D11RenderTargetView** a5 = ppRTView;
		bool a6 = 0;
		bool a7 = 1;

		return create_render_target_view_worker(a1, a2, a3, a4, a5, a6, a7);
	}

	// IUnknown::Release
	inline ULONG release(void* a1)
	{
		auto function = (*(ULONG(__fastcall**)(std::uint64_t))(**(std::uint64_t**)((std::uint64_t)a1 + 0x50) + 0x10));
		return function(*(std::uint64_t*)((std::uint64_t)a1 + 0x50));
	}

	inline void get_immediate_context(ID3D11Device* device, ID3D11DeviceContext** output)
	{
		if (output)
			*output = *(ID3D11DeviceContext**)(*((std::uint64_t*)device + 0x7C) + 0x60);
	}

	/*

		vtable functions:

		1 =  __int64 __fastcall TComObject<NOutermost::CDevice>::AddRef(__int64 a1)
		2 = __int64 __fastcall TComObject<NOutermost::CDevice>::Release(void *lpMem)
		3 = void __fastcall NOutermost::CDevice::LOEnter(NOutermost::CDevice *this)
		4 = void __fastcall NOutermost::CDevice::LOLeave(NOutermost::CDevice *this)
		
	*/
} }