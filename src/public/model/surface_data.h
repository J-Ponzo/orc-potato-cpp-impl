#ifndef ORC_POTATO_CPP_SURFACE_DATA_H
#define ORC_POTATO_CPP_SURFACE_DATA_H

#include <godot_cpp/variant/rid.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <secondary_data.h>

using namespace godot;

class ORC_PotatoCPP_MeshData;
class ORC_PotatoCPP_TopologyData;
class ORC_PotatoCPP_MaterialData;

class ORC_PotatoCPP_SurfaceData : public ORC_SecondaryData {
    GDCLASS(ORC_PotatoCPP_SurfaceData, ORC_SecondaryData)

protected:
    static void _bind_methods();

public:
    Ref<ORC_PotatoCPP_MeshData> mesh_data;
    Ref<ORC_PotatoCPP_TopologyData> topology_data;
    Ref<ORC_PotatoCPP_MaterialData> material_data;
    RID vertex_array;
};

#endif // ORC_POTATO_CPP_SURFACE_DATA_H
