#pragma once

#include <Windows.h>
#include <cstdint>
#include <d3d11.h>
#include <cstdio>
#include <vector>
#include <string>
#include <functional>
#include <filesystem>
#include <fstream>
#include <intrin.h>

#define _ACPI_XA     0x00    /* extra alphabetic - not supported */
#define _ACPI_XS     0x40    /* extra space */
#define _ACPI_BB     0x00    /* BEL, BS, etc. - not supported */
#define _ACPI_CN     0x20    /* CR, FF, HT, NL, VT */
#define _ACPI_DI     0x04    /* '0'-'9' */
#define _ACPI_LO     0x02    /* 'a'-'z' */
#define _ACPI_PU     0x10    /* punctuation */
#define _ACPI_SP     0x08    /* space, tab, CR, LF, VT, FF */
#define _ACPI_UP     0x01    /* 'A'-'Z' */
#define _ACPI_XD     0x80    /* '0'-'9', 'A'-'F', 'a'-'f' */

const UINT8 AcpiGbl_Ctypes[257] = {
 _ACPI_CN,            /* 0x00     0 NUL */
 _ACPI_CN,            /* 0x01     1 SOH */
 _ACPI_CN,            /* 0x02     2 STX */
 _ACPI_CN,            /* 0x03     3 ETX */
 _ACPI_CN,            /* 0x04     4 EOT */
 _ACPI_CN,            /* 0x05     5 ENQ */
 _ACPI_CN,            /* 0x06     6 ACK */
 _ACPI_CN,            /* 0x07     7 BEL */
 _ACPI_CN,            /* 0x08     8 BS  */
 _ACPI_CN | _ACPI_SP,   /* 0x09     9 TAB */
 _ACPI_CN | _ACPI_SP,   /* 0x0A    10 LF  */
 _ACPI_CN | _ACPI_SP,   /* 0x0B    11 VT  */
 _ACPI_CN | _ACPI_SP,   /* 0x0C    12 FF  */
 _ACPI_CN | _ACPI_SP,   /* 0x0D    13 CR  */
 _ACPI_CN,            /* 0x0E    14 SO  */
 _ACPI_CN,            /* 0x0F    15 SI  */
 _ACPI_CN,            /* 0x10    16 DLE */
 _ACPI_CN,            /* 0x11    17 DC1 */
 _ACPI_CN,            /* 0x12    18 DC2 */
 _ACPI_CN,            /* 0x13    19 DC3 */
 _ACPI_CN,            /* 0x14    20 DC4 */
 _ACPI_CN,            /* 0x15    21 NAK */
 _ACPI_CN,            /* 0x16    22 SYN */
 _ACPI_CN,            /* 0x17    23 ETB */
 _ACPI_CN,            /* 0x18    24 CAN */
 _ACPI_CN,            /* 0x19    25 EM  */
 _ACPI_CN,            /* 0x1A    26 SUB */
 _ACPI_CN,            /* 0x1B    27 ESC */
 _ACPI_CN,            /* 0x1C    28 FS  */
 _ACPI_CN,            /* 0x1D    29 GS  */
 _ACPI_CN,            /* 0x1E    30 RS  */
 _ACPI_CN,            /* 0x1F    31 US  */
 _ACPI_XS | _ACPI_SP,   /* 0x20    32 ' ' */
 _ACPI_PU,            /* 0x21    33 '!' */
 _ACPI_PU,            /* 0x22    34 '"' */
 _ACPI_PU,            /* 0x23    35 '#' */
 _ACPI_PU,            /* 0x24    36 '$' */
 _ACPI_PU,            /* 0x25    37 '%' */
 _ACPI_PU,            /* 0x26    38 '&' */
 _ACPI_PU,            /* 0x27    39 ''' */
 _ACPI_PU,            /* 0x28    40 '(' */
 _ACPI_PU,            /* 0x29    41 ')' */
 _ACPI_PU,            /* 0x2A    42 '*' */
 _ACPI_PU,            /* 0x2B    43 '+' */
 _ACPI_PU,            /* 0x2C    44 ',' */
 _ACPI_PU,            /* 0x2D    45 '-' */
 _ACPI_PU,            /* 0x2E    46 '.' */
 _ACPI_PU,            /* 0x2F    47 '/' */
 _ACPI_XD | _ACPI_DI,   /* 0x30    48 '0' */
 _ACPI_XD | _ACPI_DI,   /* 0x31    49 '1' */
 _ACPI_XD | _ACPI_DI,   /* 0x32    50 '2' */
 _ACPI_XD | _ACPI_DI,   /* 0x33    51 '3' */
 _ACPI_XD | _ACPI_DI,   /* 0x34    52 '4' */
 _ACPI_XD | _ACPI_DI,   /* 0x35    53 '5' */
 _ACPI_XD | _ACPI_DI,   /* 0x36    54 '6' */
 _ACPI_XD | _ACPI_DI,   /* 0x37    55 '7' */
 _ACPI_XD | _ACPI_DI,   /* 0x38    56 '8' */
 _ACPI_XD | _ACPI_DI,   /* 0x39    57 '9' */
 _ACPI_PU,            /* 0x3A    58 ':' */
 _ACPI_PU,            /* 0x3B    59 ';' */
 _ACPI_PU,            /* 0x3C    60 '<' */
 _ACPI_PU,            /* 0x3D    61 '=' */
 _ACPI_PU,            /* 0x3E    62 '>' */
 _ACPI_PU,            /* 0x3F    63 '?' */
 _ACPI_PU,            /* 0x40    64 '@' */
 _ACPI_XD | _ACPI_UP,   /* 0x41    65 'A' */
 _ACPI_XD | _ACPI_UP,   /* 0x42    66 'B' */
 _ACPI_XD | _ACPI_UP,   /* 0x43    67 'C' */
 _ACPI_XD | _ACPI_UP,   /* 0x44    68 'D' */
 _ACPI_XD | _ACPI_UP,   /* 0x45    69 'E' */
 _ACPI_XD | _ACPI_UP,   /* 0x46    70 'F' */
 _ACPI_UP,            /* 0x47    71 'G' */
 _ACPI_UP,            /* 0x48    72 'H' */
 _ACPI_UP,            /* 0x49    73 'I' */
 _ACPI_UP,            /* 0x4A    74 'J' */
 _ACPI_UP,            /* 0x4B    75 'K' */
 _ACPI_UP,            /* 0x4C    76 'L' */
 _ACPI_UP,            /* 0x4D    77 'M' */
 _ACPI_UP,            /* 0x4E    78 'N' */
 _ACPI_UP,            /* 0x4F    79 'O' */
 _ACPI_UP,            /* 0x50    80 'P' */
 _ACPI_UP,            /* 0x51    81 'Q' */
 _ACPI_UP,            /* 0x52    82 'R' */
 _ACPI_UP,            /* 0x53    83 'S' */
 _ACPI_UP,            /* 0x54    84 'T' */
 _ACPI_UP,            /* 0x55    85 'U' */
 _ACPI_UP,            /* 0x56    86 'V' */
 _ACPI_UP,            /* 0x57    87 'W' */
 _ACPI_UP,            /* 0x58    88 'X' */
 _ACPI_UP,            /* 0x59    89 'Y' */
 _ACPI_UP,            /* 0x5A    90 'Z' */
 _ACPI_PU,            /* 0x5B    91 '[' */
 _ACPI_PU,            /* 0x5C    92 '\' */
 _ACPI_PU,            /* 0x5D    93 ']' */
 _ACPI_PU,            /* 0x5E    94 '^' */
 _ACPI_PU,            /* 0x5F    95 '_' */
 _ACPI_PU,            /* 0x60    96 '`' */
 _ACPI_XD | _ACPI_LO,   /* 0x61    97 'a' */
 _ACPI_XD | _ACPI_LO,   /* 0x62    98 'b' */
 _ACPI_XD | _ACPI_LO,   /* 0x63    99 'c' */
 _ACPI_XD | _ACPI_LO,   /* 0x64   100 'd' */
 _ACPI_XD | _ACPI_LO,   /* 0x65   101 'e' */
 _ACPI_XD | _ACPI_LO,   /* 0x66   102 'f' */
 _ACPI_LO,            /* 0x67   103 'g' */
 _ACPI_LO,            /* 0x68   104 'h' */
 _ACPI_LO,            /* 0x69   105 'i' */
 _ACPI_LO,            /* 0x6A   106 'j' */
 _ACPI_LO,            /* 0x6B   107 'k' */
 _ACPI_LO,            /* 0x6C   108 'l' */
 _ACPI_LO,            /* 0x6D   109 'm' */
 _ACPI_LO,            /* 0x6E   110 'n' */
 _ACPI_LO,            /* 0x6F   111 'o' */
 _ACPI_LO,            /* 0x70   112 'p' */
 _ACPI_LO,            /* 0x71   113 'q' */
 _ACPI_LO,            /* 0x72   114 'r' */
 _ACPI_LO,            /* 0x73   115 's' */
 _ACPI_LO,            /* 0x74   116 't' */
 _ACPI_LO,            /* 0x75   117 'u' */
 _ACPI_LO,            /* 0x76   118 'v' */
 _ACPI_LO,            /* 0x77   119 'w' */
 _ACPI_LO,            /* 0x78   120 'x' */
 _ACPI_LO,            /* 0x79   121 'y' */
 _ACPI_LO,            /* 0x7A   122 'z' */
 _ACPI_PU,            /* 0x7B   123 '{' */
 _ACPI_PU,            /* 0x7C   124 '|' */
 _ACPI_PU,            /* 0x7D   125 '}' */
 _ACPI_PU,            /* 0x7E   126 '~' */
 _ACPI_CN,            /* 0x7F   127 DEL */

 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  /* 0x80 to 0x8F    */
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  /* 0x90 to 0x9F    */
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  /* 0xA0 to 0xAF    */
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  /* 0xB0 to 0xBF    */
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  /* 0xC0 to 0xCF    */
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  /* 0xD0 to 0xDF    */
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  /* 0xE0 to 0xEF    */
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  /* 0xF0 to 0xFF    */
 0                                 /* 0x100 */
};

