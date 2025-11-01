#include <potato_cpp_renderer.h>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void ORC_PotatoCPPRenderer::_bind_methods() {
}

void ORC_PotatoCPPRenderer::setup_impl() {
}

void ORC_PotatoCPPRenderer::pre_render_impl() {
	ORC_RendererBase::pre_render_impl();
	
	current_cam_data = Ref<ORC_PotatoCPP_CameraData>();
	surfaces_data.clear();
}

void ORC_PotatoCPPRenderer::render_impl() {
}

RID ORC_PotatoCPPRenderer::get_render_target_impl() {
     UtilityFunctions::print(scene_proxy->dump_cache());
	return attachments["Albedo"];
}

void ORC_PotatoCPPRenderer::cleanup_impl() {
}