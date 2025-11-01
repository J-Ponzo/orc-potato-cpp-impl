#ifndef ORC_POTATO_CPP_TOPOLOGY_DATA_H
#define ORC_POTATO_CPP_TOPOLOGY_DATA_H

#include <godot_cpp/variant/rid.hpp>

using namespace godot;

struct ORC_PotatoCPP_TopologyData {
    int unique_id = 0;
    int index_count = 0;
    RID index_buffer;
    RID index_array;
    int vertex_count = 0;
    RID position_buffer;
};

#endif // ORC_POTATO_CPP_TOPOLOGY_DATA_H
