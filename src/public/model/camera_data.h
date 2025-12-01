#ifndef ORC_POTATO_CPP_CAMERA_DATA_H
#define ORC_POTATO_CPP_CAMERA_DATA_H

#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/variant/rid.hpp>
#include <primary_data.h>

using namespace godot;

class ORC_PotatoCPP_CameraData : public ORC_PrimaryData {
    GDCLASS(ORC_PotatoCPP_CameraData, ORC_PrimaryData)

protected:
    static void _bind_methods();

public:
    Transform3D view_transform;
    PackedByteArray view_matrix_bytes;
    PackedByteArray projection_matrix_bytes;
    RID matrices_uniform_buffer;
};

#endif // ORC_POTATO_CPP_CAMERA_DATA_H
