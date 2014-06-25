/*****************************************************************************
 * Joseph Zambreno
 * Department of Electrical and Computer Engineering
 * Iowa State University
 *****************************************************************************/


/*****************************************************************************
 * fableofzelma.cpp - The Fable of Zelda application. Takes as input move files
 * and an optional map file and runs a Legend of Zelda-style simulation
 * for up to four teams.
 *
 *
 * NOTES:
 * 1/24/14 by JAZ::Design created.
 *****************************************************************************/


#include "fableofzelma.hpp"


/* Command spellings - note that you can't have command spelling that
 * contains a subset of another command spelling */
std::string cmdNames[NUM_CMD_TYPES][NUM_CMD_SPELLINGS] = {
    {"select", "buy", "use"},
    {"move", "run", "walk"},
    {"left", "ccw", "west"},
    {"right", "clock", "east"},
    {"attack","swing", "action"},
    {"goto", "jump", "loop"},
    {"wait", "pause","hold"},
    {"activate","open","push"},
    {"death","remove","kill"},
    {"shoot","projectile","cast"}
    };

/* Predicate spellings */
std::string predNames[NUM_PRED_TYPES][NUM_PRED_SPELLINGS] = {
    {"always", "true"},
    {"never", "false"},
    {"ready", "free"},
    {"alive", "active"},
    {"dead", "inactive"},
    {"damage", "damaged"},
    {"eaten", "alive"},
    {"hit", "contact"},
    {"score", "scored"},
    {"winning", "leading"},
    {"losing", "trailing"},
    {"empty", "free"},
    {"passed", "behind"}
    };


/* Texture files */
std::string texFiles[NUM_TEXTURES] = {
    "sprites/basic_room.png",
    "sprites/blue_link.png",
    "sprites/green_link.png",
    "sprites/purple_link.png",
    "sprites/red_link.png",
    "sprites/fonts.png",
    "sprites/rupee.png",
    "sprites/enemies.png"
    };

std::string sfxFiles[NUM_SFX]{
    "audio/arrowHit.ogg",
    "audio/getItem.ogg",
    "audio/getRupee.ogg",
    "audio/linkArrow.ogg",
    "audio/linkChoke.ogg",
    "audio/linkHey.ogg",
    "audio/linkHurt1.ogg",
    "audio/linkSlash1.ogg",
    "audio/linkSlash2.ogg",
    "audio/linkSlash3.ogg",
    "audio/linkSlash4.ogg",
    "audio/openChest.ogg",
    "audio/stoneStep.ogg",
    "audio/eyegoreAttack.wav",
    "audio/skelAttack.wav",
    "audio/shootFire.wav",
    "audio/enemyHit.wav",
    "audio/enemyKill.wav"
};
/* Sprite map for LINK objects */
uint16_t link_object_spriteMap[][4] = {
{4,23,22,46}        ,{36,17,54,46}        ,{71,10,88,46}        ,{112,16,130,45}      ,{148,18,166,46}      , //1
{183,22,208,46}	    ,{221,22,244,47}	  ,{256,15,278,47}	    ,{294,11,312,47}	  ,{329,15,351,47}	    , //2
{363,22,392,47}	    ,{401,23,434,47}	  ,{454,23,482,53}	    ,{493,23,526,47}	  ,{542,21,572,47}	    , //3
{587,12,615,47}	    ,{646,9,664,47}	      ,{690,12,708,47}	    ,{728,20,749,47}	      ,{767,23,792,47}		, //4
{4,70,23,93}		,{27,71,58,93}		  ,{60,73,95,93}		,{104,70,131,93}	  ,{141,70,168,93}		, //5
{184,67,203,93}		,{216,70,242,93}	  ,{247,70,280,93}		,{283,71,317,93}	  ,{324,71,354,94}  	, //6
{371,70,394,100}	,{417,70,434,101}	  ,{462,69,488,98}		,{508,69,525,101}	  ,{547,70,570,100}		, //7
{585,72,619,101}	,{633,72,668,93}  	  ,{677,72,710,93}		,{720,70,747,93}	  ,{769,66,787,93} 		, //8
{5,116,23,142}      ,{37,116,55,151}	  ,{73,115,91,156}		,{113,117,131,150}	  ,{150,116,168,149}	, //9
{178,115,204,140}	,{220,114,242,145}	  ,{257,112,276,150}	,{296,112,314,153}	  ,{335,114,358,151}	, //10
{374,117,403,148}	,{414,117,446,141}	  ,{460,112,489,142}    ,{507,116,540,141}	  ,{552,117,581,144}	, //11
{597,115,626,154}	,{649,114,667,156}	  ,{692,115,710,155}	,{726,119,748,150}	  ,{760,118,786,142}	, //12
{9,187,27,211}      ,{40,184,58,211}      ,{73,186,91,211}      ,{105,187,123,211}    ,{137,184,155,211}    , //13
{173,186,191,211}   ,                                                                                         //14
{7,216,26,239}      ,{38,217,61,239}      ,{70,217,94,239}      ,{104,216,123,239}    ,{133,217,156,239}    , //15
{171,217,195,239}   ,                                                                                         //16
{7,245,25,274}      ,{38,243,56,271}      ,{68,246,86,271}      ,{102,246,120,275}    ,{134,245,152,273}    , //17
{171,248,189,273}   ,                                                                                         //18
{697,191,715,215}   ,{720,191,736,215}    ,{740,192,758,215}    ,{763,192,779,215}    ,{783,195,801,215}    , //19
{805,199,829,215}   ,{11,309,36,340}      ,{37,309,62,340}      ,{63,309,88,340}      ,{89,309,114,340}     , //20
{115,309,140,340}   ,{141,309,166,340}    ,{3,342,31,373}       ,{32,342,60,373}      ,{61,342,89,373}      ,
{90,342,118,373}    ,{119,342,147,373}    ,{148,342,176,373}    ,{13,372,38,403}      ,{39,372,64,403}      ,
{65,372,90,403}     ,{91,372,116,403}     ,{117,372,142,403}    ,{143,372,168,403}
};

