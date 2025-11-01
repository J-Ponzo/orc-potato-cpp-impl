#ifndef ORC_POTATO_CPP_CAMERA_PROXY_H
#define ORC_POTATO_CPP_CAMERA_PROXY_H

#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/variant/projection.hpp>
#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class ORC_PotatoCPP_CameraData;

struct ORC_PotatoCPP_CameraProxy {
    Transform3D cam_transform_last_frame;
    Projection cam_proj_last_frame;
    Ref<ORC_PotatoCPP_CameraData> primary_data;

    void update();
};

#endif // ORC_POTATO_CPP_CAMERA_PROXY_H
