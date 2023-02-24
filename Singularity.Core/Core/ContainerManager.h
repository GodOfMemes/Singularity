#pragma once

#include <map>
#include "../Defines.h"

// TODO use guid/uuid instead of uint
class ContainerManager
{
public:
    static unsigned int create_global_container(void* data,int elementNum);
    static void get_container_data(unsigned int id,void** data,int* length);
    static void update_container(unsigned int id, void* newData,int length);
    static void delete_container(unsigned int* id);
    static void clear_container(unsigned int id);
private:
    static std::map<unsigned int,std::tuple<void*,unsigned int>> _data;
};

SAPI inline unsigned int CreateGlobalContainer(void* data,int elementNum)
{
    return ContainerManager::create_global_container(data,elementNum);
}

SAPI inline void GetContainerData(unsigned int id,void** data,int* length)
{
    ContainerManager::get_container_data(id,data,length);
}

SAPI inline void UpdateContainer(unsigned int id, void* newData,int length)
{
    ContainerManager::update_container(id,newData,length);
}