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
	std::vector<Ref<ORC_PotatoCPP_CameraData>> cameras_data = scene_proxy->get_by_type<ORC_PotatoCPP_CameraData>();
	for (const auto& camera_data : cameras_data) {
		if (camera_data.is_valid() && camera_data->proxy_object.is_valid()) {
			Camera3D* cam_node = Object::cast_to<Camera3D>(camera_data->proxy_object->node);
			if (cam_node && cam_node->is_current()) {
				current_cam_data = camera_data;
				break;
			}
		}
	}
	
	surfaces_data.clear();
	std::vector<Ref<ORC_PotatoCPP_SurfaceData>> non_casted_surfaces_data = scene_proxy->get_by_type<ORC_PotatoCPP_SurfaceData>();
	for (const auto& surface_data : non_casted_surfaces_data) {
		if (surface_data.is_valid()) {
			surfaces_data.append(surface_data);
		}
	}
}

void ORC_PotatoCPPRenderer::render_impl() {
    ((Ref<ORC_RenderPassBase>)render_passes["Single"])->render();
}

RID ORC_PotatoCPPRenderer::get_render_target_impl() {
    UtilityFunctions::print(scene_proxy->dump_registry());
	return attachments["Albedo"];
}

void ORC_PotatoCPPRenderer::cleanup_impl() {
}