uint16_t link_object_spriteMap_centers[][2] = {
{12,33} , {45,33}, {80,33}, {121,33}, {157,33},
{192,33}, {230,33}, {265,33}, {303,33}, {342,33},
{383,33}, {425,33}, {473,42}/*this one*/, {517,33}, {563,33},
{606,33}, {655,33}, {699,33}, {737,33}, {776,33},
{15,81}, {48,83}, {84,84}, {124,82}, {161,82},
{196,82}, {234,82}, {269,82}, {306,83}, {345,83},
{386,82}, {426,82}, {472,82}, {517,82}, {563,83},
{609,84}, {658,84}, {700,84}, {739,83}, {780,83},
{15,128}, {47,128}, {83,127}, {123,128}, {160,127},
{196,127}, {234,127}, {268,127}, {306,125}, {346,127},
{384,128}, {424,128}, {470,128}, {517,128}, {562,128},
{607,128}, {659,128}, {702,128}, {740,131}, {778,130}
};

/* Sprite map for fonts */
uint16_t font_spriteMap[][4] = {
{70,187,105,232}   ,{128,188,163,233}   ,{185,187,220,232}   ,{243,188,278,233}    ,{12,246,47,291}   ,
{70,246,105,291}   ,{128,245,163,290}   ,{184,246,219,291}   ,{243,245,278,290}    ,{11,300,46,345}   ,
{185,141,220,186}  ,{475,0,515,44}      ,{533,0,573,44}      ,{301,58,341,102}     ,{359,58,399,102}  ,
{417,58,457,102}   ,{475,58,515,102}    ,{532,58,572,102}    ,{301,115,341,159}    ,{360,115,400,159} , // Ends with 'I'
{417,115,457,159}  ,{474,115,514,159}   ,{533,115,573,159}   ,{298,172,344,216}    ,{360,173,400,217} , // Ends with 'N'
{417,173,457,217}  ,{475,173,515,217}   ,{532,173,572,217}   ,{302,232,342,276}    ,{360,230,400,274} , // Ends with 'S'
{417,231,457,275}  ,{475,231,515,275}   ,{532,230,572,274}   ,{297,288,346,332}    ,{359,289,399,333} , // Ends with 'X'
{416,288,456,332}  ,{475,289,515,333}   ,{592,0,632,42}      ,{650,0,690,42}       ,{709,0,748,42}    , // Ends with 'c'
{764,0,804,42}     ,{823,0,863,42}      ,{594,55,630,99}     ,{649,62,689,108}     ,{709,55,745,99}   , // Ends with 'h'
{769,55,801,99}    ,{827,56,861,106}    ,{593,113,630,157}   ,{654,112,686,156}    ,{705,113,749,157} , // Ends with 'm'
{767,116,803,157}  ,{825,115,860,157}   ,{593,177,633,222}   ,{652,176,689,221}    ,{710,172,740,214} , // Ends with 'r'
{767,175,803,212}  ,{828,174,859,214}   ,{594,231,632,272}   ,{651,230,687,272}    ,{706,231,748,273} ,
{766,231,803,272}  ,{824,237,860,279}   ,{596,289,628,329}   ,{0,0,68,62}          ,{62,295,109,353}  ,
{240,127,278,178}

};


