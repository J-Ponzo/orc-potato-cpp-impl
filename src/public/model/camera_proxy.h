#ifndef ORC_POTATO_CPP_CAMERA_PROXY_H
#define ORC_POTATO_CPP_CAMERA_PROXY_H

#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/variant/projection.hpp>

using namespace godot;

struct ORC_PotatoCPP_CameraData;

struct ORC_PotatoCPP_CameraProxy {
    Transform3D cam_transform_last_frame;
    Projection cam_proj_last_frame;
    ORC_PotatoCPP_CameraData* primary_data = nullptr;

    void update();
};

#endif // ORC_POTATO_CPP_CAMERA_PROXY_H
