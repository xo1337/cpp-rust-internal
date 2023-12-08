#pragma once

#include "offsets.hpp"
#include "includes.hpp"
#include "cfg.hpp"
#include "il2cpp.h"
#include <codecvt>

namespace unity {

    enum bone_id : uint32_t
    {
        pelvis = 0,
        l_hip = 1,
        l_knee = 2,
        l_foot = 3,
        l_toe = 4,
        l_ankle_scale = 5,
        penis = 6,
        GenitalCensor = 7,
        GenitalCensor_LOD0 = 8,
        Inner_LOD0_9 = 9,
        Inner_LOD0 = 10,
        GenitalCensor_LOD1 = 11,
        GenitalCensor_LOD2 = 12,
        r_hip = 13,
        r_knee = 14,
        r_foot = 15,
        r_toe = 16,
        r_ankle_scale = 17,
        spine1 = 18,
        spine1_scale = 19,
        spine2 = 20,
        spine3 = 21,
        spine4 = 22,
        l_clavicle = 23,
        l_upperarm = 24,
        l_forearm = 25,
        l_hand = 26,
        l_index1 = 27,
        l_index2 = 28,
        l_index3 = 29,
        l_little1 = 30,
        l_little2 = 31,
        l_little3 = 32,
        l_middle1 = 33,
        l_middle2 = 34,
        l_middle3 = 35,
        l_prop = 36,
        l_ring1 = 37,
        l_ring2 = 38,
        l_ring3 = 39,
        l_thumb1 = 40,
        l_thumb2 = 41,
        l_thumb3 = 42,
        IKtarget_righthand_min = 43,
        IKtarget_righthand_max = 44,
        l_ulna = 45,
        neck = 46,
        head = 47,
        jaw = 48,
        eyeTranform = 49,
        l_eye = 50,
        l_Eyelid = 51,
        r_eye = 52,
        r_Eyelid = 53,
        r_clavicle = 54,
        r_upperarm = 55,
        r_forearm = 56,
        r_hand = 57,
        r_index1 = 58,
        r_index2 = 59,
        r_index3 = 60,
        r_little1 = 61,
        r_little2 = 62,
        r_little3 = 63,
        r_middle1 = 64,
        r_middle2 = 65,
        r_middle3 = 66,
        r_prop = 67,
        r_ring1 = 68,
        r_ring2 = 69,
        r_ring3 = 70,
        r_thumb1 = 71,
        r_thumb2 = 72,
        r_thumb3 = 73,
        IKtarget_lefthand_min = 74,
        IKtarget_lefthand_max = 75,
        r_ulna = 76,
        l_breast = 77,
        r_breast = 78,
        BoobCensor = 79,
        BreastCensor_LOD0 = 80,
        Inner_LOD0_81 = 81,
        Inner_LOD0_82 = 82,
        BreastCensor_LOD1 = 83,
        BreastCensor_LOD2 = 84,
    };

    enum : WORD
    {
        tag_main_camera = 5,
        tag_player = 6,
        tag_terrain = 20001,
        tag_misc = 20006,
        tag_animal = 20008,
        tag_corpse = 20009,
        tag_monument = 20015,
        tag_helicopter = 20017,
        tag_skydometag = 20011
    };

    template<typename t> 
    inline t* get_fields(uintptr_t class_instance)
    {

        if (!class_instance)
            return nullptr;

        auto klass = *(uintptr_t*)(base::game_assembly + class_instance);

        if (!klass)
            return nullptr;

        auto instance = (t*)(klass);

        if (!instance)
            return nullptr;

        return instance;
    }

    template<typename T, typename ... Args>
    inline T call(uint64_t offset, Args ... args)
    {
        if (!offset)
            return T();

        auto function = reinterpret_cast<T(*)(Args ...)>(base::game_assembly + offset);
        if (!function)
            return T();

        return function(args ...);
    }

    class list {
    public:
        template <typename T>
        T get_value() {
            auto list = *reinterpret_cast<uintptr_t*>(this + 0x10);
            if (!list)
                return 0;

            auto value = *reinterpret_cast<T*>(list + 0x28);
            if (!value)
                return 0;
            return value;
        }

        int get_size() {
            auto value = get_value<uintptr_t>();
            if (!value)
                return 0;

            auto size = *(int*)(value + 0x10);
            if (!size)
                return 0;
        }

        template <typename T>
        T get_buffer() {
            auto value = get_value<uintptr_t>();

            return *reinterpret_cast<uintptr_t*>(value + 0x18);
        }
    };

    struct matrix4x4 
    {
        union 
        {
            struct 
            {
                float _11, _12, _13, _14;
                float _21, _22, _23, _24;
                float _31, _32, _33, _34;
                float _41, _42, _43, _44;

            }; float m[4][4];
        };
    };

    inline std::string utf16_to_utf8(std::u16string u16_string) 
    {
        std::wstring wide_string(u16_string.begin(), u16_string.end());
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
        return convert.to_bytes(wide_string);
    }

    inline std::string convert_from_string(System_String_o* input) 
    {
        if (!input) return xorstr_("**INVALID**");
        std::u16string u16(reinterpret_cast<const char16_t*>(&input->fields._firstChar));
        return utf16_to_utf8(u16);
    }

    namespace camera
    {
        void* get_main();
        matrix4x4 get_matrix();
        void get_position_Injected(void* _this, vector3& retval);
    }

    bool world_to_screen(vector3 location, ImVec2& return_value);
    bool get_bone_3d(BasePlayer_o* player, uint32_t id, vector3& output);
    bool get_bone(BasePlayer_o* player, uint32_t id, ImVec2& output);
}

namespace sdk 
{
    inline BasePlayer_o* local_player = nullptr;
    inline std::pair<uint64_t, uint32_t> entity_list = {};

    BasePlayer_o* get_local_player();
    std::pair<uint64_t, uint32_t> get_entity_list();
    Item_o* get_current_item(BasePlayer_o* player);
    vector2 get_best_aim_angles(unity::bone_id bone_id);
}

namespace modules
{
	bool update();
	void visuals(ImDrawList* draw_list, const ImVec2& size);
	void other(ImDrawList* draw_list, const ImVec2& size);
}

namespace addr 
{
    template<typename T>
    inline bool valid(T address) 
    {
        uint64_t ptr = (uint64_t)address;
        return (ptr > 0 && ptr < 0x7fffffffffffff);
    }
}