#ifndef ORC_POTATO_CPP_PROXY_FACTORY_H
#define ORC_POTATO_CPP_PROXY_FACTORY_H

#include <proxy_factory.h>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/base_material3d.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/rendering_device.hpp>
#include <godot_cpp/classes/rd_vertex_attribute.hpp>
#include <camera_data.h>
#include <camera_proxy.h>
#include <mesh_data.h>
#include <mesh_proxy.h>
#include <surface_data.h>
#include <topology_data.h>
#include <material_data.h>

namespace godot {

class ORC_PotatoCPPProxyFactory : public ORC_ProxyFactory {
	GDCLASS(ORC_PotatoCPPProxyFactory, ORC_ProxyFactory)

protected:
	static void _bind_methods();

public:
	ORC_PotatoCPPProxyFactory() = default;
	~ORC_PotatoCPPProxyFactory() = default;

	Ref<ORC_ProxyObject> create_proxy_from_impl(Node* node) override;
	Ref<ORC_PrimaryData> create_data_from_impl(Node* node, const Ref<ORC_ProxyRegistry>& registry) override;
	bool free_proxy_impl(const Ref<ORC_ProxyObject>& proxy_object) override;
	bool free_data_impl(const Ref<ORC_ProxyData>& data, const Ref<ORC_ProxyRegistry>& registry) override;

	static PackedByteArray proj_to_bytes(const Projection& proj); // TODO implement this the c++ way

private:
	Ref<ORC_PotatoCPP_CameraData> create_camera_data_from(Camera3D* cam_node, const Ref<ORC_ProxyRegistry>& registry);
	Ref<ORC_PotatoCPP_MeshData> create_mesh_data_from(MeshInstance3D* mesh_node, const Ref<ORC_ProxyRegistry>& registry);
	Ref<ORC_PotatoCPP_SurfaceData> create_surface_data_from(const Ref<Mesh>& mesh, const Ref<ORC_PotatoCPP_MeshData>& mesh_data, int surface_index, const Ref<ORC_ProxyRegistry>& registry);
	Ref<ORC_PotatoCPP_TopologyData> create_topology_data_from(const Ref<Mesh>& mesh, const Ref<ORC_PotatoCPP_MeshData>& mesh_data, int surface_index, const Ref<ORC_ProxyRegistry>& registry);
	Ref<ORC_PotatoCPP_MaterialData> create_material_data_from(const Ref<BaseMaterial3D>& material, const Ref<ORC_PotatoCPP_MeshData>& mesh_data, const Ref<ORC_ProxyRegistry>& registry);

	bool free_camera_data(const Ref<ORC_PotatoCPP_CameraData>& cam_data, const Ref<ORC_ProxyRegistry>& registry);
	bool free_mesh_data(const Ref<ORC_PotatoCPP_MeshData>& mesh_data, const Ref<ORC_ProxyRegistry>& registry);
	bool free_surface_data(const Ref<ORC_PotatoCPP_SurfaceData>& surface_data, const Ref<ORC_ProxyRegistry>& registry);
	bool free_topology_data(const Ref<ORC_PotatoCPP_TopologyData>& topology_data, const Ref<ORC_ProxyRegistry>& registry);
	bool free_material_data(const Ref<ORC_PotatoCPP_MaterialData>& material_data, const Ref<ORC_ProxyRegistry>& registry);
};

}

#endif

