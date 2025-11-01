#ifndef ORC_POTATO_CPP_MATERIAL_DATA_H
#define ORC_POTATO_CPP_MATERIAL_DATA_H

#include <godot_cpp/variant/rid.hpp>
#include <secondary_data.h>

using namespace godot;

class ORC_PotatoCPP_MaterialData : public ORC_SecondaryData {
    GDCLASS(ORC_PotatoCPP_MaterialData, ORC_SecondaryData)

protected:
    static void _bind_methods();

public:
    int unique_id = 0;
    RID albedo_buffer;
};

#endif // ORC_POTATO_CPP_MATERIAL_DATA_H