#define _islower(c)  (AcpiGbl_Ctypes[(unsigned char)(c)] & (_ACPI_LO))

namespace base { namespace memory {

	struct CLIENT_ID
	{
		HANDLE UniqueProcess;
		HANDLE UniqueThread;
	};

	struct TEB
	{
		NT_TIB NtTib;
		PVOID EnvironmentPointer;
		CLIENT_ID ClientId;
		PVOID ActiveRpcHandle;
		PVOID ThreadLocalStoragePointer;
		struct PEB* ProcessEnvironmentBlock;
	};

	struct PEB_LDR_DATA
	{
		ULONG Length;
		BOOLEAN Initialized;
		HANDLE SsHandle;
		LIST_ENTRY InLoadOrderModuleList;
		LIST_ENTRY InMemoryOrderModuleList;
		LIST_ENTRY InInitializationOrderModuleList;
		PVOID EntryInProgress;
		BOOLEAN ShutdownInProgress;
		HANDLE ShutdownThreadId;
	};

	struct PEB
	{
		BOOLEAN InheritedAddressSpace;
		BOOLEAN ReadImageFileExecOptions;
		BOOLEAN BeingDebugged;
		union
		{
			BOOLEAN BitField;
			struct
			{
				BOOLEAN ImageUsesLargePages : 1;
				BOOLEAN IsProtectedProcess : 1;
				BOOLEAN IsImageDynamicallyRelocated : 1;
				BOOLEAN SkipPatchingUser32Forwarders : 1;
				BOOLEAN IsPackagedProcess : 1;
				BOOLEAN IsAppContainer : 1;
				BOOLEAN IsProtectedProcessLight : 1;
				BOOLEAN SpareBits : 1;
			};
		};
		HANDLE Mutant;
		PVOID ImageBaseAddress;
		PEB_LDR_DATA* Ldr;
	};

