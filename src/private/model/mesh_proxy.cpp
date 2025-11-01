#include <mesh_proxy.h>
#include <mesh_data.h>
#include <godot_cpp/classes/node3d.hpp>
#include <potato_cpp_proxy_factory.h>

using namespace godot;

void ORC_PotatoCPP_MeshProxy::_bind_methods() {
}

void ORC_PotatoCPP_MeshProxy::update_impl() {
	Node3D* node3d = Object::cast_to<Node3D>(node);
	if (!node3d) {
		return;
	}

	Ref<ORC_PotatoCPP_MeshData> mesh_data = primary_data;
	if (!mesh_data.is_valid()) {
		return;
	}

	Transform3D global_transform = node3d->get_global_transform();
	if (global_transform_last_frame != global_transform) {
		mesh_data->model_matrix_bytes = ORC_PotatoCPPProxyFactory::proj_to_bytes(Projection(global_transform));
		global_transform_last_frame = global_transform;
	}
}
