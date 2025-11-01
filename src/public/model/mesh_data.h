#ifndef ORC_POTATO_CPP_MESH_DATA_H
#define ORC_POTATO_CPP_MESH_DATA_H

#include <godot_cpp/variant/packed_byte_array.hpp>
#include <vector>

using namespace godot;

struct ORC_PotatoCPP_SurfaceData;

struct ORC_PotatoCPP_MeshData {
    std::vector<ORC_PotatoCPP_SurfaceData*> surfaces_data;
    PackedByteArray model_matrix_bytes;
};

#endif // ORC_POTATO_CPP_MESH_DATA_H
