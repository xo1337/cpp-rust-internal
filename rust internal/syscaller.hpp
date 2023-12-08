#pragma once

#include <cstdint>
extern "C" void* syscall_stub();

namespace system_call
{
	template<typename T, typename First = void*, typename Second = void*, typename Third = void*, typename Fourth = void*>
	T call(std::uint32_t idx, First first = 0, Second second = 0, Third third = 0, Fourth fourth = 0)
	{
		auto fn = reinterpret_cast<T(*)(First, Second, Third, Fourth, std::uint32_t)>(&syscall_stub);
		return fn(first, second, third, fourth, idx);
	}

	template<typename T, typename First, typename Second, typename Third, typename Fourth, typename... Args>
	T call(std::uint32_t idx, First first, Second second, Third third, Fourth fourth, Args... args)
	{
		auto fn = reinterpret_cast<T(*)(First, Second, Third, Fourth, std::uint32_t, Args...)>(&syscall_stub);
		return fn(first, second, third, fourth, idx, args...);
	}

	template<typename T>
	class func
	{
	public:
		void init(std::string func_name, std::string module_name = xorstr_("win32u.dll"))
		{
			auto fn = (base::memory::get_export(module_name.c_str(), func_name.c_str()));
			_syscall_idx = *reinterpret_cast<std::uint32_t*>(fn + 4);
		}

		func() 
		{
			
		}

		explicit func(std::string func_name, std::string module_name = xorstr_("win32u.dll"))
		{ 
			init(func_name, module_name);
		}

		template<typename... Args>
		T operator()(Args... args)
		{
			return call<T>(_syscall_idx, std::forward<Args>(args)...);
		}
	private:
		std::uint32_t _syscall_idx;
	};

	template<typename T = NTSTATUS, typename ... Args>
	inline T syscall(std::string func_name, std::string module_name, Args ... args)
	{
		system_call::func<T> addr_of_call(func_name, module_name);
		return addr_of_call(args ...);
	}
}

#define SYSCALL(Type, FunctionName, FunctionModule, ...) system_call::syscall<Type>(xorstr_(#FunctionName), xorstr_(#FunctionModule), __VA_ARGS__)
