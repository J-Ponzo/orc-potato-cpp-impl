#include <camera_proxy.h>
#include <camera_data.h>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/rendering_device.hpp>
#include <rd_helper.h>

using namespace godot;

void ORC_PotatoCPP_CameraProxy::_bind_methods() {
}

void ORC_PotatoCPP_CameraProxy::update_impl() {
	Camera3D* camera = Object::cast_to<Camera3D>(node);
	if (!camera) {
		return;
	}

	Ref<ORC_PotatoCPP_CameraData> cam_data = primary_data;
	if (!cam_data.is_valid()) {
		return;
	}

	Transform3D cam_transform = camera->get_camera_transform();
	Projection cam_proj = camera->get_camera_projection();
	
	bool has_changed = false;
	if (cam_transform_last_frame != cam_transform) {
		cam_data->view_transform = cam_transform.affine_inverse();
		cam_data->view_matrix_bytes = ORC_RDHelper::proj_to_bytes(Projection(cam_data->view_transform));
		cam_transform_last_frame = cam_transform;
		has_changed = true;
	}

	if (cam_proj_last_frame != cam_proj) {
		cam_data->projection_matrix_bytes = ORC_RDHelper::proj_to_bytes(cam_proj.flipped_y());
		cam_proj_last_frame = cam_proj;
		has_changed = true;
	}

	if (has_changed) {
		RenderingDevice* rd = RenderingServer::get_singleton()->get_rendering_device();
		rd->free_rid(cam_data->matrices_uniform_buffer);
		
		PackedByteArray bytes = cam_data->view_matrix_bytes;
		bytes.append_array(cam_data->projection_matrix_bytes);
		cam_data->matrices_uniform_buffer = rd->uniform_buffer_create(bytes.size(), bytes);
	}
}
