#ifndef FGE_PRIM_GEOMETRY_H_
#define FGE_PRIM_GEOMETRY_H_
#include "FGE_sdl_types.h"


constexpr unsigned int __FGE_PRIMITIVE_PRELOAD_INDICES[]=
{0,1,2,0,2,3,0,3,4,0,4,5,0,5,6,0,6,7,0,7,8,0,8,9,0,9,10,0,10,11,0,11,12,0,12,13,0,13,14,0,14,15,0,15,16,0,16,17,0,17,18,0,18,19,0,19,20,0,20,21,0,21,22,0,22,23,0,23,24,0,24,25,0,25,26,0,26,27,0,27,28,0,28,29,0,29,30,0,30,31,0,31,32,0,32,33,0,33,34,0,34,35,0,35,36,0,36,37,0,37,38,0,38,39,0,39,40,0,40,41,0,41,42,0,42,43,0,43,44,0,44,45,0,45,46,0,46,47,0,47,48,0,48,49,0,49,50,0,50,51,0,51,52,0,52,53,0,53,54,0,54,55,0,55,56,0,56,57,0,57,58,0,58,59,0,59,60,0,60,61,0,61,62,0,62,63,0,63,64,0,64,65,0,65,66,0,66,67,0,67,68,0,68,69,0,69,70,0,70,71,0,71,72,0,72,73,0,73,74,0,74,75,0,75,76,0,76,77,0,77,78,0,78,79,0,79,80,0,80,81,0,81,82,0,82,83,0,83,84,0,84,85,0,85,86,0,86,87,0,87,88,0,88,89,0,89,90,0,90,91,0,91,92,0,92,93,0,93,94,0,94,95,0,95,96,0,96,97,0,97,98,0,98,99,0,99,100,0,100,101,0,101,102,0,102,103,0,103,104,0,104,105,0,105,106,0,106,107,0,107,108,0,108,109,0,109,110,0,110,111,0,111,112,0,112,113,0,113,114,0,114,115,0,115,116,0,116,117,0,117,118,0,118,119,0,119,120,0,120,121,0,121,122,0,122,123,0,123,124,0,124,125,0,125,126,0,126,127,0,127,128,0,128,129,0,129,130,0,130,131,0,131,132,0,132,133,0,133,134,0,134,135,0,135,136,0,136,137,0,137,138,0,138,139,0,139,140,0,140,141,0,141,142,0,142,143,0,143,144,0,144,145,0,145,146,0,146,147,0,147,148,0,148,149,0,149,150,0,150,151,0,151,152,0,152,153,0,153,154,0,154,155,0,155,156,0,156,157,0,157,158,0,158,159,0,159,160,0,160,161,0,161,162,0,162,163,0,163,164,0,164,165,0,165,166,0,166,167,0,167,168,0,168,169,0,169,170,0,170,171,0,171,172,0,172,173,0,173,174,0,174,175,0,175,176,0,176,177,0,177,178,0,178,179,0,179,180,0,180,181,0,181,182,0,182,183,0,183,184,0,184,185,0,185,186,0,186,187,0,187,188,0,188,189,0,189,190,0,190,191,0,191,192,0,192,193,0,193,194,0,194,195,0,195,196,0,196,197,0,197,198,0,198,199,0,199,200,0,200,201,0,201,202,0,202,203,0,203,204,0,204,205,0,205,206,0,206,207,0,207,208,0,208,209,0,209,210,0,210,211,0,211,212,0,212,213,0,213,214,0,214,215,0,215,216,0,216,217,0,217,218,0,218,219,0,219,220,0,220,221,0,221,222,0,222,223,0,223,224,0,224,225,0,225,226,0,226,227,0,227,228,0,228,229,0,229,230,0,230,231,0,231,232,0,232,233,0,233,234,0,234,235,0,235,236,0,236,237,0,237,238,0,238,239,0,239,240,0,240,241,0,241,242,0,242,243,0,243,244,0,244,245,0,245,246,0,246,247,0,247,248,0,248,249,0,249,250,0,250,251,0,251,252,0,252,253,0,253,254,0,254,255,0,255,256,0,256,257,0,257,258,0,258,259,0,259,260,0,260,261,0,261,262,0,262,263,0,263,264,0,264,265,0,265,266,0,266,267,0,267,268,0,268,269,0,269,270,0,270,271,0,271,272,0,272,273,0,273,274,0,274,275,0,275,276,0,276,277,0,277,278,0,278,279,0,279,280,0,280,281,0,281,282,0,282,283,0,283,284,0,284,285,0,285,286,0,286,287,0,287,288,0,288,289,0,289,290,0,290,291,0,291,292,0,292,293,0,293,294,0,294,295,0,295,296,0,296,297,0,297,298,0,298,299,0,299,300,0,300,301,0,301,302,0,302,303,0,303,304,0,304,305,0,305,306,0,306,307,0,307,308,0,308,309,0,309,310,0,310,311,0,311,312,0,312,313,0,313,314,0,314,315,0,315,316,0,316,317,0,317,318,0,318,319,0,319,320,0,320,321,0,321,322,0,322,323,0,323,324,0,324,325,0,325,326,0,326,327,0,327,328,0,328,329,0,329,330,0,330,331,0,331,332,0,332,333,0,333,334,0,334,335,0,335,336,0,336,337,0,337,338,0,338,339,0,339,340,0,340,341,0,341,342,0,342,343,0,343,344,0,344,345,0,345,346,0,346,347,0,347,348,0,348,349,0,349,350,0,350,351,0,351,352,0,352,353,0,353,354,0,354,355,0,355,356,0,356,357,0,357,358,0,358,359,0,359,360,0,360,361,0,361,362,0,362,363,0,363,364,0,364,365,0,365,366,0,366,367,0,367,368,0,368,369,0,369,370,0,370,371,0,371,372,0,372,373,0,373,374,0,374,375,0,375,376,0,376,377,0,377,378,0,378,379,0,379,380,0,380,381,0,381,382,0,382,383,0,383,384,0,384,385,0,385,386,0,386,387,0,387,388,0,388,389,0,389,390,0,390,391,0,391,392,0,392,393,0,393,394,0,394,395,0,395,396,0,396,397,0,397,398,0,398,399,0,399,400,0,400,401,0,401,402,0,402,403,0,403,404,0,404,405,0,405,406,0,406,407,0,407,408,0,408,409,0,409,410,0,410,411,0,411,412,0,412,413,0,413,414,0,414,415,0,415,416,0,416,417,0,417,418,0,418,419,0,419,420,0,420,421,0,421,422,0,422,423,0,423,424,0,424,425,0,425,426,0,426,427,0,427,428,0,428,429,0,429,430,0,430,431,0,431,432,0,432,433,0,433,434,0,434,435,0,435,436,0,436,437,0,437,438,0,438,439,0,439,440,0,440,441,0,441,442,0,442,443,0,443,444,0,444,445,0,445,446,0,446,447,0,447,448,0,448,449,0,449,450,0,450,451,0,451,452,0,452,453,0,453,454,0,454,455,0,455,456,0,456,457,0,457,458,0,458,459,0,459,460,0,460,461,0,461,462,0,462,463,0,463,464,0,464,465,0,465,466,0,466,467,0,467,468,0,468,469,0,469,470,0,470,471,0,471,472,0,472,473,0,473,474,0,474,475,0,475,476,0,476,477,0,477,478,0,478,479,0,479,480,0,480,481,0,481,482,0,482,483,0,483,484,0,484,485,0,485,486,0,486,487,0,487,488,0,488,489,0,489,490,0,490,491,0,491,492,0,492,493,0,493,494,0,494,495,0,495,496,0,496,497,0,497,498,0,498,499,0,499,500,0,500,501,0,501,502,0,502,503,0,503,504,0,504,505,0,505,506,0,506,507,0,507,508,0,508,509,0,509,510,0,510,511};

