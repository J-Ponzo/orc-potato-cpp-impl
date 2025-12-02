#include <potato_cpp_proxy_factory.h>
#include <godot_cpp/classes/rendering_device.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <camera_proxy.h>
#include <mesh_proxy.h>
#include <rd_helper.h>

using namespace godot;

void ORC_PotatoCPPProxyFactory::_bind_methods() {
}

Ref<ORC_ProxyObject> ORC_PotatoCPPProxyFactory::create_proxy_from_impl(Node* node) {
	Ref<ORC_ProxyObject> proxy_object;
	
	if (Object::cast_to<Camera3D>(node)) {
		Ref<ORC_PotatoCPP_CameraProxy> cam_proxy;
		cam_proxy.instantiate();
		proxy_object = cam_proxy;
	} else if (Object::cast_to<MeshInstance3D>(node)) {
		Ref<ORC_PotatoCPP_MeshProxy> mesh_proxy;
		mesh_proxy.instantiate();
		proxy_object = mesh_proxy;
	}
	
	return proxy_object;
}

Ref<ORC_PrimaryData> ORC_PotatoCPPProxyFactory::create_data_from_impl(Node* node, const Ref<ORC_ProxyRegistry>& registry) {
	Ref<ORC_PrimaryData> primary_data;
	
	if (Camera3D* cam_node = Object::cast_to<Camera3D>(node)) {
		primary_data = create_camera_data_from(cam_node, registry);
	} else if (MeshInstance3D* mesh_node = Object::cast_to<MeshInstance3D>(node)) {
		primary_data = create_mesh_data_from(mesh_node, registry);
	}
	
	return primary_data;
}

bool ORC_PotatoCPPProxyFactory::free_proxy_impl(const Ref<ORC_ProxyObject>& proxy_object) {
	return true;
}

bool ORC_PotatoCPPProxyFactory::free_data_impl(const Ref<ORC_ProxyData>& data, const Ref<ORC_ProxyRegistry>& registry) {
	if (!data.is_valid()) {
		return false;
	}
	
	Ref<ORC_PotatoCPP_CameraData> cam_data = data;
	if (cam_data.is_valid()) {
		return free_camera_data(cam_data, registry);
	}
	
	Ref<ORC_PotatoCPP_MeshData> mesh_data = data;
	if (mesh_data.is_valid()) {
		return free_mesh_data(mesh_data, registry);
	}
	
	Ref<ORC_PotatoCPP_SurfaceData> surface_data = data;
	if (surface_data.is_valid()) {
		return free_surface_data(surface_data, registry);
	}
	
	Ref<ORC_PotatoCPP_TopologyData> topology_data = data;
	if (topology_data.is_valid()) {
		return free_topology_data(topology_data, registry);
	}
	
	Ref<ORC_PotatoCPP_MaterialData> material_data = data;
	if (material_data.is_valid()) {
		return free_material_data(material_data, registry);
	}
	
	return false;
}

Ref<ORC_PotatoCPP_CameraData> ORC_PotatoCPPProxyFactory::create_camera_data_from(Camera3D* cam_node, const Ref<ORC_ProxyRegistry>& registry) {
	Ref<ORC_PotatoCPP_CameraData> cam_data = create_and_register_primary<ORC_PotatoCPP_CameraData>(registry);
	
	cam_data->view_transform = cam_node->get_camera_transform().affine_inverse();
	cam_data->view_matrix_bytes = proj_to_bytes(Projection(cam_data->view_transform));
	cam_data->projection_matrix_bytes = proj_to_bytes(cam_node->get_camera_projection().flipped_y());

	PackedByteArray bytes = cam_data->view_matrix_bytes;
	bytes.append_array(cam_data->projection_matrix_bytes);

	cam_data->matrices_uniform_buffer = ORC_RDHelper::get_rd()->uniform_buffer_create(bytes.size(), bytes);
	
	return cam_data;
}

