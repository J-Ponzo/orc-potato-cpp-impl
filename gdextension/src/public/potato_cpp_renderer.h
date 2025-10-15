#ifndef ORC_POTATO_CPP_RENDERER_H
#define ORC_POTATO_CPP_RENDERER_H

#include <renderer_base.h>

namespace godot {

class ORC_PotatoCPPRenderer : public ORC_RendererBase {
	GDCLASS(ORC_PotatoCPPRenderer, ORC_RendererBase)

protected:
	static void _bind_methods();

public:
	ORC_PotatoCPPRenderer() = default;
	~ORC_PotatoCPPRenderer()  = default;
};

}

#endif