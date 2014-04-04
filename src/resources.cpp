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
    {"swing", "fire", "action"},
    {"goto", "jump", "loop"}
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
    "sprites/fonts.png"
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
{585,72,619,101}	,{633,72,668,93}  	  ,{677,72,710,93}		,{720,70,474,93}	  ,{769,66,787,93} 		, //8
{5,166,23,142}      ,{37,116,55,151}	  ,{73,115,91,156}		,{113,117,131,150}	  ,{150,116,168,149}	, //9
{178,115,204,140}	,{220,114,242,145}	  ,{257,112,276,150}	,{296,112,314,153}	  ,{335,114,358,151}	, //10
{374,117,403,148}	,{414,117,446,147}	  ,{460,112,489,141}    ,{507,116,540,141}	  ,{552,117,581,144}	, //11
{597,115,626,154}	,{649,114,667,156}	  ,{692,115,711,155}	,{726,119,748,150}	  ,{760,118,786,142}	, //12
{9,187,27,211}      ,{40,184,58,211}      ,{73,186,91,211}      ,{105,187,123,211}    ,{137,184,155,211}    , //13
{173,186,191,211}   ,                                                                                         //14
{7,216,26,239}      ,{38,217,61,239}      ,{70,217,94,239}      ,{104,216,123,239}    ,{133,217,156,239}    , //15
{171,217,195,239}   ,                                                                                         //16
{7,245,25,274}      ,{38,243,56,271}      ,{68,246,86,271}      ,{102,246,120,275}    ,{134,245,152,273}    , //17
{171,248,189,273}   ,                                                                                         //18
{697,191,715,215}   ,{720,191,736,215}    ,{740,192,758,215}    ,{763,192,779,215}    ,{783,195,801,215}    , //19
{805,199,829,215}                                                                                             //20

};
uint16_t link_object_spriteMap_centers[][2] = {
{12,33} , {45,33}, {80,33}, {121,33}, {157,33},
{192,33}, {230,33}, {265,33}, {303,33}, {342,33},
{383,33}, {425,33}, {473,42}, {517,33}, {563,33},
{606,33}, {655,33}, {699,33}, {737,33}, {776,33}

};


/* Sprite map for Fonts */
uint16_t Font_spriteMap[][4] = {
{70,187,105,232}   ,{128,188,163,233}   ,{185,187,220,232}   ,{243,188,278,233}    ,{12,246,47,291}   ,
{70,246,105,291}   ,{128,245,163,290}   ,{184,246,219,291}   ,{243,245,278,290}    ,{11,300,46,345}   ,
{185,141,220,186}

};


/* Sprite map for ROOM objects */
uint16_t room_object_spriteMap[][4] = {
{11,10,260,259}		,{282,10,340,229}	  ,{365,10,614,259}		,{665,152,741,269}    ,{705,41,821,116}	    ,//1
{787,156,863,273}   ,{11,270,230,328}	  ,{280,271,338,329}    ,{395,278,614,336}	  ,{714,297,831,371}	,//2
{11,347,260,596}	,{283,377,341,596}    ,{365,347,614,596}    ,{622,438,679,495}  						 //3

};