	struct UNICODE_STRING
	{
		USHORT Length;
		USHORT MaximumLength;
		PWCH Buffer;
	};

	struct LDR_DATA_TABLE_ENTRY
	{
		LIST_ENTRY InLoadOrderLinks;
		LIST_ENTRY InMemoryOrderLinks;
		union
		{
			LIST_ENTRY InInitializationOrderLinks;
			LIST_ENTRY InProgressLinks;
		};
		PVOID DllBase;
		PVOID EntryPoint;
		ULONG SizeOfImage;
		UNICODE_STRING FullDllName;
		UNICODE_STRING BaseDllName;
	};

	inline void* __cdecl __memccpy(void* to, const void* from, int c, size_t count)
	{
		char t;
		size_t i;
		char* dst = (char*)to;
		const char* src = (const char*)from;

		for (i = 0; i < count; i++)
		{
			dst[i] = t = src[i];
			if (t == '\0')
				break;
			if (t == c)
				return &dst[i + 1];
		}
		return NULL; /* didn't copy c */
	}

	inline void* __cdecl _memchr(const void* s, int c, size_t n)
	{
		if (n)
		{
			const char* p = (const char*)s;
			do {
				if (*p++ == c)
					return (void*)(p - 1);
			} while (--n != 0);
		}
		return 0;
	}

