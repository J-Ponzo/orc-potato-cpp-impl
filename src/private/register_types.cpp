#include <register_types.h>

#include <potato_cpp_renderer.h>
#include <potato_cpp_scene_proxy.h>

#include <impl_registry.h>
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_potato_cpp_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_RUNTIME_CLASS(ORC_PotatoCPPRenderer);
	GDREGISTER_RUNTIME_CLASS(ORC_PotatoCPPSceneProxy);
}

void uninitialize_potato_cpp_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

ORC_REGISTER_IMPL_MODULE("potato-cpp", initialize_potato_cpp_module, uninitialize_potato_cpp_module);