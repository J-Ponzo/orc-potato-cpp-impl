#ifndef ORC_POTATO_CPP_SURFACE_DATA_H
#define ORC_POTATO_CPP_SURFACE_DATA_H

#include <godot_cpp/variant/rid.hpp>

using namespace godot;

struct ORC_PotatoCPP_MeshData;
struct ORC_PotatoCPP_TopologyData;
struct ORC_PotatoCPP_MaterialData;

struct ORC_PotatoCPP_SurfaceData {
    ORC_PotatoCPP_MeshData* mesh_data = nullptr;
    ORC_PotatoCPP_TopologyData* topology_data = nullptr;
    ORC_PotatoCPP_MaterialData* material_data = nullptr;
    RID vertex_array;
};

#endif // ORC_POTATO_CPP_SURFACE_DATA_H