	inline void* __cdecl _memcpy(void* dest, const void* src, size_t count)
	{
		char* char_dest = (char*)dest;
		char* char_src = (char*)src;

		if ((char_dest <= char_src) || (char_dest >= (char_src + count)))
		{
			/*  non-overlapping buffers */
			while (count > 0)
			{
				*char_dest = *char_src;
				char_dest++;
				char_src++;
				count--;
			}
		}
		else
		{
			/* overlaping buffers */
			char_dest = (char*)dest + count - 1;
			char_src = (char*)src + count - 1;

			while (count > 0)
			{
				*char_dest = *char_src;
				char_dest--;
				char_src--;
				count--;
			}
		}

		return dest;
	}

	inline void* __cdecl _memmove(void* dest, const void* src, size_t count)
	{
		char* char_dest = (char*)dest;
		char* char_src = (char*)src;

		if ((char_dest <= char_src) || (char_dest >= (char_src + count)))
		{
			/*  non-overlapping buffers */
			while (count > 0)
			{
				*char_dest = *char_src;
				char_dest++;
				char_src++;
				count--;
			}
		}
		else
		{
			/* overlaping buffers */
			char_dest = (char*)dest + count - 1;
			char_src = (char*)src + count - 1;

			while (count > 0)
			{
				*char_dest = *char_src;
				char_dest--;
				char_src--;
				count--;
			}
		}

		return dest;
	}

	inline void* __cdecl _memset(void* src, int val, size_t count)
	{
		char* char_src = (char*)src;

		while (count > 0) {
			*char_src = val;
			char_src++;
			count--;
		}
		return src;
	}

	inline const unsigned short* __cdecl __pwctype_func(void)
	{
		return __pwctype_func();
	}

	inline int __cdecl __isctype(int c, int ctypeFlags)
	{
		return (__pctype_func()[(unsigned char)(c & 0xFF)] & ctypeFlags);
	}

	inline wint_t __cdecl _towlower(wint_t c)
	{
		if (__isctype(c, _UPPER))
			return (c - ('A' - 'a'));
		return(c);
	}

	inline int __cdecl _isspace(int c)
	{
		return (__isctype(c, _SPACE));
	}

	inline  int __cdecl _isdigit(int c)
	{
		return(__isctype(c, _DIGIT));
	}

	inline  int __cdecl _isalpha(int c)
	{
		return(__isctype(c, _ALPHA));
	}

	inline int __cdecl _isupper(int c)
	{
		return (__isctype(c, _UPPER));
	}

