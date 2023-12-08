# 💻 ***C++ Rust Internal***
***A internal software developed for the game Rust. Made for educational purposes.***

**Showcase Video:**

[![Showcase Video](https://img.youtube.com/vi/b5nBIwMBYVQ/0.jpg)](https://www.youtube.com/watch?v=b5nBIwMBYVQ)

> [!NOTE]
> An injector is not included, so you have to figure out how to get the DLL in the game. The injector I used is modified, and so you will see some winapi calls on purpose because the injector I used spoof called all the winapi functions so I didn't have to manually spoof call them one by one. Feel free to manually spoof call these winapi calls yourself if you want. 

> [!NOTE]
> The offsets have not been updated since I've last worked on this project. To update them follow these steps:
> 1. Download IL2CPP Dumper and DnSpy.
> 2. Dump rust with IL2CPP dumper
> 3. Replace the `il2cpp.h` file with the one generated from IL2CPP dumper.
> 4. Open the `config.json` file generated from IL2CPP dumper
> 5. Goto `modules/offsets.hpp` and update all of the offsets from what you get in `config.json`
> 6. Thats it! 

![alt text](https://github.com/xo1337/cpp-rust-internal/blob/main/images/rust_internal_1.png)
![alt text](https://github.com/xo1337/cpp-rust-internal/blob/main/images/rust_internal_2.png)

## 🧰 Code Features:
- No hooks
  - The only hooks that are used in this code is just for the overlay, which you can't really avoid. Everything else from the aimbot to visuals, are all done without hooking any of Rusts unity/game functions which most other rust internals do infact do.

- Obfuscation Barley any CRT functions
  - I've spent quite a good chunk of time encrypting every single string possible, and avoiding using CRT functions like `sqrt` `tan` `atan`, etc. I've re-wrote most of these functions, even the simple ones like `memcpy` `memcmp` to avoid calling any C-runtime functions. There is also a macro definition called `SAFE_CALL`, this macro just essentially calls a funtion passed but does a whole bunch of random junk in assembly to slightly confuse and throw off any reverse engineer. Although if you're insanely skilled you can probably tell its just a bunch of crap LOL.
  
- Obfuscated/Encrypted ImGui Library/Modified ImGui API
   - **By default, ImGui has lots of strings and things that can be sigged by anticheats and third parties to detect your software. In this project, I've made it very difficult for these third parties to find anything ImGui related in this file. Once the DLL is compiled, you won't find a single trace of ImGui in the strings, or anywhere else. It took me more than 2hours going through all of ImGui and removing all string traces and even certain array of bytes of things like fonts, etc... The ImGui API/code in this project is also heavily modified to avoid calling any window API functions and just doing things straight through just recreating functions.**

- Custom DirectX 11 Hooking Method `d3d11.hpp/cpp`
    - **I haven't seen anyone else post about this, so I believe I'm the first one to do this but it's worked extremely well on many games without causing bans. Instead of directly hooking DirectX by doing a function pointer swap in the DXGI vtable or hooking another overlay, I instead hook a function (via .data ptr swap) that is being called inside of present. That function that is being called deep down inside present is a very small function and literally only calls one function: EnterCriticalSection(), and therefore I don't have to do much else than to hook the function and simply call my present handler inside it. So far I've tested this rendering method on Apex and Rust ofcourse without any issues. I'm sure they will detect it now because of this release, but who knows.**
```cpp
// get the games swapchain from previous func call that set the var
gui::d3d11_swap_chain = swap_chain;

// enter the first pointer to the vtable
gui::d3d11_unk1 = (char*)gui::d3d11_swap_chain + 0x40;

// get the vtable for where this function is located
uint64_t* vtable = (uint64_t*)(**((uint64_t**)gui::d3d11_unk1 + 1));

uint64_t cdeviceLOEnter = vtable[3]; // index of func is 3
gui::d3d11_detour_original = (decltype(gui::d3d11_detour_original))(cdeviceLOEnter);
memory::_memcpy(&gui::hooked_vtable, vtable, 4096);

// do a vtable swap hook on the function, instead of just byte patching
gui::hooked_vtable[3] = (uint64_t)&fake_present_hook;
(**((PVOID**)gui::d3d11_unk1 + 1)) = gui::hooked_vtable;
```

```cpp
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
```

## 😁 Menu Features:
**_1._ Aimbot**
   - Visible Check
   - Crosshair/Color Picker
   - Radius/Color Picker
   - Radius Filled/Color Picker
   - Closest Bone
   - Select target bone (head, neck, chest)
   - Smoothing (float)
   - Keybind
     
**_2._ Visuals**
   - Boxes/Color Picker
   - Boxes Filled
   - Corners/Color Picker
   - Snaplines/Color Picker
   - Skeleton/Color Picker
   - Player Distance/Color Picker
   - Player Names/Color Picker
   - Health Bar
   - Visible/Non-Visible/Color Picker
   - Weapon Name/Color Picker
   - Maximum Distance

**_3._ Misc/Other**
   - Custom field of view (10-150)
   - Zoom/Keybind
   - Team Check (aimbot/visuals)
   - Fake Admin
   - Spiderman
   - Infinite Jump
   - Spinbot