/* Sprite map for ROOM objects */
uint16_t room_object_spriteMap[][4] = {
{11,10,260,259}		,{282,10,340,229}	  ,{365,10,614,259}		,{665,152,741,269}    ,{705,41,821,116}	    ,//0-4
{787,156,863,273}   ,{11,270,230,328}	  ,{280,271,338,329}    ,{395,278,614,336}	  ,{714,297,831,371}	,//5-9
{11,347,260,596}	,{283,377,341,596}    ,{365,347,614,596}    ,{622,438,680,496}    ,{686,438,745,499}    ,//10-14
{622,374,680,432}   ,{686,374,744,432}    ,{750,374,808,432}    ,{750,438,808,496}    ,{750,502,808,560}    ,//15-19
{686,502,744,560}   ,{622,502,680,560}    ,{2,854,36,918}       ,{44,854,78,918}      ,{87,854,121,918}     ,//20-24
{129,854,163,918}   ,{171,854,208,918}    ,{216,854,251,918}    ,{2,924,36,987}       ,{44,924,78,987}      ,//25-29
{87,924,121,987}    ,{129,924,163,987}    ,{171,924,208,987}    ,{216,924,247,987}    ,{2,993,36,1057}      ,//30-34
{44,993,78,1057}    ,{87,993,121,1057}    ,{622,564,680,622}    ,{346,607,403,664}    ,{404,607,461,664}    ,//35-39
{462,607,519,664}   ,{288,607,345,664} //40-41
};

uint16_t rupee_spriteMap[][4] = {
{23,32,58,97}   ,{65,32,100,97}   ,{108,32,143,97}   , // Green
{150,32,185,97} ,{192,32,227,97}  ,{235,32,270,97}   , // Purple
{23,102,58,167} ,{65,102,100,167} ,{108,102,143,167} , // Blue
{23,171,58,236} ,{65,171,100,236} ,{108,171,143,236}   // Red
};

uint16_t enemy_spriteMap[][4] = {
//BSKEL
{48,3,63,28},{64,3,79,28},{80,3,95,28},
{240,3,255,28},{256,3,271,28},{272,3,287,28},
{0,3,15,28},{16,3,31,28},{32,3,47,28},
{192,3,207,28},{208,3,223,28},{224,3,239,28},
{96,3,111,28},{112,3,127,28},{128,3,143,28},
{288,3,303,28},{304,3,319,28},{320,3,335,28},
{144,3,159,28},{160,3,175,28},{176,3,191,28},
{336,3,351,28},{352,3,367,28},{368,3,383,28},
//RSKEL
{48,32,63,57},{64,32,79,57},{80,32,95,57},
{240,32,255,57},{256,32,271,57},{272,32,287,57},
{0  ,32,15 ,57},{16 ,32,31 ,57},{32 ,32,47 ,57},
{192,32,207,57},{208,32,223,57},{224,32,239,57},
{96 ,32,111,57},{112,32,127,57},{128,32,143,57},
{288,32,303,57},{304,32,319,57},{320,32,335,57},
{144,32,159,57},{160,32,175,57},{176,32,191,57},
{336,32,351,57},{352,32,367,57},{368,32,383,57},
//GREEN_EYEGORE
{168,62,191,86},{192,62,215,86},{216,62,239,86},
{48,62,71,86}, {72,62,95,86},  {48,62,71,86},
{96,62,119,86},{120,62,143,86},{144,62,167,86},
{240,62,263,86},{264,62,287,86},{240,62,263,86},
{264,62,287,86},{288,62,311,86},{312,62,335,86},
{336,62,359,86},{360,62,383,86},{384,62,407,86},
{408,62,431,86},{432,62,455,86},{456,62,479,86}
};

char* enemy_filePath[NUM_ENEMIES] {
    "scripts/enemies/blue_skel_commands.zef",
    "scripts/enemies/red_skel_commands.zef",
    "scripts/enemies/green_eyegore_commands.zef"
};

char* enemyNames[NUM_ENEMIES] {
    "blue_skel","red_skel","green_eyegore"
};

uint8_t enemyDamage[NUM_ENEMIES]{
    10,10,30
};

int16_t direction_Modifier[4][2] = {
{0,1},{1,0},{0,-1},{-1,0}
};











