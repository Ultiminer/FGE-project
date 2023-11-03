#ifndef FGE_COREDEF_H_
#define FGE_COREDEF_H_
#include <functional>
#include <iostream>


namespace FGE{

template <class F>
struct MemManage
{
private:
std::function<void(F*)>* delPtr=nullptr;
public:
F* const ptr;


inline MemManage(F* mem_adress)noexcept
:ptr(mem_adress)
{
if(mem_adress==nullptr){std::cout<<"FGE_FATAL_ERROR:\n <FGE_MEMORY_WRONGASSIGN>\n Code tried to assign nonexistant memory :("<<"";exit(-1);}
};

inline MemManage(F* mem_adress, std::function<void(F*)>* pointer_to_delete_call)noexcept
:delPtr(pointer_to_delete_call),ptr(mem_adress)
{if(mem_adress==nullptr){std::cout<<"FGE_FATAL_ERROR:\n <FGE_MEMORY_WRONGASSIGN>\n Code tried to assign nonexistant memory :("<<"";exit(-1);}};

inline ~MemManage()noexcept{if(delPtr==nullptr)delete ptr; (*delPtr)(ptr);}
constexpr F* operator()()noexcept
{
    return ptr; 
}
}; 






}

#endif