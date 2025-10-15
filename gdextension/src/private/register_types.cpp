#include "register_types.h"

#include "potato_cpp_renderer.h"
#include "potato_cpp_scene_proxy.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_orcpotatocppimpl_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_RUNTIME_CLASS(ORC_PotatoCPPRenderer);
	GDREGISTER_RUNTIME_CLASS(ORC_PotatoCPPSceneProxy);

	fprintf(stderr, ">>> [ORC] orcpotatocppimpl_library_init called\n");
	fflush(stderr);
}

void uninitialize_orcpotatocppimpl_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT orcpotatocppimpl_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_orcpotatocppimpl_module);
	init_obj.register_terminator(uninitialize_orcpotatocppimpl_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}