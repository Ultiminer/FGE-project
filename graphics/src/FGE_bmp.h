#ifndef FGE_BMP_H_
#define FGE_BMP_H_
#include <iostream>
#include <string>
#include <cstdint>
#include <array>
#include <fstream>
#include <vector>
namespace FGE{

typedef uint8_t BYTE1; 
typedef uint32_t BYTE4;
typedef int32_t sBYTE4; 
typedef uint16_t BYTE2; 

struct Color
{
    unsigned char r; 
    unsigned char g; 
    unsigned char b; 
    unsigned char a; 
};
struct BMP_DESCRIPTOR
{
    int width,height,channelNum; 
    std::vector<char> data; 
};
inline struct BMP_HEAD{const BYTE2 id{66+77*256}; BYTE4 fileSize; const BYTE4 reserved{0}; const BYTE4 offsetToImgData{54};}bmpHead; 
inline struct BMP_INFO{const BYTE4 size{40};sBYTE4 imgWidth; sBYTE4 imgHeight; const BYTE2 numColorPlanes{1}; const BYTE2 bitsPerPixel{32};
const BYTE4 compression{0};const BYTE4 imgSize{0}; const sBYTE4 horRes{1920}; const sBYTE4 vertRes{1080};const BYTE4 numColorPallete{0};
const BYTE4 numImportantColors{0};
}bmpInfo;


#define MAP_OUT_BYTE4(x) ((char*)&x)[0]<<((char*)&x)[1]<<((char*)&x)[2]<<((char*)&x)[3]
#define MAP_OUT_BYTE2(x) ((char*)&x)[0]<<((char*)&x)[1]
#define MAP_IN_BYTE4(x) *((int*)&x)
#define MAP_IN_BYTE2(x) *((short*)&x)


inline BMP_DESCRIPTOR LoadBitmap(const char* src) noexcept
{
    BMP_DESCRIPTOR retVal; 

    std::ifstream file(src,std::ios::binary);
    char currByte=' ';
    size_t byteNum=0;
    std::string readBuffer="";
    size_t pixelDataOffset=0;
    bool PIXEL_DATA_MODE=false;

    while(file>>currByte)
    {
        if(PIXEL_DATA_MODE)
        {
            //if(byteNum-pixelDataOffset<5||(byteNum-pixelDataOffset-2)%6>1){
            retVal.data.push_back(currByte); 
            std::cout<<(int)currByte<<"|";
            //}
        }
        else{
        //Read out offset to pixel data array
        if(byteNum==14)pixelDataOffset=MAP_IN_BYTE4(readBuffer.at(10));
        //Read out image width
        if(byteNum==22)retVal.width=MAP_IN_BYTE4(readBuffer.at(18));
        //Read out image height
        if(byteNum==26)retVal.height=MAP_IN_BYTE4(readBuffer.at(22));
        //Read out channelNum in bitsPerPixel/8
        if(byteNum==30)retVal.channelNum=MAP_IN_BYTE2(readBuffer.at(28))/8;
        if(pixelDataOffset!=0&&byteNum==pixelDataOffset-1)PIXEL_DATA_MODE=true;
       }
        readBuffer+=currByte;  
        
        byteNum++;
    }
    file.close();
    std::cout<<"width: "<<retVal.width<<" height: "<<retVal.height<<" channelNum: "<<retVal.channelNum<<" data_size: "<<retVal.data.size();

    return retVal;
}

/*WIDTH should NOT be 10^n*/
template<size_t WIDTH, size_t HEIGHT>
void CreateBitmap(const char* path, const std::array<Color,WIDTH*HEIGHT>&colorArray)
{
    bmpInfo.imgHeight=HEIGHT; 
    bmpInfo.imgWidth=WIDTH;
    bmpHead.fileSize=bmpHead.offsetToImgData+WIDTH*HEIGHT*4;

    std::ofstream fileDescriptor(path);
    fileDescriptor<<MAP_OUT_BYTE2(bmpHead.id)<<MAP_OUT_BYTE4(bmpHead.fileSize)
    <<MAP_OUT_BYTE4(bmpHead.reserved)<<MAP_OUT_BYTE4(bmpHead.offsetToImgData)<<
    MAP_OUT_BYTE4(bmpInfo.size)<<MAP_OUT_BYTE4(bmpInfo.imgWidth)<<MAP_OUT_BYTE4(bmpInfo.imgHeight)<<MAP_OUT_BYTE2(bmpInfo.numColorPlanes)<<
    MAP_OUT_BYTE2(bmpInfo.bitsPerPixel)<<MAP_OUT_BYTE4(bmpInfo.compression)<<MAP_OUT_BYTE4(bmpInfo.imgSize)<<
    MAP_OUT_BYTE4(bmpInfo.horRes)<<MAP_OUT_BYTE4(bmpInfo.vertRes)<<MAP_OUT_BYTE4(bmpInfo.numColorPallete)<<MAP_OUT_BYTE4(bmpInfo.numImportantColors)
    ;
    for(int i=0; i<colorArray.size();++i)
    fileDescriptor<<colorArray.at(i).b<<colorArray.at(i).g<<colorArray.at(i).r<<colorArray.at(i).a;

    fileDescriptor.close(); 
}


};


#endif