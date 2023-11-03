#ifndef FGE_FILE_PARSING_H_
#define FGE_FILE_PASRSING_H_
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <unordered_map>



namespace FGE{
constexpr size_t AVG_WORD_LENGTH_ENGLISH{5};
constexpr size_t AVG_SEPERATOR_CONTRIB{1};
constexpr size_t AVG_SIZE_PER_WORDS{AVG_SEPERATOR_CONTRIB+AVG_WORD_LENGTH_ENGLISH};
using SeperatorList=std::vector<std::string>;
using XmlMap=std::unordered_map<std::string,std::string>;

template<typename T>
inline std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vec)
{
for(auto& el:vec)stream<<"["<<el<<"]";
return stream; 
}



/*https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring; User: Tyler McHenrey; accessed:30.08.2023*/
std::string ReadFile(const char* filename)
{
std::ifstream t(filename);
std::string str;

t.seekg(0, std::ios::end);   
str.reserve(t.tellg());
t.seekg(0, std::ios::beg);

str.assign((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());

return std::move(str);
}

template<typename T>
inline bool contains(const std::vector<T>& vec, T id)noexcept
{
    for(auto& el:vec)if(el==id)return 1;
    return 0;
}

inline SeperatorList SeperateFile(const char* filename, const std::vector<char>& seperators)
{
char ch;
std::fstream fin(filename, std::fstream::in);
SeperatorList list; list.reserve(100);
std::string word=""; 
while (fin >> std::noskipws >> ch) {
if(contains(seperators,ch)){if(word!=""){list.push_back(word); word="";}continue;} 
word+=ch;
}

return list; 
}

inline void ReadXml(const char* filename,XmlMap& map)
{
    const SeperatorList list=std::move(SeperateFile(filename,{'<','>',' ','/','\n'}));
    for(int i=0;i<list.size()-2;++i)
     if(list.at(i)==list.at(i+2))
     {
        map.insert({list.at(i),list.at(i+1)});
        i+=2;
     }
}

inline void CreateXml(const char* filename, const XmlMap& map)noexcept
{
std::ofstream file{filename,std::ios::trunc|std::ios::binary};
for(auto& pair:map)file<<'<'<<pair.first<<'>'<<pair.second<<"</"<<pair.first<<">\n";

}

}
#endif