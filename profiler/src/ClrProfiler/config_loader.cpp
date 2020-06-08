#include "config_loader.h"
#include "util.h"
#include "json.hpp"
#include <fstream>

namespace trace
{
    using json = nlohmann::json;

    std::pair<TraceAssembly, bool> TraceAssemblyFromJson(const json::value_type& src) {
        if (!src.is_object()) {
            return std::make_pair<TraceAssembly, bool>({}, false);
        }
        const auto assemblyName = ToWSTRING(src.value("assemblyName", ""));
        const auto className = ToWSTRING(src.value("className", ""));

        if(assemblyName.empty() || className.empty()){
            return std::make_pair<TraceAssembly, bool>({}, false);
        }

        std::vector<TraceMethod> traceMethods;
        auto arr = src.value("methods", json::array());
        if (arr.is_array()) {
            for (auto& el : arr) {
                const auto methodName = ToWSTRING(el.value("methodName", ""));
                const auto paramsName = ToWSTRING(el.value("paramsName", ""));
                if (methodName.empty()) {
                    continue;
                }
                traceMethods.push_back(TraceMethod{ methodName,paramsName });
            }
        }
        if(traceMethods.empty()) {
            return std::make_pair<TraceAssembly, bool>({}, false);
        }
        return std::make_pair<TraceAssembly, bool>({ assemblyName, className, traceMethods }, true);
    }

    ManagedAssembly LoadManagedAssembly(const json::value_type& src)
    {
        ManagedAssembly managedAssembly;
        const auto publicKey = src.value("publicKey", "");
        const auto version = ToWSTRING(src.value("version", "1.0.0.0"));
        managedAssembly.publicKey = HexToBytes(publicKey);

        const auto assembly_version = Version(Split(version, static_cast<wchar_t>('.')));

        ASSEMBLYMETADATA assemblyMetaData;
        ZeroMemory(&assemblyMetaData, sizeof(assemblyMetaData));
        assemblyMetaData.usMajorVersion = assembly_version.major;
        assemblyMetaData.usMinorVersion = assembly_version.minor;
        assemblyMetaData.usBuildNumber = assembly_version.build;
        assemblyMetaData.usRevisionNumber = assembly_version.revision;
        managedAssembly.assemblyMetaData = assemblyMetaData;
        return managedAssembly;
    }

    TraceConfig LoadTraceConfigFromStream(std::istream& stream) {
        TraceConfig traceConfig;
        std::vector<TraceAssembly> traceAssemblies;
        ManagedAssembly managedAssembly;
        try {
            json j;
            // parse the stream
            stream >> j;

            for (auto& el : j["instrumentation"]) {
                auto i = TraceAssemblyFromJson(el);
                if (std::get<1>(i)) {
                    traceAssemblies.push_back(std::get<0>(i));
                }
            }
            managedAssembly = LoadManagedAssembly(j["managedAssembly"]);
        }
        catch (const json::parse_error& e) {
            //Warn("Invalid TraceAssemblies: {}", e.what());
            printf("toto\n");
        }
        catch (const json::type_error& e) {
            //Warn("Invalid TraceAssemblies: {}", e.what());
            printf("titi\n");
        }
        catch (...) {
            const auto ex = std::current_exception();
            try {
                if (ex) {
                    std::rethrow_exception(ex);
                }
            }
            catch (const std::exception& ex0) {
                //Warn("Failed to load TraceAssemblies: {}", ex0.what());
                printf("tata\n");
            }
        }
        traceConfig.traceAssemblies = traceAssemblies;
        traceConfig.managedAssembly = managedAssembly;
        return traceConfig;
    }

    TraceConfig LoadTraceConfig(const WSTRING& traceHomePath)
    {
        const auto traceJsonFilePath = traceHomePath + PathSeparator + "trace.json"_W;
        TraceConfig config;
        try {
            std::ifstream stream;
            stream.open(ToString(traceJsonFilePath));
            config = LoadTraceConfigFromStream(stream);
            stream.close();
        }
        catch (...) {
            const auto ex = std::current_exception();
            try {
                if (ex) {
                    std::rethrow_exception(ex);
                }
            }
            catch (const std::exception& ex0) {
                //Warn("Failed to load TraceAssemblies:{}", ex0.what());
                printf("Failed to load TraceAssemblies");
            }
        }
        return config;
    }
}
