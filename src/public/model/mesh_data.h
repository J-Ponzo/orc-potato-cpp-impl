#ifndef ORC_POTATO_CPP_MESH_DATA_H
#define ORC_POTATO_CPP_MESH_DATA_H

#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <primary_data.h>

using namespace godot;

class ORC_PotatoCPP_SurfaceData;

class ORC_PotatoCPP_MeshData : public ORC_PrimaryData {
    GDCLASS(ORC_PotatoCPP_MeshData, ORC_PrimaryData)

protected:
    static void _bind_methods();

public:
    TypedArray<ORC_PotatoCPP_SurfaceData> surfaces_data;
    PackedByteArray model_matrix_bytes;
};

#endif // ORC_POTATO_CPP_MESH_DATA_H
