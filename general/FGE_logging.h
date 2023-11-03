#ifndef FGE_PRINT_H_
#define FGE_PRINT_H_
#include <fstream>
namespace FGE{
inline struct Logger
{
private:
std::ofstream file; 
public:
Logger():file("log.text",std::ios::trunc|std::ios::binary){}
Logger(const char* filename):file(filename){}
~Logger(){file.close();}
template<typename T>
inline std::ofstream& operator<<(T obj)
{
    file<<obj; 
    return file; 
}

}logger;




};



#endif