	inline unsigned long long __cdecl _strtoull(const char* nptr, char** endptr, int base)
	{
		const char* s = nptr;
		unsigned long long acc;
		int c;
		unsigned long long cutoff;
		int neg = 0, any, cutlim;

		/*
		 * See strtol for comments as to the logic used.
		 */
		do {
			c = *s++;
		} while (_isspace(c));
		if (c == '-')
		{
			neg = 1;
			c = *s++;
		}
		else if (c == '+')
			c = *s++;
		if ((base == 0 || base == 16) &&
			c == '0' && (*s == 'x' || *s == 'X'))
		{
			c = s[1];
			s += 2;
			base = 16;
		}
		if (base == 0)
			base = c == '0' ? 8 : 10;
		cutoff = (unsigned long long)ULLONG_MAX / (unsigned long long)base;
		cutlim = (unsigned long long)ULLONG_MAX % (unsigned long long)base;
		for (acc = 0, any = 0;; c = *s++)
		{
			if (_isdigit(c))
				c -= '0';
			else if (_isalpha(c))
				c -= _isupper(c) ? 'A' - 10 : 'a' - 10;
			else
				break;
			if (c >= base)
				break;
			if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
				any = -1;
			else {
				any = 1;
				acc *= base;
				acc += c;
			}
		}
		if (neg)
			acc = 0 - acc;
		if (endptr != 0)
			*endptr = any ? (char*)((size_t)(s - 1)) : (char*)((size_t)nptr);
		return acc;
	}

	inline int __cdecl crc32_wcsicmp(const wchar_t* cs, const wchar_t* ct)
	{
		while (_towlower(*cs) == _towlower(*ct))
		{
			if (*cs == 0)
				return 0;
			cs++;
			ct++;
		}
		return _towlower(*cs) - _towlower(*ct);
	}

	inline unsigned int crc32_strlen(const char* String)
	{
		UINT32 Length = 0;
		while (*String)
		{
			Length++;
			String++;
		}

		return (Length);
	}

	inline int crc32_strcmp(const char* String1, const char* String2)
	{
		for (; (*String1 == *String2); String2++)
		{
			if (!*String1++)
			{
				return (0);
			}
		}

		return ((unsigned char)*String1 - (unsigned char)*String2);
	}

	inline int crc32_toupper(int c)
	{
		return (_islower(c) ? ((c)-0x20) : (c));
	}

	inline unsigned long long crc32_strtoull(const char* nptr, char** endptr, int base)
	{
		const char* s = nptr;
		unsigned long long acc;
		int c;
		unsigned long long cutoff;
		int neg = 0, any, cutlim;

		do {
			c = *s++;
		} while (_isspace(c));
		if (c == '-')
		{
			neg = 1;
			c = *s++;
		}
		else if (c == '+')
			c = *s++;
		if ((base == 0 || base == 16) &&
			c == '0' && (*s == 'x' || *s == 'X'))
		{
			c = s[1];
			s += 2;
			base = 16;
		}
		if (base == 0)
			base = c == '0' ? 8 : 10;
		cutoff = (unsigned long long)ULLONG_MAX / (unsigned long long)base;
		cutlim = (unsigned long long)ULLONG_MAX % (unsigned long long)base;
		for (acc = 0, any = 0;; c = *s++)
		{
			if (_isdigit(c))
				c -= '0';
			else if (_isalpha(c))
				c -= _isupper(c) ? 'A' - 10 : 'a' - 10;
			else
				break;
			if (c >= base)
				break;
			if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
				any = -1;
			else {
				any = 1;
				acc *= base;
				acc += c;
			}
		}
		if (any < 0)
		{
			acc = ULLONG_MAX;
		}
		else if (neg)
			acc = 0 - acc;
		if (endptr != 0)
			*endptr = any ? (char*)((size_t)(s - 1)) : (char*)((size_t)nptr);
		return acc;
	}

	inline int crc32_memcmp(const void* s1, const void* s2, size_t n)
	{
		if (n != 0) {
			const unsigned char* p1 = (const unsigned char*)s1, * p2 = (const unsigned char*)s2;
			do {
				if (*p1++ != *p2++)
					return (*--p1 - *--p2);
			} while (--n != 0);
		}
		return 0;
	}

	inline const char* crc32_strstr(const char* String1, const char* String2)
	{
		unsigned int Length;

		Length = crc32_strlen(String2);
		if (!Length)
		{
			return (String1);
		}

		while (crc32_strlen(String1) >= Length)
		{
			if (crc32_memcmp(String1, String2, Length) == 0)
			{
				return (String1);
			}
			String1++;
		}

		return (NULL);
	}

	inline char* crc32_strncpy(char* DstString, const char* SrcString, unsigned int Count)
	{
		char* String = DstString;
		for (String = DstString;
			Count && (Count--, (*String++ = *SrcString++)); )
		{
			;
		}

		while (Count--)
		{
			*String = 0;
			String++;
		}

		return (DstString);
	}

