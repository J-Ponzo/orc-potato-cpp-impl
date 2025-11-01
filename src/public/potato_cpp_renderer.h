#ifndef ORC_POTATO_CPP_RENDERER_H
#define ORC_POTATO_CPP_RENDERER_H

#include <renderer_base.h>
#include <godot_cpp/variant/typed_array.hpp>
#include <camera_data.h>
#include <surface_data.h>

namespace godot {

class ORC_PotatoCPPRenderer : public ORC_RendererBase {
	GDCLASS(ORC_PotatoCPPRenderer, ORC_RendererBase)

protected:
	static void _bind_methods();

private:
	Ref<ORC_PotatoCPP_CameraData> current_cam_data;
	TypedArray<ORC_PotatoCPP_SurfaceData> surfaces_data;

public:
	ORC_PotatoCPPRenderer() = default;
	~ORC_PotatoCPPRenderer() = default;

	void setup_impl() override;
	void pre_render_impl() override;
	void render_impl() override;
	RID get_render_target_impl() override;
	void cleanup_impl() override;
};

}

#endif