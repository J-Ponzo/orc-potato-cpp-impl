#ifndef ORC_POTATO_CPP_TOPOLOGY_DATA_H
#define ORC_POTATO_CPP_TOPOLOGY_DATA_H

#include <godot_cpp/variant/rid.hpp>
#include <secondary_data.h>

using namespace godot;

class ORC_PotatoCPP_TopologyData : public ORC_SecondaryData {
    GDCLASS(ORC_PotatoCPP_TopologyData, ORC_SecondaryData)

protected:
    static void _bind_methods();

public:
    int unique_id = 0;
    int index_count = 0;
    RID index_buffer;
    RID index_array;
    int vertex_count = 0;
    RID position_buffer;
};

#endif // ORC_POTATO_CPP_TOPOLOGY_DATA_H
