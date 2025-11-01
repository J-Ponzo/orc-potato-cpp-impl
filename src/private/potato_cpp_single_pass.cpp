#include <potato_cpp_single_pass.h>
#include <godot_cpp/variant/utility_functions.hpp>
#include <pso.h>
#include <potato_cpp_renderer.h>

using namespace godot;

void ORC_PotatoCPPSinglePass::_bind_methods() {
}

ORC_PotatoCPPSinglePass::ORC_PotatoCPPSinglePass() {
}

ORC_PotatoCPPSinglePass::~ORC_PotatoCPPSinglePass() {
}

void ORC_PotatoCPPSinglePass::setup_impl() {
	setup();
	UtilityFunctions::print("ORC_PotatoCPPSinglePass.setup()");
}

void ORC_PotatoCPPSinglePass::render_impl() {
	RenderingDevice* rd = RenderingServer::get_singleton()->get_rendering_device();
	
	Ref<ORC_PotatoCPPRenderer> potato_renderer = renderer;

	// Create matrices uniform
	Ref<RDUniform> matrices_uniform;
	matrices_uniform.instantiate();
	matrices_uniform->set_uniform_type(RenderingDevice::UNIFORM_TYPE_UNIFORM_BUFFER);
	matrices_uniform->set_binding(0);
	matrices_uniform->add_id(potato_renderer->current_cam_data->matrices_uniform_buffer);

	// Get PSO from dictionary
	Ref<ORC_PSO> potato_pso = explicits_pso["Potato_PSO"];
	RID matrices_uniform_set = rd->uniform_set_create(Array::make(matrices_uniform), potato_pso->shader_program, 0);

	// Begin draw list
	PackedColorArray clear_colors;
	clear_colors.append(Color(0.0, 0.0, 0.0));
	int64_t draw_flags = RenderingDevice::DRAW_CLEAR_ALL;
	int64_t draw_list = rd->draw_list_begin(framebuffer, draw_flags, clear_colors);

	// Bind matrices uniform set and pipeline
	rd->draw_list_bind_uniform_set(draw_list, matrices_uniform_set, 0);
	rd->draw_list_bind_render_pipeline(draw_list, potato_pso->pipeline);

	// Draw each surface
	for (int i = 0; i < potato_renderer->surfaces_data.size(); i++) {
		Ref<ORC_PotatoCPP_SurfaceData> surface_data = potato_renderer->surfaces_data[i];
		
		// Create albedo uniform
		Ref<RDUniform> albedo_uniform;
		albedo_uniform.instantiate();
		albedo_uniform->set_uniform_type(RenderingDevice::UNIFORM_TYPE_UNIFORM_BUFFER);
		albedo_uniform->set_binding(0);
		albedo_uniform->add_id(surface_data->material_data->albedo_buffer);

		RID albedo_uniform_set = rd->uniform_set_create(Array::make(albedo_uniform), potato_pso->shader_program, 1);

		// Bind uniform set, vertex and index arrays
		rd->draw_list_bind_uniform_set(draw_list, albedo_uniform_set, 1);
		rd->draw_list_bind_vertex_array(draw_list, surface_data->vertex_array);
		rd->draw_list_bind_index_array(draw_list, surface_data->topology_data->index_array);
		
		// Set push constant and draw
		rd->draw_list_set_push_constant(draw_list, surface_data->mesh_data->model_matrix_bytes, surface_data->mesh_data->model_matrix_bytes.size());
		rd->draw_list_draw(draw_list, true, 1, 0);

		// Free albedo uniform set
		rd->free_rid(albedo_uniform_set);
	}

	// End draw list
	rd->draw_list_end();

	// Free matrices uniform set
	rd->free_rid(matrices_uniform_set);
}

void ORC_PotatoCPPSinglePass::cleanup_impl() {
	cleanup();
	UtilityFunctions::print("ORC_PotatoCPPSinglePass.cleanup()");
}
