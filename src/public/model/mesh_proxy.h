#ifndef ORC_POTATO_CPP_MESH_PROXY_H
#define ORC_POTATO_CPP_MESH_PROXY_H

#include <godot_cpp/variant/transform3d.hpp>

using namespace godot;

struct ORC_PotatoCPP_MeshData;

struct ORC_PotatoCPP_MeshProxy {
    Transform3D global_transform_last_frame;
    ORC_PotatoCPP_MeshData* primary_data = nullptr;

    void update();
};

#endif // ORC_POTATO_CPP_MESH_PROXY_H
