#include "header.hpp"

void save_modules(const ModuleList& modules, Serial& ar) {
    for (const auto* mod : modules) {
        ar(mod->name);
        size_t size = mod->variables.size();
        ar(size);
        for (const auto& var : mod->variables) {
            ar(var.first);
            ar(var.second.addr);
        }
    }
    ar(std::string{});
}

namespace orig {
long long run(long long iterations) {
    ModuleList mods;
    mods.reserve(1000);
    std::vector<std::string> moduleNames;
    moduleNames.reserve(1000);
    for (int i = 0; i < 1000; i++) {
        moduleNames.emplace_back("module_" + std::to_string(i));
    }
    for (int i = 0; i < 1000; i++) {
        auto* m = new Module{moduleNames[i], {}};
        if (i == 0 || i % 10 == 0) {
            m->variables.emplace_back(i, VariableEntry{i, i * 2});
        }
        mods.push_back(m);
    }
    Serial ar;
    ar.buffer.reserve(1024);
    long long dummy = 0;
    for (long long r = 0; r < iterations; r++) {
        ar.clear();
        save_modules(mods, ar);
        if (!ar.buffer.empty()) dummy += ar.buffer[0];
    }
    for (auto m : mods) delete m;
    return dummy;
}
}

long long run(long long iters) {
    return orig::run(iters);
}

// Explicit template instantiations if any
