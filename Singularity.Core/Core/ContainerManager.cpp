#include "ContainerManager.h"

#include <ctime>

std::map<unsigned int,std::tuple<void*,unsigned int>> ContainerManager::_data = {};

unsigned int ContainerManager::create_global_container(void* data,int elementNum)
{
    srand(static_cast<unsigned>(time(nullptr)));
    
    unsigned int id = rand();
    while(_data.contains(id) && id == 0)
    {
        id = rand();
    }

    _data.insert({id,{data,elementNum}});
    return id;
}

void ContainerManager::get_container_data(unsigned int id,void** data,int* length)
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

void ContainerManager::update_container(unsigned int id, void* newData,int length)
{
    if(id == 0) return;
    
    if(_data.contains(id))
        _data[id] = {newData,length};
}

void ContainerManager::delete_container(unsigned int* id)
{
    if(id == 0) return;

    if(_data.contains(*id))
    {
        _data.erase(_data.find(*id));
        *id = 0;
    }
}

void ContainerManager::clear_container(unsigned id)
{
    update_container(id,nullptr,-1);
}
