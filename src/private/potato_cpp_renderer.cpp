#include <potato_cpp_renderer.h>
#include <render_pass_base.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void ORC_PotatoCPPRenderer::_bind_methods() {
}

void ORC_PotatoCPPRenderer::setup_impl() {
}

void ORC_PotatoCPPRenderer::pre_render_impl() {
	ORC_RendererBase::pre_render_impl();
	
	current_cam_data = Ref<ORC_PotatoCPP_CameraData>();
	TypedArray<ORC_ProxyData> cameras_data = scene_proxy->fetch_queue_data("cameras");
	for (int i = 0; i < cameras_data.size(); i++) {
		Ref<ORC_ProxyData> proxy_data = cameras_data[i];
		Ref<ORC_PotatoCPP_CameraData> camera_data = Object::cast_to<ORC_PotatoCPP_CameraData>(proxy_data.ptr());
		if (camera_data.is_valid() && camera_data->proxy_object.is_valid()) {
			Camera3D* cam_node = Object::cast_to<Camera3D>(camera_data->proxy_object->node);
			if (cam_node && cam_node->is_current()) {
				current_cam_data = camera_data;
				break;
			}
		}
	}
	
	surfaces_data.clear();
	TypedArray<ORC_ProxyData> surfaces_data_array = scene_proxy->fetch_queue_data("surfaces");
	for (int i = 0; i < surfaces_data_array.size(); i++) {
		Ref<ORC_ProxyData> proxy_data = surfaces_data_array[i];
		Ref<ORC_PotatoCPP_SurfaceData> surface_data = Object::cast_to<ORC_PotatoCPP_SurfaceData>(proxy_data.ptr());
		if (surface_data.is_valid()) {
			surfaces_data.append(surface_data);
		}
	}
}

void ORC_PotatoCPPRenderer::render_impl() {
    ((Ref<ORC_RenderPassBase>)render_passes["Single"])->render();
}

RID ORC_PotatoCPPRenderer::get_render_target_impl() {
	return attachments["Albedo"];
}

void ORC_PotatoCPPRenderer::cleanup_impl() {
}