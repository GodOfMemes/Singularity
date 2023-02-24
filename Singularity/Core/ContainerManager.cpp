#include "ContainerManager.h"

#include <random>

std::map<uint64_t,std::tuple<void*,int>> ContainerManager::_data = {};

std::random_device rd;
std::mt19937_64 eng(rd());
std::uniform_int_distribution<unsigned long long> dis;

uint64_t ContainerManager::create_container(void* data,int elementNum)
{
    uint64_t id = 0;
    do
    {
        id = dis(eng);
    }
    while (_data.contains(id) && id == 0);
    
    _data.insert({id,{data,elementNum}});
    return id;
}

void ContainerManager::get_container_data(uint64_t id,void** data,int* length)
{
    if(id == 0) return;
    
    if(_data.contains(id))
    {
        auto tup = _data[id];
        *data = tup._Myfirst._Val;
        *length = tup._Get_rest()._Myfirst._Val;
    }
    return;
}

void ContainerManager::update_container(uint64_t id, void* newData,int length)
{
    if(id == 0) return;
    
    if(_data.contains(id))
        _data[id] = {newData,length};
}

void ContainerManager::delete_container(uint64_t* id)
{
    if(id == nullptr || *id == 0) return;

    if(_data.contains(*id))
    {
        _data.erase(_data.find(*id));
        *id = 0;
    }
}

void ContainerManager::clear_container(uint64_t id)
{
    update_container(id,nullptr,-1);
}