	inline _TEB* _NtCurrentTeb()
	{
		return (struct _TEB*)__readgsqword(((LONG)__builtin_offsetof(NT_TIB, Self)));
	}

	inline std::uint64_t get_main_image_base()
	{
		PEB* ProcessEnvironmentBlock = ((PEB*)((TEB*)((TEB*)_NtCurrentTeb())->ProcessEnvironmentBlock));
		return (std::uint64_t)ProcessEnvironmentBlock->ImageBaseAddress;
	}

	inline std::uint64_t get_module(std::string module_name)
	{	
		PEB* ProcessEnvironmentBlock = ((PEB*)((TEB*)((TEB*)_NtCurrentTeb())->ProcessEnvironmentBlock));
		PEB_LDR_DATA* Ldr = ProcessEnvironmentBlock->Ldr;

		std::wstring Temp(module_name.begin(), module_name.end());
		const wchar_t* lpModuleName = Temp.c_str();

		LIST_ENTRY* ModuleLists[3] = { 0,0,0 };
		ModuleLists[0] = &Ldr->InLoadOrderModuleList;
		ModuleLists[1] = &Ldr->InMemoryOrderModuleList;
		ModuleLists[2] = &Ldr->InInitializationOrderModuleList;

		for (int j = 0; j < 3; j++)
		{
			for (LIST_ENTRY* pListEntry = ModuleLists[j]->Flink; pListEntry != ModuleLists[j]; pListEntry = pListEntry->Flink)
			{
				LDR_DATA_TABLE_ENTRY* pEntry = (LDR_DATA_TABLE_ENTRY*)((BYTE*)pListEntry - sizeof(LIST_ENTRY) * j);
				if (crc32_wcsicmp(pEntry->BaseDllName.Buffer, lpModuleName) == 0)
					return (std::uint64_t)pEntry->DllBase;
			}
		}

		return 0;
	}