constexpr float __FGE_PRIMITIVE_PRELOAD_SQUIRCLE_DATA[]={1,0,1,0.0122721,1,0.0245479,0.999998,0.036831,0.999995,0.0491251,0.999988,0.0614338,0.999974,0.0737604,0.999953,0.0861082,0.999919,0.0984805,0.999871,0.11088,0.999804,0.12331,0.999714,0.135773,0.999596,0.148272,0.999445,0.160807,0.999256,0.173382,0.999023,0.185998,0.998739,0.198656,0.9984,0.211356,0.997998,0.224101,0.997525,0.236889,0.996976,0.249722,0.996343,0.262598,0.995618,0.275516,0.994793,0.288476,0.993862,0.301475,0.992816,0.314513,0.991647,0.327586,0.990349,0.340692,0.988911,0.353827,0.987328,0.366988,0.985591,0.380172,0.983692,0.393374,0.981624,0.406589,0.979379,0.419812,0.976951,0.433038,0.974331,0.446262,0.971514,0.459477,0.968493,0.472676,0.96526,0.485854,0.961811,0.499004,0.958139,0.512118,0.95424,0.525189,0.950107,0.53821,0.945738,0.551173,0.941126,0.564069,0.936268,0.576891,0.931162,0.58963,0.925804,0.602279,0.920191,0.614829,0.914321,0.627271,0.908193,0.639597,0.901806,0.651799,0.895159,0.663869,0.888251,0.675797,0.881083,0.687577,0.873657,0.699199,0.865972,0.710656,0.858031,0.721939,0.849836,0.733043,0.84139,0.743958,0.832696,0.754679,0.823757,0.765197,0.814577,0.775507,0.805161,0.785602,0.795514,0.795477,0.78564,0.805125,0.775545,0.814542,0.765236,0.823723,0.754719,0.832663,0.743999,0.841358,0.733084,0.849805,0.721982,0.858001,0.710698,0.865943,0.699242,0.873628,0.687621,0.881056,0.675842,0.888224,0.663914,0.895133,0.651845,0.901781,0.639643,0.90817,0.627318,0.914298,0.614876,0.920169,0.602327,0.925783,0.589678,0.931142,0.576939,0.93625,0.564117,0.941108,0.551221,0.945721,0.538259,0.950091,0.525239,0.954225,0.512168,0.958125,0.499054,0.961798,0.485904,0.965248,0.472726,0.968481,0.459526,0.971503,0.446312,0.974321,0.433088,0.976941,0.419862,0.979371,0.406639,0.981616,0.393424,0.983685,0.380222,0.985584,0.367038,0.987322,0.353877,0.988906,0.340741,0.990344,0.327635,0.991643,0.314562,0.992812,0.301524,0.993858,0.288525,0.99479,0.275565,0.995615,0.262646,0.99634,0.24977,0.996974,0.236938,0.997523,0.224149,0.997996,0.211404,0.998399,0.198704,0.998738,0.186046,0.999022,0.17343,0.999255,0.160855,0.999444,0.148319,0.999595,0.13582,0.999713,0.123357,0.999804,0.110927,0.999871,0.0985273,0.999919,0.0861549,0.999953,0.0738069,0.999974,0.0614802,0.999988,0.0491716,0.999995,0.0368774,0.999998,0.0245942,1,0.0123185,1,4.63287e-05,1,-0.0122258,1,-0.0245015,1,-0.0367846,0.999998,-0.0490788,0.999995,-0.0613872,0.999988,-0.0737138,0.999974,-0.0860616,0.999953,-0.0984337,0.99992,-0.110833,0.999871,-0.123263,0.999804,-0.135726,0.999714,-0.148224,0.999596,-0.16076,0.999445,-0.173334,0.999256,-0.18595,0.999024,-0.198608,0.998741,-0.211308,0.998401,-0.224053,0.997999,-0.236841,0.997527,-0.249673,0.996978,-0.262549,0.996345,-0.275467,0.99562,-0.288427,0.994797,-0.301426,0.993866,-0.314463,0.99282,-0.327536,0.991652,-0.340642,0.990354,-0.353777,0.988917,-0.366939,0.987334,-0.380122,0.985598,-0.393324,0.9837,-0.406539,0.981632,-0.419762,0.979388,-0.432988,0.97696,-0.446212,0.974342,-0.459427,0.971525,-0.472626,0.968504,-0.485805,0.965273,-0.498955,0.961824,-0.512069,0.958154,-0.52514,0.954255,-0.538161,0.950123,-0.551124,0.945754,-0.56402,0.941144,-0.576842,0.936287,-0.589582,0.931182,-0.602231,0.925824,-0.614781,0.920212,-0.627224,0.914344,-0.639551,0.908217,-0.651753,0.90183,-0.663823,0.895184,-0.675752,0.888278,-0.687532,0.881111,-0.699155,0.873685,-0.710613,0.866002,-0.721897,0.858062,-0.733001,0.849868,-0.743917,0.841422,-0.754638,0.832729,-0.765158,0.823791,-0.775468,0.814612,-0.785564,0.805197,-0.79544,0.795551,-0.805089,0.785678,-0.814507,0.775584,-0.823688,0.765276,-0.832629,0.754759,-0.841325,0.74404,-0.849774,0.733126,-0.85797,0.722024,-0.865913,0.710741,-0.8736,0.699286,-0.881028,0.687665,-0.888198,0.675887,-0.895107,0.663959,-0.901757,0.651891,-0.908146,0.63969,-0.914276,0.627364,-0.920147,0.614923,-0.925762,0.602374,-0.931123,0.589726,-0.936231,0.576987,-0.94109,0.564166,-0.945704,0.55127,-0.950075,0.538308,-0.95421,0.525288,-0.958111,0.512217,-0.961784,0.499103,-0.965235,0.485954,-0.968469,0.472776,-0.971492,0.459576,-0.974311,0.446362,-0.976932,0.433138,-0.979362,0.419912,-0.981608,0.406689,-0.983677,0.393473,-0.985577,0.380272,-0.987316,0.367088,-0.9889,0.353926,-0.990338,0.340791,-0.991638,0.327685,-0.992808,0.314611,-0.993855,0.301574,-0.994787,0.288574,-0.995612,0.275614,-0.996337,0.262695,-0.996971,0.249819,-0.997521,0.236986,-0.997994,0.224197,-0.998397,0.211453,-0.998737,0.198751,-0.999021,0.186093,-0.999254,0.173477,-0.999444,0.160902,-0.999595,0.148366,-0.999713,0.135868,-0.999803,0.123404,-0.999871,0.110974,-0.999919,0.0985741,-0.999952,0.0862015,-0.999974,0.0738535,-0.999988,0.0615269,-0.999995,0.0492179,-0.999998,0.0369238,-1,0.0246407,-1,0.0123647,-1,9.26574e-05,-1,-0.0121793,-1,-0.0244553,-0.999998,-0.0367383,-0.999995,-0.0490322,-0.999988,-0.0613409,-0.999974,-0.0736672,-0.999953,-0.0860148,-0.99992,-0.0983871,-0.999871,-0.110787,-0.999805,-0.123216,-0.999715,-0.135679,-0.999597,-0.148177,-0.999446,-0.160712,-0.999257,-0.173287,-0.999025,-0.185902,-0.998742,-0.19856,-0.998403,-0.21126,-0.998001,-0.224005,-0.997529,-0.236793,-0.99698,-0.249625,-0.996348,-0.2625,-0.995623,-0.275418,-0.9948,-0.288378,-0.993869,-0.301377,-0.992824,-0.314414,-0.991657,-0.327487,-0.990359,-0.340592,-0.988923,-0.353727,-0.987341,-0.366889,-0.985605,-0.380072,-0.983707,-0.393274,-0.98164,-0.406489,-0.979397,-0.419712,-0.97697,-0.432938,-0.974352,-0.446162,-0.971536,-0.459377,-0.968516,-0.472577,-0.965285,-0.485755,-0.961838,-0.498905,-0.958168,-0.512019,-0.95427,-0.525091,-0.95014,-0.538112,-0.945771,-0.551075,-0.941162,-0.563972,-0.936306,-0.576794,-0.931202,-0.589534,-0.925845,-0.602184,-0.920234,-0.614734,-0.914366,-0.627177,-0.90824,-0.639505,-0.901855,-0.651708,-0.89521,-0.663778,-0.888304,-0.675708,-0.881139,-0.687488,-0.873714,-0.699111,-0.866031,-0.71057,-0.858092,-0.721855,-0.849899,-0.73296,-0.841455,-0.743877,-0.832762,-0.754598,-0.823825,-0.765118,-0.814647,-0.77543,-0.805233,-0.785527,-0.795587,-0.795403,-0.785715,-0.805053,-0.775622,-0.814472,-0.765315,-0.823654,-0.754799,-0.832596,-0.744081,-0.841293,-0.733167,-0.849742,-0.722066,-0.85794,-0.710784,-0.865883,-0.699329,-0.873571,-0.687709,-0.881001,-0.675931,-0.888171,-0.664005,-0.895082,-0.651937,-0.901732,-0.639736,-0.908122,-0.627411,-0.914253,-0.61497,-0.920126,-0.602422,-0.925742,-0.589774,-0.931103,-0.577035,-0.936212,-0.564214,-0.941072,-0.551319,-0.945687,-0.538358,-0.950059,-0.525337,-0.954194,-0.512266,-0.958097,-0.499153,-0.961771,-0.486004,-0.965222,-0.472826,-0.968457,-0.459626,-0.971481,-0.446411,-0.974301,-0.433188,-0.976922,-0.419962,-0.979353,-0.406738,-0.9816,-0.393523,-0.98367,-0.380322,-0.98557,-0.367137,-0.987309,-0.353976,-0.988894,-0.34084,-0.990333,-0.327734,-0.991634,-0.314661,-0.992804,-0.301623,-0.993851,-0.288623,-0.994783,-0.275662,-0.995609,-0.262744,-0.996335,-0.249867,-0.996969,-0.237035,-0.997519,-0.224246,-0.997993,-0.2115,-0.998396,-0.198799,-0.998736,-0.186141,-0.99902,-0.173525,-0.999253,-0.16095,-0.999443,-0.148414,-0.999594,-0.135915,-0.999713,-0.123451,-0.999803,-0.111021,-0.99987,-0.0986209,-0.999919,-0.0862484,-0.999952,-0.0739003,-0.999974,-0.0615731,-0.999987,-0.0492644,-0.999995,-0.0369702,-0.999998,-0.024687,-1,-0.0124113,-1,-0.000139225,-1,0.0121333,-1,0.0244089,-1,0.0366919,-0.999998,0.0489857,-0.999995,0.0612941,-0.999988,0.0736209,-0.999975,0.0859684,-0.999953,0.0983403,-0.99992,0.11074,-0.999872,0.123169,-0.999805,0.135632,-0.999715,0.14813,-0.999597,0.160665,-0.999447,0.17324,-0.999258,0.185855,-0.999026,0.198512,-0.998743,0.211212,-0.998404,0.223957,-0.998003,0.236745,-0.997531,0.249576,-0.996983,0.262451,-0.99635,0.275369,-0.995626,0.288328,-0.994803,0.301328,-0.993873,0.314365,-0.992829,0.327438,-0.991662,0.340543,-0.990364,0.353678,-0.988929,0.366839,-0.987347,0.380023,-0.985611,0.393224,-0.983714,0.406439,-0.981648,0.419662,-0.979406,0.432888,-0.976979,0.446112,-0.974362,0.459327,-0.971547,0.472527,-0.968528,0.485705,-0.965298,0.498855,-0.961851,0.51197,-0.958182,0.525042,-0.954285,0.538063,-0.950156,0.551026,-0.945788,0.563923,-0.941179,0.576746,-0.936325,0.589486,-0.931221,0.602136,-0.925866,0.614687,-0.920256,0.627131,-0.914389,0.639458,-0.908264,0.651662,-0.90188,0.663733,-0.895235,0.675663,-0.888331,0.687444,-0.881166,0.699068,-0.873742,0.710527,-0.86606,0.721813,-0.858123,0.732918,-0.849931,0.743836,-0.841487,0.754558,-0.832795,0.765079,-0.823859,0.775391,-0.814682,0.785489,-0.805269,0.795366,-0.795624,0.805017,-0.785753,0.814437,-0.775661,0.82362,-0.765354,0.832563,-0.754839,0.841261,-0.744122,0.849711,-0.733209,0.857909,-0.722109,0.865854,-0.710827,0.873543,-0.699373,0.880973,-0.687753,0.888145,-0.675976,0.895056,-0.66405,0.901707,-0.651983,0.908099,-0.639782,0.914231,-0.627458,0.920104,-0.615017,0.925721,-0.602469,0.931083,-0.589822,0.936193,-0.577084,0.941054,-0.564263,0.94567,-0.551368,0.950043,-0.538406,0.954179,-0.525387,0.958082,-0.512316,0.961757,-0.499203,0.96521,-0.486053,0.968445,-0.472875,0.97147,-0.459676,0.97429,-0.446461,0.976913,-0.433238,0.979344,-0.420012,0.981592,-0.406788,0.983662,-0.393573,0.985563,-0.380371,0.987303,-0.367187,0.988889,-0.354026,0.990328,-0.34089,0.991629,-0.327783,0.992799,-0.31471,0.993847,-0.301672,0.99478,-0.288672,0.995606,-0.275712,0.996332,-0.262793,0.996967,-0.249916,0.997518,-0.237083,0.997991,-0.224294,0.998394,-0.211549,0.998735,-0.198847,0.999019,-0.186189,0.999253,-0.173572,0.999442,-0.160997,0.999594,-0.148461,0.999712,-0.135962,0.999803,-0.123498,0.99987,-0.111068,0.999919,-0.0986674,0.999952,-0.0862948,0.999974,-0.0739467,0.999987,-0.0616199,0.999995,-0.0493111,0.999998,-0.0370168,1,-0.0247332,1,-0.0124574,1,0};
constexpr float __FGE_PRIMITIVE_PRELOAD_SQUARE_DATA[]={-1,1,1,1,1,-1,-1,-1,-1,1};
constexpr float __FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA[]=
{1,0,0.999924,0.0122848,0.999698,0.0245678,0.999321,0.0368471,0.998793,0.0491209,0.998114,0.0613872,0.997285,0.0736442,0.996305,0.0858902,0.995174,0.0981231,0.993894,0.110341,0.992463,0.122543,0.990883,0.134726,0.989153,0.146888,0.987274,0.159029,0.985246,0.171145,0.983069,0.183236,0.980744,0.195299,0.97827,0.207333,0.97565,0.219335,0.972881,0.231304,0.969967,0.243238,0.966905,0.255136,0.963698,0.266995,0.960345,0.278814,0.956848,0.29059,0.953205,0.302323,0.94942,0.31401,0.94549,0.32565,0.941418,0.337241,0.937205,0.34878,0.932849,0.360267,0.928353,0.3717,0.923716,0.383077,0.918941,0.394396,0.914026,0.405655,0.908974,0.416853,0.903784,0.427988,0.898458,0.439059,0.892997,0.450063,0.887401,0.460999,0.88167,0.471866,0.875807,0.482662,0.869811,0.493384,0.863685,0.504033,0.857427,0.514605,0.851041,0.525099,0.844526,0.535515,0.837883,0.545849,0.831115,0.556101,0.82422,0.566269,0.817201,0.576352,0.810059,0.586348,0.802795,0.596255,0.79541,0.606072,0.787904,0.615798,0.78028,0.625431,0.772537,0.634969,0.764679,0.644412,0.756704,0.653757,0.748616,0.663004,0.740414,0.67215,0.732101,0.681196,0.723678,0.690138,0.715145,0.698976,0.706504,0.707709,0.697757,0.716335,0.688904,0.724853,0.679947,0.733261,0.670888,0.741559,0.661727,0.749745,0.652467,0.757817,0.643108,0.765776,0.633652,0.773618,0.6241,0.781344,0.614455,0.788952,0.604716,0.796441,0.594886,0.80381,0.584967,0.811057,0.574959,0.818182,0.564864,0.825184,0.554684,0.832061,0.544421,0.838812,0.534075,0.845437,0.523649,0.851934,0.513143,0.858303,0.50256,0.864542,0.491902,0.870651,0.481169,0.876628,0.470363,0.882473,0.459487,0.888185,0.448541,0.893762,0.437527,0.899205,0.426448,0.904512,0.415304,0.909683,0.404097,0.914716,0.39283,0.919611,0.381503,0.924368,0.370118,0.928985,0.358678,0.933461,0.347184,0.937797,0.335637,0.941992,0.324039,0.946044,0.312393,0.949953,0.300699,0.953719,0.28896,0.957341,0.277178,0.960819,0.265353,0.964151,0.253489,0.967338,0.241586,0.970379,0.229647,0.973274,0.217673,0.976022,0.205667,0.978622,0.193629,0.981075,0.181562,0.98338,0.169468,0.985536,0.157348,0.987543,0.145204,0.989402,0.133039,0.991111,0.120853,0.99267,0.108649,0.99408,0.0964287,0.99534,0.0841938,0.996449,0.0719463,0.997409,0.0596879,0.998217,0.0474205,0.998875,0.035146,0.999382,0.0228661,0.999739,0.0105829,0.999944,-0.00170203,0.999999,-0.0139868,0.999902,-0.0262693,0.999655,-0.038548,0.999257,-0.0508206,0.998708,-0.0630857,0.998008,-0.0753414,0.997158,-0.0875855,0.996157,-0.0998166,0.995006,-0.112032,0.993705,-0.124231,0.992253,-0.136412,0.990652,-0.148571,0.988902,-0.160709,0.987002,-0.172822,0.984953,-0.184909,0.982756,-0.196968,0.98041,-0.208997,0.977916,-0.220995,0.975275,-0.232959,0.972487,-0.244888,0.969551,-0.25678,0.96647,-0.268634,0.963242,-0.280447,0.959869,-0.292218,0.956352,-0.303944,0.95269,-0.315625,0.948884,-0.327258,0.944935,-0.338842,0.940843,-0.350374,0.93661,-0.361854,0.932235,-0.373279,0.927719,-0.384647,0.923064,-0.395958,0.918269,-0.407209,0.913335,-0.418398,0.908264,-0.429525,0.903055,-0.440586,0.89771,-0.451581,0.89223,-0.462508,0.886615,-0.473365,0.880866,-0.484151,0.874985,-0.494864,0.868971,-0.505501,0.862826,-0.516063,0.856551,-0.526547,0.850146,-0.536951,0.843613,-0.547274,0.836953,-0.557515,0.830167,-0.567671,0.823255,-0.577742,0.816219,-0.587726,0.80906,-0.59762,0.801779,-0.607425,0.794377,-0.617138,0.786855,-0.626758,0.779214,-0.636283,0.771455,-0.645713,0.763581,-0.655044,0.75559,-0.664277,0.747486,-0.67341,0.739269,-0.682441,0.730941,-0.691369,0.722502,-0.700193,0.713954,-0.708911,0.705298,-0.717522,0.696536,-0.726025,0.687669,-0.734418,0.678698,-0.7427,0.669624,-0.75087,0.66045,-0.758927,0.651175,-0.76687,0.641803,-0.774696,0.632333,-0.782406,0.622769,-0.789998,0.61311,-0.79747,0.603359,-0.804822,0.593516,-0.812053,0.583584,-0.819161,0.573564,-0.826145,0.563458,-0.833005,0.553266,-0.839739,0.542991,-0.846346,0.532634,-0.852825,0.522196,-0.859176,0.51168,-0.865397,0.501086,-0.871488,0.490417,-0.877447,0.479674,-0.883273,0.468858,-0.888967,0.457972,-0.894526,0.447017,-0.89995,0.435994,-0.905238,0.424905,-0.91039,0.413752,-0.915404,0.402537,-0.92028,0.391261,-0.925017,0.379926,-0.929615,0.368533,-0.934072,0.357085,-0.938388,0.345583,-0.942563,0.334029,-0.946595,0.322425,-0.950485,0.310772,-0.954231,0.299071,-0.957833,0.287326,-0.96129,0.275538,-0.964603,0.263707,-0.96777,0.251838,-0.97079,0.239929,-0.973665,0.227985,-0.976392,0.216007,-0.978972,0.203995,-0.981404,0.191954,-0.983688,0.179883,-0.985824,0.167784,-0.98781,0.155661,-0.989648,0.143514,-0.991337,0.131345,-0.992875,0.119157,-0.994264,0.106951,-0.995503,0.0947281,-0.996592,0.0824913,-0.99753,0.0702422,-0.998318,0.0579822,-0.998955,0.0457136,-0.999441,0.0334382,-0.999776,0.0211576,-0.999961,0.00887382,-0.999994,-0.00341129,-0.999877,-0.0156959,-0.999609,-0.0279781,-0.999189,-0.0402561,-0.998619,-0.052528,-0.997899,-0.0647922,-0.997028,-0.0770464,-0.996006,-0.089289,-0.994834,-0.101518,-0.993511,-0.113732,-0.992039,-0.125929,-0.990417,-0.138106,-0.988646,-0.150263,-0.986726,-0.162397,-0.984656,-0.174507,-0.982438,-0.18659,-0.980072,-0.198645,-0.977557,-0.21067,-0.974895,-0.222663,-0.972086,-0.234623,-0.969131,-0.246547,-0.966029,-0.258435,-0.962781,-0.270283,-0.959388,-0.28209,-0.95585,-0.293855,-0.952168,-0.305575,-0.948342,-0.317249,-0.944373,-0.328875,-0.940262,-0.340452,-0.936008,-0.351978,-0.931614,-0.36345,-0.927078,-0.374867,-0.922403,-0.386228,-0.917589,-0.397531,-0.912636,-0.408773,-0.907546,-0.419954,-0.902318,-0.431071,-0.896954,-0.442124,-0.891455,-0.453109,-0.885821,-0.464027,-0.880054,-0.474874,-0.874154,-0.485649,-0.868122,-0.496352,-0.861958,-0.506979,-0.855665,-0.51753,-0.849243,-0.528002,-0.842692,-0.538396,-0.836015,-0.548707,-0.829211,-0.558936,-0.822281,-0.569081,-0.815228,-0.57914,-0.808052,-0.589111,-0.800754,-0.598993,-0.793335,-0.608785,-0.785796,-0.618485,-0.778139,-0.628092,-0.770364,-0.637604,-0.762473,-0.64702,-0.754467,-0.656338,-0.746347,-0.665557,-0.738114,-0.674676,-0.72977,-0.683693,-0.721316,-0.692606,-0.712753,-0.701415,-0.704082,-0.710118,-0.695306,-0.718714,-0.686424,-0.727202,-0.677438,-0.73558,-0.668351,-0.743846,-0.659162,-0.752001,-0.649874,-0.760042,-0.640488,-0.767968,-0.631005,-0.775779,-0.621427,-0.783472,-0.611756,-0.791047,-0.601992,-0.798502,-0.592137,-0.805838,-0.582192,-0.813051,-0.57216,-0.820142,-0.562041,-0.827109,-0.551838,-0.833951,-0.541551,-0.840668,-0.531183,-0.847257,-0.520734,-0.853719,-0.510207,-0.860052,-0.499603,-0.866254,-0.488924,-0.872327,-0.47817,-0.878267,-0.467345,-0.884075,-0.456448,-0.88975,-0.445484,-0.89529,-0.434451,-0.900695,-0.423354,-0.905964,-0.412192,-0.911097,-0.400968,-0.916092,-0.389684,-0.920949,-0.37834,-0.925667,-0.36694,-0.930245,-0.355484,-0.934682,-0.343975,-0.938979,-0.332414,-0.943134,-0.320803,-0.947146,-0.309143,-0.951016,-0.297436,-0.954742,-0.285685,-0.958324,-0.27389,-0.961761,-0.262055,-0.965053,-0.250179,-0.9682,-0.238266,-0.9712,-0.226317,-0.974054,-0.214334,-0.97676,-0.202318,-0.97932,-0.190272,-0.981731,-0.178197,-0.983995,-0.166095,-0.98611,-0.153968,-0.988076,-0.141819,-0.989893,-0.129647,-0.99156,-0.117456,-0.993078,-0.105247,-0.994446,-0.0930226,-0.995664,-0.0807841,-0.996732,-0.0685329,-0.997649,-0.0562718,-0.998416,-0.0440022,-0.999031,-0.0317258,-0.999497,-0.0194448,-0.999811,-0.00716058,-0.999974,0.00512459,-0.999987,0.0174089,-0.999848,0.0296906,-0.999559,0.0419678,-0.999119,0.0542389,-0.998528,0.0665015,-0.997786,0.0787544,-0.996894,0.0909951,-0.995851,0.103222,-0.994658,0.115434,-0.993315,0.127628,-0.991822,0.139803,-0.990179,0.151956,-0.988387,0.164087,-0.986446,0.176193,-0.984356,0.188273,-0.982117,0.200324,-0.97973,0.212344,-0.977195,0.224333,-0.974513,0.236288,-0.971683,0.248207,-0.968707,0.260089,-0.965585,0.271932,-0.962317,0.283733,-0.958903,0.295492,-0.955345,0.307206,-0.951643,0.318874,-0.947797,0.330493,-0.943808,0.342063,-0.939677,0.353581,-0.935404,0.365045,-0.93099,0.376455,-0.926435,0.387808,-0.92174,0.399102,-0.916906,0.410336,-0.911934,0.421508,-0.906825,0.432617,-0.901578,0.44366,-0.896195,0.454636,-0.890677,0.465544,-0.885025,0.476381,-0.879239,0.487146,-0.87332,0.497838,-0.86727,0.508455,-0.861089,0.518995,-0.854777,0.529457,-0.848337,0.539839,-0.841769,0.550139,-0.835073,0.560356,-0.828252,0.570489,-0.821305,0.580535,-0.814235,0.590494,-0.807042,0.600364,-0.799727,0.610144,-0.792291,0.619831,-0.784736,0.629424,-0.777062,0.638923,-0.769271,0.648325,-0.761363,0.65763,-0.753341,0.666835,-0.745206,0.675939,-0.736957,0.684942,-0.728598,0.693841,-0.720128,0.702635,-0.71155,0.711324,-0.702865,0.719904,-0.694073,0.728377,-0.685177,0.736739,-0.676177,0.74499,-0.667075,0.753129,-0.657873,0.761154,-0.648571,0.769064,-0.639171,0.776859,-0.629675,0.784536,-0.620084,0.792094,-0.610399,0.799533,-0.600622,0.806851,-0.590755,0.814048,-0.580798,0.821121,-0.570754,0.828071,-0.560623,0.834896,-0.550408,0.841594,-0.54011,0.848166,-0.52973,0.85461,-0.519271,0.860925,-0.508733,0.867109,-0.498118,0.873163,-0.487428,0.879085,-0.476664,0.884875,-0.465829,0.890531,-0.454923,0.896052,-0.443949,0.901438,-0.432907,0.906689,-0.4218,0.911802,-0.41063,0.916778,-0.399398,0.921615,-0.388105,0.926313,-0.376754,0.930872,-0.365346,0.93529,-0.353883,0.939567,-0.342366,0.943702,-0.330797,0.947694,-0.319179,0.951544,-0.307513,0.95525,-0.2958,0.958812,-0.284042,0.962229,-0.272242,0.965501,-0.260401,0.968627,-0.24852,0.971607,-0.236602,0.97444,-0.224648,0.977126,-0.21266,0.979665,-0.20064,0.982056,-0.18859,0.984299,-0.176511,0.986393,-0.164406,0.988338,-0.152275,0.990134,-0.140122,0.991781,-0.127948,0.993278,-0.115754,0.994625,-0.103543,0.995822,-0.0913165,0.996869,-0.0790759,0.997765,-0.0668237,0.99851,-0.0545611,0.999105,-0.0422903,0.99955,-0.0300132,0.999843,-0.0177314,0.999985,-0.00544714,1,0};
constexpr float __FGE_PRIMITIVE_GEOMETRY_CONVERSION{(sizeof(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA)/(sizeof(float))-1)*6.283f};

