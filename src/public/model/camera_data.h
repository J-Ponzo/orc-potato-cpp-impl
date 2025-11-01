#ifndef ORC_POTATO_CPP_CAMERA_DATA_H
#define ORC_POTATO_CPP_CAMERA_DATA_H

#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/variant/rid.hpp>

using namespace godot;

struct ORC_PotatoCPP_CameraData {
    Transform3D view_transform;
    PackedByteArray view_matrix_bytes;
    PackedByteArray projection_matrix_bytes;
    RID matrices_uniform_buffer;
};

#endif // ORC_POTATO_CPP_CAMERA_DATA_H
