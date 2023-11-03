#ifndef FGE_UNITS_H_
#define FGE_UNITS_H_

namespace FGE{


enum CURRENCY_UNIT{
    CURRENCY_NONE, 
    EUR,
    USD,
    JPY,
    GBP,
    CNY,
    AUD,
    CAD,
    CHF,
    HKD,
    SGD,
    SEK,
    KRW,
    NOK,
    NZD,
    INR,
    MXN,
    TWD,
    ZAR,
    BRL,
    DKK,
    PLN,
    THB,
    ILS,
    IDR,
    CZK
};
enum TIME_UNIT
{
    TIME_NONE,
    second,
    minute, 
    hour,
    day,
    week,
    millisecond,
    microsecond,
    nanosecond
};
enum LENGTH_UNIT
{
    LENGTH_NONE,
    meter,
    millimeter, 
    centimeter,
    decimeter,
    kilometer,
    inch,
    foot,
    yard,
    mile,
    league
};
enum MASS_UNIT
{
    MASS_NONE,
    kilogram,
    gram, 
    milligram,
    tonne,
    sl,
    lb,
};
enum TEMPERATURE_UNIT
{
    TEMPERATURE_NONE,
    KELVIN, 
    FAHRENHEIT,
    CELSIUS
};
constexpr float ConvertToKelvin(TEMPERATURE_UNIT unit, float value)
{
    switch(unit)
    {
        case TEMPERATURE_NONE: return 0;
        case KELVIN: return value; 
        case CELSIUS: return value+273.15f;
        case FAHRENHEIT: return (value-32.f)*0.55556f+273.15f; 
    }
}
constexpr float ConvertKelvinTo(TEMPERATURE_UNIT unit, float value)
{
    switch(unit)
    {
        case TEMPERATURE_NONE: return 0;
        case KELVIN: return value; 
        case CELSIUS: return value-273.15f;
        case FAHRENHEIT: return (value-273.15f)*1.8f+32.f; 
    }
}
constexpr float TIME_LOOKUP__CONVERSION_FACTOR[]={0.0f,1.0f,60.f,3600.f,86400.f,604800.f,0.001f,1.e-06,1.e-09 };
constexpr float LENGTH_LOOKUP__CONVERSION_FACTOR[]={0.0f,1.0f,0.001f,0.01f,0.1f,1000.f,0.0254f,0.3048f,0.9144f, 1609.344f,4.800f };
constexpr float MASS_LOOKUP__CONVERSION_FACTOR[]={0.0f,1.0f,0.001f,1.e-06f,1000.f,14.6f,0.45f };

/*Conversion factors as of 30.08.2023*/
constexpr float CURRENCY_LOOKUP__CONVERSION_FACTOR[]={0.0f, 1.0f,1.088267f, 159.27728f, 0.860359f,7.931304f,1.682898f,1.476056f, 0.957322f,8.540276f,1.472374f,11.834727f, 1440.715537f,11.536586f,1.836874f,90.019421f,18.230825f,34.662863f,20.21517f,5.281461f,7.45331f,4.474619f,38.206145f,4.133189,16558.559633f,24.074727f, };


constexpr float ConversionFactor(TIME_UNIT from, TIME_UNIT to)
{
    return TIME_LOOKUP__CONVERSION_FACTOR[from]/TIME_LOOKUP__CONVERSION_FACTOR[to];
}
constexpr float ConvertUnit(float value, TIME_UNIT from, TIME_UNIT to)
{   
    return ConversionFactor(from,to)*value; 
}
constexpr float ConversionFactor(LENGTH_UNIT from, LENGTH_UNIT to)
{
    return LENGTH_LOOKUP__CONVERSION_FACTOR[from]/LENGTH_LOOKUP__CONVERSION_FACTOR[to];
}
constexpr float ConvertUnit(float value, LENGTH_UNIT from, LENGTH_UNIT to)
{   
    return ConversionFactor(from,to)*value; 
}
constexpr float ConversionFactor(MASS_UNIT from, MASS_UNIT to)
{
    return MASS_LOOKUP__CONVERSION_FACTOR[from]/MASS_LOOKUP__CONVERSION_FACTOR[to];
}
constexpr float ConvertUnit(float value, MASS_UNIT from, MASS_UNIT to)
{   
    return ConversionFactor(from,to)*value; 
}
constexpr float ConvertUnit(float value, TEMPERATURE_UNIT from, TEMPERATURE_UNIT to)
{
if(from==to)return value; 
if(to==KELVIN)return ConvertToKelvin(from,value); 
if(from==KELVIN)return ConvertKelvinTo(to,value);
return ConvertKelvinTo(to,ConvertToKelvin(from,value));
}
constexpr float ConversionFactor(CURRENCY_UNIT from, CURRENCY_UNIT to)
{
    return CURRENCY_LOOKUP__CONVERSION_FACTOR[to]/CURRENCY_LOOKUP__CONVERSION_FACTOR[from];
}
constexpr float ConvertUnit(float value, CURRENCY_UNIT from, CURRENCY_UNIT to)
{
    return value*ConversionFactor(from,to);
}
}

#endif