Ref<ORC_PotatoCPP_MeshData> ORC_PotatoCPPProxyFactory::create_mesh_data_from(MeshInstance3D* mesh_node, const Ref<ORC_ProxyRegistry>& registry) {
	Ref<ORC_PotatoCPP_MeshData> mesh_data = create_and_register_primary<ORC_PotatoCPP_MeshData>(registry);
	mesh_data->model_matrix_bytes = proj_to_bytes(Projection(mesh_node->get_global_transform()));

	Ref<Mesh> mesh = mesh_node->get_mesh();
	if (mesh.is_valid()) {
		for (int i = 0; i < mesh->get_surface_count(); i++) {
			Ref<ORC_PotatoCPP_SurfaceData> surface_data = create_surface_data_from(mesh, mesh_data, i, registry);
			mesh_data->surfaces_data.append(surface_data);
		}
	}

	return mesh_data;
}

Ref<ORC_PotatoCPP_SurfaceData> ORC_PotatoCPPProxyFactory::create_surface_data_from(const Ref<Mesh>& mesh, const Ref<ORC_PotatoCPP_MeshData>& mesh_data, int surface_index, const Ref<ORC_ProxyRegistry>& registry) {
	Ref<ORC_PotatoCPP_SurfaceData> surface_data = create_and_register_secondary<ORC_PotatoCPP_SurfaceData>(registry, mesh_data);
	surface_data->mesh_data = mesh_data;
	surface_data->topology_data = create_topology_data_from(mesh, mesh_data, surface_index, registry);
	
	Ref<BaseMaterial3D> material = mesh->surface_get_material(surface_index);
	surface_data->material_data = create_material_data_from(material, mesh_data, registry);

	Ref<ORC_VertexFormatInfo> vf_info = memnew(ORC_VertexFormatInfo);
	int64_t vf = ORC_RDHelper::create_vertex_format(vf_info);
	surface_data->vertex_array = ORC_RDHelper::get_rd()->vertex_array_create(
		surface_data->topology_data->vertex_count,
		vf,
		Array::make(surface_data->topology_data->position_buffer)
	);

	return surface_data;
}

Ref<ORC_PotatoCPP_TopologyData> ORC_PotatoCPPProxyFactory::create_topology_data_from(const Ref<Mesh>& mesh, const Ref<ORC_PotatoCPP_MeshData>& mesh_data, int surface_index, const Ref<ORC_ProxyRegistry>& registry) {
	int64_t unique_id = mesh->get_instance_id();
	Ref<ORC_PotatoCPP_TopologyData> topology_data = create_and_register_secondary<ORC_PotatoCPP_TopologyData>(registry, mesh_data, unique_id);
	topology_data->unique_id = mesh->get_instance_id();

	Array arrays = mesh->surface_get_arrays(surface_index);
	PackedInt32Array indices = arrays[Mesh::ARRAY_INDEX];
	topology_data->index_count = indices.size();
	
	PackedByteArray byte_array = indices.to_byte_array();
	topology_data->index_buffer = ORC_RDHelper::get_rd()->index_buffer_create(indices.size(), RenderingDevice::INDEX_BUFFER_FORMAT_UINT32, byte_array);
	topology_data->index_array = ORC_RDHelper::get_rd()->index_array_create(topology_data->index_buffer, 0, topology_data->index_count);

	PackedVector3Array vertices = arrays[Mesh::ARRAY_VERTEX];
	topology_data->vertex_count = vertices.size();
	byte_array = vertices.to_byte_array();
	topology_data->position_buffer = ORC_RDHelper::get_rd()->vertex_buffer_create(byte_array.size(), byte_array);

	return topology_data;
}

