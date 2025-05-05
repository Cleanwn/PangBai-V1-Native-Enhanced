#pragma once
#include "types/script/scrNativeHandler.hpp"
#include "hooking/vmt_hook.hpp"
#include "util/joaat.hpp"

enum class NativeIndex;

namespace rage
{
	class scrProgram;
}
namespace MdayS
{
	class NativeHooks
	{
		struct Hook
		{
			NativeIndex m_Index;
			rage::scrNativeHandler m_Replacement;
		};

		class Program final
		{
			rage::scrProgram* m_Program = nullptr;
			std::unique_ptr<VMTHook> m_Hook = nullptr;
			rage::scrNativeHandler* m_OrigHandlers = nullptr;

		public:
			Program(rage::scrProgram* program);
			void Apply(Hook hook);
			void Cleanup();
			static void ScrProgram_Dtor(rage::scrProgram* _this, bool free_mem);
		};

		std::unordered_map<rage::scrProgram*, std::unique_ptr<Program>> m_RegisteredPrograms;
		std::unordered_map<joaat_t, std::vector<Hook>> m_RegisteredHooks;
	public:
		void RunScript();
		static constexpr auto ALL_SCRIPTS = "ALL_SCRIPTS"_J;
		void AddHook(joaat_t script, NativeIndex index, rage::scrNativeHandler hook);
		void RegisterProgram(rage::scrProgram* program);
		void UnregisterProgram(rage::scrProgram* program);
		void Destroy();
	};

	inline NativeHooks g_NativeHooks;
}