	inline std::uint64_t get_export(LPCSTR module_name, LPCSTR exported_routine)
	{
		PIMAGE_DOS_HEADER pIDH;
		PIMAGE_NT_HEADERS pINH;
		PIMAGE_EXPORT_DIRECTORY pIED;

		HMODULE hModule;
		PDWORD Address, Name;
		PWORD Ordinal;

		DWORD i;

		hModule = (HMODULE)get_module(module_name);
		if (!hModule) return 0;

		pIDH = (PIMAGE_DOS_HEADER)hModule;

		if (pIDH->e_magic != IMAGE_DOS_SIGNATURE) return 0;
		pINH = (PIMAGE_NT_HEADERS)((LPBYTE)hModule + pIDH->e_lfanew);

		if (pINH->Signature != IMAGE_NT_SIGNATURE) return 0;
		if (pINH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress == 0) return 0;

		pIED = (PIMAGE_EXPORT_DIRECTORY)((LPBYTE)hModule + pINH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
		Address = (PDWORD)((LPBYTE)hModule + pIED->AddressOfFunctions);
		Name = (PDWORD)((LPBYTE)hModule + pIED->AddressOfNames);
		Ordinal = (PWORD)((LPBYTE)hModule + pIED->AddressOfNameOrdinals);

		for (i = 0; i < pIED->AddressOfFunctions; i++)
		{
			if (!crc32_strcmp(exported_routine, (char*)hModule + Name[i]))
			{
				return (std::uint64_t)((LPBYTE)hModule + Address[Ordinal[i]]);
			}
		}

		return 0;
	}

	template<typename T = void*, typename ... Args>
	inline T call(const char* szModule, const char* szExport, Args ... args)
	{
		auto fn = reinterpret_cast<T(*)(Args...)>(get_export(szModule, szExport));
		if (!fn) return T();

		return fn( args ...);
	}

	inline void popup(const std::string message, std::uint32_t flags = (MB_OK | MB_ICONINFORMATION))
	{
		MSGBOXPARAMSA msgbox;

		msgbox.cbSize = sizeof(MSGBOXPARAMSA);
		msgbox.hwndOwner = 0;
		msgbox.hInstance = 0;
		msgbox.lpszText = message.c_str();
		msgbox.lpszCaption = 0;
		msgbox.dwStyle = flags;
		msgbox.lpszIcon = 0;
		msgbox.dwContextHelpId = 0;
		msgbox.lpfnMsgBoxCallback = 0;
		msgbox.dwLanguageId = LANG_NEUTRAL;

		auto function = reinterpret_cast<int(__stdcall*)(const tagMSGBOXPARAMSA*)>(get_export(xorstr_("user32.dll"), xorstr_("MessageBoxIndirectA")));
		function((const tagMSGBOXPARAMSA*)&msgbox);
	}

	class pattern
	{
	private:
		std::uint64_t make_pattern(const char* module, const char* pattern, bool from_image_base = false, std::uint64_t* image_base = 0)
		{
			std::uint64_t module_address = 0;

			switch (from_image_base)
			{
			case true:
				module_address = get_main_image_base();
				break;
			case false:
				module_address = get_module(module);
				break;
			}

			if (!module_address) return 0;

			if (image_base)
				*image_base = module_address;

			static auto patternToByte = [](const char* pattern)
			{
				auto       bytes = std::vector<int>{};
				const auto start = const_cast<char*>(pattern);
				const auto end = const_cast<char*>(pattern) + crc32_strlen(pattern);

				for (auto current = start; current < end; ++current)
				{
					if (*current == '?')
					{
						++current;
						if (*current == '?')
							++current;
						bytes.push_back(-1);
					}
					else { bytes.push_back(crc32_strtoull(current, &current, 16)); }
				}
				return bytes;
			};

			const auto dosHeader = (PIMAGE_DOS_HEADER)module_address;
			const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module_address + dosHeader->e_lfanew);

			const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
			auto       patternBytes = patternToByte(pattern);
			const auto scanBytes = reinterpret_cast<std::uint8_t*>(module_address);

			const auto s = patternBytes.size();
			const auto d = patternBytes.data();

			for (auto i = 0ul; i < sizeOfImage - s; ++i)
			{
				bool found = true;
				for (auto j = 0ul; j < s; ++j)
				{
					if (scanBytes[i + j] != d[j] && d[j] != -1)
					{
						found = false;
						break;
					}
				}
				if (found) { return reinterpret_cast<uintptr_t>(&scanBytes[i]); }
			}
			return 0ull;
		}

		std::uint64_t m_address;
		std::uint64_t m_image;
	public:

		pattern(std::uint64_t module, const char* pattern)
		{
			m_address = 0;
			m_image = 0;
			m_address = make_pattern(nullptr, pattern, true, &m_image);
		}

		pattern(const char* module, const char* pattern)
		{
			m_address = 0;
			m_image = 0;
			m_address = make_pattern(module, pattern, false, &m_image);
		}

		inline bool valid() const
		{
			return (m_address > 0 && m_image > 0);
		}

		inline std::uint64_t get() const
		{
			return m_address;
		}

		inline std::uint64_t base() const
		{
			return m_image;
		}

		inline pattern& rva(int value)
		{
			this->m_address += *(int*)(this->m_address + value);
			return *this;
		}

		inline pattern& size(int value)
		{
			this->m_address += value;
			return *this;
		}

		inline pattern& add(int value)
		{
			this->m_address += value;
			return *this;
		}

		inline pattern& sub(int value)
		{
			if (value != -1)
				this->m_address -= value;
			else if (value == -1)
				this->m_address -= m_image;
			return *this;
		}

		template<typename type = std::uint64_t>
		inline pattern& set(type& value, bool deref = false)
		{
			*(std::uint64_t*)&value = (deref ? *(type*)(this->m_address) : this->m_address); 
			return *this;
		}
	};

} }

extern int __cdecl crc32_vsnprintf(char* buf, size_t cnt, const char* fmt, va_list args);

#define SAFE_CALL(function, ...) (reinterpret_cast<decltype(&function)>(do_safe_call((std::uint64_t)function)))(__VA_ARGS__)
extern "C" __forceinline std::uint64_t do_safe_call(std::uint64_t rcx);

#include "crc32.hpp"
#include "winapi.hpp"