constexpr float __FGE_W16{1.f/20.f};
constexpr float __FGE_PRIMITIVE_PRELOAD_SIMPLE_ARROW_VERTICES[]={-__FGE_W16,-1,__FGE_W16,-1,__FGE_W16,0.4,-3*__FGE_W16,0.4,0,1,3*__FGE_W16,0.4,-__FGE_W16,0.4,-__FGE_W16,-1};
constexpr unsigned int __FGE_PRIMITIVE_PRELOAD_SIMPLE_ARROW_INDICES[]={0,1,2,0,2,6,4,5,3};
constexpr float __FGE_PRIMITIVE_PRELOAD_FANCY_ARROW_VERTICES[]={-__FGE_W16,-1,__FGE_W16,-1,__FGE_W16,0.5,-__FGE_W16,0.5,-3.4*__FGE_W16,0.2,0,1,3.4*__FGE_W16,0.2,0,0.5};
constexpr unsigned int __FGE_PRIMITIVE_PRELOAD_FANCY_ARROW_INDICES[]={0,1,2,0,2,3,4,5,7,5,6,7};

/*Returns a vector of the form {cos(angle),sin(angle)} in radians
assuming: angle between 0 and 2*pi*/
constexpr FGE_FPoint __FGE_PRIMITIVE_GetCosSin(const float angle)noexcept
{
    const unsigned int projectIndex{static_cast<unsigned int>(angle*__FGE_PRIMITIVE_GEOMETRY_CONVERSION)};
    if(projectIndex%2==0)
    return {__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA[projectIndex],__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA[projectIndex+1]};

    return {__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA[projectIndex+1],__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA[projectIndex]};
}



#endif