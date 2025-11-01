#ifndef ORC_POTATO_CPP_CAMERA_PROXY_H
#define ORC_POTATO_CPP_CAMERA_PROXY_H

#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/variant/projection.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <proxy_object.h>
#include <camera_data.h>

using namespace godot;

class ORC_PotatoCPP_CameraProxy : public ORC_ProxyObject {
    GDCLASS(ORC_PotatoCPP_CameraProxy, ORC_ProxyObject)

protected:
    static void _bind_methods();

public:
    Transform3D cam_transform_last_frame;
    Projection cam_proj_last_frame;

    void update_impl() override;
};

#endif // ORC_POTATO_CPP_CAMERA_PROXY_H
