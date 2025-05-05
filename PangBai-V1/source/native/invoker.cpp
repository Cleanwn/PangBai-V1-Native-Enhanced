#include "pch.h"
#include "invoker.hpp"
#include "crossmap.hpp"
#include "hooking/hooks.hpp"

#include "types/script/scrProgram.hpp"

namespace MdayS
{
	void NativeInvoker::DefaultHandler(rage::scrNativeCallContext* ctx)
	{
		g_logger.insert(log_levels::RED_ERROR, "Native handler not registered");
		ctx->SetReturnValue(0);
	}

	void NativeInvoker::CacheHandlers()
	{
		if (m_AreHandlersCached)
			return;

		memcpy(m_Handlers.data(), g_crossmap.data(), sizeof(g_crossmap));
		auto program = reinterpret_cast<rage::scrProgram*>(calloc(1, sizeof(rage::scrProgram)));
		program->m_NativeCount = m_Handlers.size();
		program->m_NativeEntrypoints = m_Handlers.data();
		get_original<decltype(&hooks::init_native_tables)>("INT")(program);
		free(program);
		m_AreHandlersCached = true;
	}
}