Ref<ORC_PotatoCPP_MaterialData> ORC_PotatoCPPProxyFactory::create_material_data_from(const Ref<BaseMaterial3D>& material, const Ref<ORC_PotatoCPP_MeshData>& mesh_data, const Ref<ORC_ProxyRegistry>& registry) {
	int64_t unique_id = material.is_valid() ? material->get_instance_id() : -1;
	Ref<ORC_PotatoCPP_MaterialData> material_data = create_and_register_secondary<ORC_PotatoCPP_MaterialData>(registry, mesh_data, unique_id);
	
	if (material.is_valid()) {
		material_data->unique_id = material->get_instance_id();
		
		Color albedo = material->get_albedo();
		PackedFloat32Array albedo_floats;
		albedo_floats.append(albedo.r);
		albedo_floats.append(albedo.g);
		albedo_floats.append(albedo.b);
		albedo_floats.append(albedo.a);
		
		PackedByteArray bytes = albedo_floats.to_byte_array();
		material_data->albedo_buffer = ORC_RDHelper::get_rd()->uniform_buffer_create(bytes.size(), bytes);
	}

	return material_data;
}

bool ORC_PotatoCPPProxyFactory::free_camera_data(const Ref<ORC_PotatoCPP_CameraData>& cam_data, const Ref<ORC_ProxyRegistry>& registry) {
	if (cam_data->matrices_uniform_buffer.is_valid()) {
		ORC_RDHelper::get_rd()->free_rid(cam_data->matrices_uniform_buffer);
		cam_data->matrices_uniform_buffer = RID();
	}
	
	return registry->unregister_data(cam_data);
}

bool ORC_PotatoCPPProxyFactory::free_mesh_data(const Ref<ORC_PotatoCPP_MeshData>& mesh_data, const Ref<ORC_ProxyRegistry>& registry) {
	return registry->unregister_data(mesh_data);
}

bool ORC_PotatoCPPProxyFactory::free_surface_data(const Ref<ORC_PotatoCPP_SurfaceData>& surface_data, const Ref<ORC_ProxyRegistry>& registry) {
	return registry->unregister_data(surface_data);
}

bool ORC_PotatoCPPProxyFactory::free_topology_data(const Ref<ORC_PotatoCPP_TopologyData>& topology_data, const Ref<ORC_ProxyRegistry>& registry) {
	if (topology_data->index_array.is_valid()) {
		ORC_RDHelper::get_rd()->free_rid(topology_data->index_array);
		topology_data->index_array = RID();
	}
	if (topology_data->index_buffer.is_valid()) {
		ORC_RDHelper::get_rd()->free_rid(topology_data->index_buffer);
		topology_data->index_buffer = RID();
	}
	if (topology_data->position_buffer.is_valid()) {
		ORC_RDHelper::get_rd()->free_rid(topology_data->position_buffer);
		topology_data->position_buffer = RID();
	}
	
	return registry->unregister_data(topology_data);
}

bool ORC_PotatoCPPProxyFactory::free_material_data(const Ref<ORC_PotatoCPP_MaterialData>& material_data, const Ref<ORC_ProxyRegistry>& registry) {
	if (material_data->albedo_buffer.is_valid()) {
		ORC_RDHelper::get_rd()->free_rid(material_data->albedo_buffer);
		material_data->albedo_buffer = RID();
	}
	
	return registry->unregister_data(material_data);
}

PackedByteArray ORC_PotatoCPPProxyFactory::proj_to_bytes(const Projection& proj) {
	const int SIZEOF_MAT4 = 64;
	PackedByteArray byte_array;
	byte_array.resize(SIZEOF_MAT4);
	
	int offset = 0;
	for (int i = 0; i < 4; i++) {
		Vector4 column = proj.columns[i];
		byte_array.encode_float(offset, column.x);
		offset += 4;
		byte_array.encode_float(offset, column.y);
		offset += 4;
		byte_array.encode_float(offset, column.z);
		offset += 4;
		byte_array.encode_float(offset, column.w);
		offset += 4;
	}
	
	return byte_array;
}


