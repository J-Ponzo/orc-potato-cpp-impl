#ifndef ORC_POTATO_CPP_MATERIAL_DATA_H
#define ORC_POTATO_CPP_MATERIAL_DATA_H

#include <godot_cpp/variant/rid.hpp>

using namespace godot;

struct ORC_PotatoCPP_MaterialData {
    int unique_id = 0;
    RID albedo_buffer;
};

#endif // ORC_POTATO_CPP_MATERIAL_DATA_H
