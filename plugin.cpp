#include <Windows.h>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/msvc_sink.h"

static bool InitializeLogger()
{
    auto logdir = SKSE::log::log_directory();
    if (!logdir) {
		return false;
    }
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    auto logpath = *logdir / std::format("{}.log", pluginName);
    if (IsDebuggerPresent()) {
        auto logger1 = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logpath.string(), false);
		auto logger2 = std::make_shared<spdlog::sinks::msvc_sink_mt>();
		spdlog::sinks_init_list loggers = { logger1, logger2 };
        auto logger = std::make_shared<spdlog::logger>("logger-main", loggers);
		spdlog::set_default_logger(logger);
    }
    else {
        auto logger = spdlog::basic_logger_mt("logger-main", logpath.string(), false);
        spdlog::set_default_logger(logger);
    }
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);
	return true;
}

std::uint32_t TestPapyrusFunction(RE::StaticFunctionTag*, RE::TESObjectREFR* ref) { return 0; }

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);

    InitializeLogger();

    SKSE::GetPapyrusInterface()->Register([](RE::BSScript::IVirtualMachine* vm) {
        vm->RegisterFunction("TestPapyrusFunction", "ScriptFileNameWithoutExt", TestPapyrusFunction);

        return true;
    });

    return true;
}
