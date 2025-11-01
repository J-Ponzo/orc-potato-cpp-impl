#ifndef ORC_POTATO_CPP_SINGLE_PASS_H
#define ORC_POTATO_CPP_SINGLE_PASS_H

#include <render_pass_base.h>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/rendering_device.hpp>
#include <godot_cpp/classes/rd_uniform.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/packed_color_array.hpp>
#include <camera_data.h>
#include <mesh_data.h>
#include <surface_data.h>
#include <topology_data.h>
#include <material_data.h>

using namespace godot;

class ORC_PotatoCPPSinglePass : public ORC_RenderPassBase {
	GDCLASS(ORC_PotatoCPPSinglePass, ORC_RenderPassBase)

protected:
	static void _bind_methods();

public:
	ORC_PotatoCPPSinglePass();
	~ORC_PotatoCPPSinglePass();

	void setup_impl() override;
	void render_impl() override;
	void cleanup_impl() override;
};

#endif
