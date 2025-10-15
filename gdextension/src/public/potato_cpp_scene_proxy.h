#ifndef ORC_POTATO_CPP_SCENEPROXY_H
#define ORC_POTATO_CPP_SCENEPROXY_H

#include <scene_proxy_base.h>

namespace godot {

class ORC_PotatoCPPSceneProxy : public ORC_SceneProxyBase {
	GDCLASS(ORC_PotatoCPPSceneProxy, ORC_SceneProxyBase)

protected:
	static void _bind_methods();

public:
	ORC_PotatoCPPSceneProxy() = default;
	~ORC_PotatoCPPSceneProxy() = default;
};

}

#endif