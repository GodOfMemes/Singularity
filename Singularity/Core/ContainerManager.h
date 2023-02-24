#pragma once

#include <map>
#include "../Defines.h"

// TODO use guid/uuid instead of uint
class ContainerManager
{
public:
    static uint64_t create_container(void* data,int elementNum);
    static void get_container_data(uint64_t id,void** data,int* length);
    static void update_container(uint64_t id, void* newData,int length);
    static void delete_container(uint64_t* id);
    static void clear_container(uint64_t id);
private:
    static std::map<uint64_t,std::tuple<void*,int>> _data;
};

SAPI inline uint64_t CreateContainer(void* data,int elementNum)
{
    return ContainerManager::create_container(data,elementNum);
}

SAPI inline void GetContainerData(uint64_t id,void** data,int* length)
{
    ContainerManager::get_container_data(id,data,length);
}

SAPI inline void UpdateContainer(uint64_t id, void* newData,int length)
{
    ContainerManager::update_container(id,newData,length);
}

SAPI inline void DeleteContainer(uint64_t* id)
{
    ContainerManager::delete_container(id);
}

SAPI inline void ClearContainer(uint64_t id)
{
    ContainerManager::clear_container(id);
}