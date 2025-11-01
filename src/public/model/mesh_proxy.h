#ifndef ORC_POTATO_CPP_MESH_PROXY_H
#define ORC_POTATO_CPP_MESH_PROXY_H

#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <proxy_object.h>
#include <mesh_data.h>

using namespace godot;

class ORC_PotatoCPP_MeshProxy : public ORC_ProxyObject {
    GDCLASS(ORC_PotatoCPP_MeshProxy, ORC_ProxyObject)

protected:
    static void _bind_methods();

public:
    Transform3D global_transform_last_frame;

    void update_impl() override;
};

#endif // ORC_POTATO_CPP_MESH_PROXY_H
