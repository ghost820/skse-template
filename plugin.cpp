std::uint32_t TestPapyrusFunction(RE::StaticFunctionTag*, RE::TESObjectREFR* ref) { return 0; }

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);

    SKSE::GetPapyrusInterface()->Register([](RE::BSScript::IVirtualMachine* vm) {
        vm->RegisterFunction("TestPapyrusFunction", "ScriptFileNameWithoutExt", TestPapyrusFunction);

        return true;
    });

    return true;
}
