#include <register_types.h>

#include <potato_cpp_renderer.h>
#include <potato_cpp_proxy_factory.h>
#include <potato_cpp_single_pass.h>

#include <camera_data.h>
#include <mesh_data.h>
#include <material_data.h>
#include <topology_data.h>
#include <surface_data.h>
#include <camera_proxy.h>
#include <mesh_proxy.h>

#include <impl_registry.h>
#include <proxy_registry.h>
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_potato_cpp_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_RUNTIME_CLASS(ORC_PotatoCPPRenderer);
	GDREGISTER_RUNTIME_CLASS(ORC_PotatoCPPProxyFactory);
	GDREGISTER_RUNTIME_CLASS(ORC_PotatoCPPSinglePass);
	
	GDREGISTER_RUNTIME_CLASS(ORC_PotatoCPP_CameraProxy);
	GDREGISTER_RUNTIME_CLASS(ORC_PotatoCPP_MeshProxy);

	ORC_REGISTER_PROXY_DATA_TYPE(ORC_PotatoCPP_CameraData);
	ORC_REGISTER_PROXY_DATA_TYPE(ORC_PotatoCPP_MeshData);
	ORC_REGISTER_PROXY_DATA_TYPE(ORC_PotatoCPP_MaterialData);
	ORC_REGISTER_PROXY_DATA_TYPE(ORC_PotatoCPP_TopologyData);
	ORC_REGISTER_PROXY_DATA_TYPE(ORC_PotatoCPP_SurfaceData);
}

void uninitialize_potato_cpp_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

ORC_REGISTER_IMPL_MODULE("potato-cpp", initialize_potato_cpp_module, uninitialize_potato_cpp_module);