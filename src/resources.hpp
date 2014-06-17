/*****************************************************************************
 * Joseph Zambreno
 * Department of Electrical and Computer Engineering
 * Iowa State University
 *****************************************************************************/


/*****************************************************************************
 * resources.hpp - The Fable of Zelda application. Takes as input move files
 * and an optional map file and runs a Legend of Zelda-style simulation
 * for up to four teams.
 *
 *
 * NOTES:
 * 1/24/14 by JAZ::Design created.
 *****************************************************************************/

#pragma once

/* Command types and spellings */
#define NUM_CMD_SPELLINGS 3
typedef enum {SELECT_CMD=0, MOVE_CMD, LEFT_CMD, RIGHT_CMD, ATTACK_CMD, GOTO_CMD, WAIT_CMD, ACTIVATE_CMD, DEATH_CMD, SHOOT_CMD, NUM_CMD_TYPES} CMD_TYPE;
extern std::string cmdNames[NUM_CMD_TYPES][NUM_CMD_SPELLINGS];

/* Predicate types and spellings */
#define NUM_PRED_SPELLINGS 2
typedef enum {ALWAYS_PRED=0, NEVER_PRED, READY_PRED, ALIVE_PRED, DEAD_PRED, DAMAGE_PRED, EAT_PRED, HIT_PRED, SCORE_PRED, WINNING_PRED, LOSING_PRED, EMPTY_PRED, PASSED_PRED, NUM_PRED_TYPES} PRED_TYPE;
extern std::string predNames[NUM_PRED_TYPES][NUM_PRED_SPELLINGS];


/* Sound effect file enum */
typedef enum {SFX_BIGITEM=0, SFX_SMALLITEM, SFX_LINKDIES1, SFX_LINKDIES2, NUM_SFX} SFX_ENUM;
extern std::string sfxFiles[NUM_SFX];

/* Music file enum */
typedef enum {MUSIC_MAIN=0, MUSIC_ANNIVERSARY, NUM_MUSIC} MUSIC_ENUM;
extern std::string musicFiles[NUM_MUSIC];

 /* Texture file enum */
typedef enum {TEX_BASIC_ROOM=0, TEX_BLUE_LINK, TEX_GREEN_LINK, TEX_PURPLE_LINK, TEX_RED_LINK, TEX_FONTS, TEX_RUPEE, TEX_ENEMIES, NUM_TEXTURES} TEXTURE_ENUM;
extern std::string texFiles[NUM_TEXTURES];

/* Depth enum */
typedef enum {FRONT_DEPTH=0, FONT_DEPTH=60000, OVERLAY_DEPTH=60001, CORNER_DEPTH, WALL_DEPTH, FLOOR_DEPTH, BACK_DEPTH} DEPTH_ENUM;

/* Camera state enum */
typedef enum {CAMERA_INIT=0, CAMERA_PAN_LEFT, CAMERA_PAN_RIGHT, CAMERA_PAN_UP, CAMERA_PAN_DOWN, CAMERA_ZOOM_IN, CAMERA_ZOOM_OUT, CAMERA_TEAM_1, CAMERA_TEAM_2, CAMERA_TEAM_3, CAMERA_TEAM_4, CAMERA_IDLE} CAMERA_ENUM;

/* Direction enum */
typedef enum {DIRECTION_NORTH=0, DIRECTION_EAST, DIRECTION_SOUTH, DIRECTION_WEST} DIRECTION_TYPE;
extern int16_t direction_Modifier[4][2];

/* Object Type Enum */
//Begins at the value of the first sprite
//typedef enum {CHEST_OBJ=13, CHEST_OPEN_OBJ,POT_OBJ, POT_TILE,BUTTON,TORCH_UNLIT,TORCH_LIT} OBJECT_TYPE;

/* Sprite enum for LINK objects */
typedef enum
{LINK_SLASH_NORTH_1 = 0, LINK_SLASH_NORTH_2, LINK_SLASH_NORTH_3, LINK_SLASH_NORTH_4, LINK_SLASH_NORTH_5,                                                                        //1
LINK_SLASH_NORTH_6, LINK_SLASH_NORTH_7, LINK_SLASH_NORTH_8, LINK_SLASH_NORTH_9, LINK_SLASH_NORTH_10,                                                                            //2
LINK_SLASH_NORTH_11, LINK_SLASH_NORTH_12, LINK_SLASH_NORTH_13, LINK_SLASH_NORTH_14, LINK_SLASH_NORTH_15,                                                                         //3
LINK_SLASH_NORTH_16, LINK_SLASH_NORTH_17, LINK_SLASH_NORTH_18, LINK_SLASH_NORTH_19, LINK_SLASH_NORTH_20,                                                                       //4
LINK_SLASH_WEST_1, LINK_SLASH_WEST_2, LINK_SLASH_WEST_3, LINK_SLASH_WEST_4, LINK_SLASH_WEST_5,                                                                                  //5
LINK_SLASH_WEST_6, LINK_SLASH_WEST_7, LINK_SLASH_WEST_8, LINK_SLASH_WEST_9, LINK_SLASH_WEST_10,                                                                                 //6
LINK_SLASH_WEST_11, LINK_SLASH_WEST_12, LINK_SLASH_WEST_13, LINK_SLASH_WEST_14, LINK_SLASH_WEST_15,                                                                           //7
LINK_SLASH_WEST_16, LINK_SLASH_WEST_17, LINK_SLASH_WEST_18, LINK_SLASH_WEST_19, LINK_SLASH_WEST_20,                                                                            //8
LINK_SLASH_SOUTH_1, LINK_SLASH_SOUTH_2, LINK_SLASH_SOUTH_3, LINK_SLASH_SOUTH_4, LINK_SLASH_SOUTH_5,                                                                             //9
LINK_SLASH_SOUTH_6, LINK_SLASH_SOUTH_7, LINK_SLASH_SOUTH_8, LINK_SLASH_SOUTH_9,   LINK_SLASH_SOUTH_10,                                                                            //10
LINK_SLASH_SOUTH_11, LINK_SLASH_SOUTH_12, LINK_SLASH_SOUTH_13, LINK_SLASH_SOUTH_14, LINK_SLASH_SOUTH_15,                                                                         //11
LINK_SLASH_SOUTH_16, LINK_SLASH_SOUTH_17, LINK_SLASH_SOUTH_18, LINK_SLASH_SOUTH_19, LINK_SLASH_SOUTH_20,                                                                       //12
LINK_WALKING_NORTH_1, LINK_WALKING_NORTH_2, LINK_WALKING_NORTH_3, LINK_WALKING_NORTH_4, LINK_WALKING_NORTH_5,                                                                   //13
LINK_WALKING_NORTH_6,                                                                                                                                                           //14
LINK_WALKING_WEST_1, LINK_WALKING_WEST_2, LINK_WALKING_WEST_3, LINK_WALKING_WEST_4, LINK_WALKING_WEST_5,                                                                        //15
LINK_WALKING_WEST_6,                                                                                                                                                            //16
LINK_WALKING_SOUTH_1, LINK_WALKING_SOUTH_2, LINK_WALKING_SOUTH_3, LINK_WALKING_SOUTH_4, LINK_WALKING_SOUTH_5,                                                                   //17
LINK_WALKING_SOUTH_6,                                                                                                                                                           //18
LINK_DYING_1, LINK_DYING_2, LINK_DYING_3, LINK_DYING_4, LINK_DYING_5,                                                                                                           //19
LINK_DYING_6}                                                                                                                                                                   //20
LINK_SPRITE_ENUM;
extern uint16_t link_object_spriteMap[][4];
extern uint16_t link_object_spriteMap_centers[][2];


/*Sprite enum for ROOM*/
typedef enum
{WALL_TOP_LEFT, WALL_TOP_CENTER, WALL_TOP_RIGHT, DOOR_LEFT, DOOR_TOP,                                                                                                           //1
DOOR_RIGHT, WALL_LEFT, FLOOR_TILE, WALL_RIGHT, DOOR_BOTTOM,                                                                                                                     //2
WALL_BOTTOM_LEFT, WALL_BOTTOM, WALL_BOTTOM_RIGHT, CHEST, CHEST_OPEN, POT, POT_TILE,
BUTTON, TORCH_UNLIT, TORCH_LIT,DEFAULT_BLOCK, VOID_BLOCK, RUPEE_GREEN_1,RUPEE_GREEN_2,
RUPEE_GREEN_3,RUPEE_PURPLE_1,RUPEE_PURPLE_2,RUPEE_PURPLE_3, RUPEE_BLUE_1,RUPEE_BLUE_2,
RUPEE_BLUE_3, RUPEE_ORANGE_1,RUPEE_ORANGE_2,RUPEE_ORANGE_3, RUPEE_RED_1,RUPEE_RED_2,
RUPEE_RED_3,KEY,ARROW_NORTH,ARROW_EAST,ARROW_SOUTH,ARROW_WEST}                                                                                                                   //3
ROOM_SPRITE_ENUM ;
extern uint16_t room_object_spriteMap[][4];

/* Sprite enum for FONTS */
typedef enum
{LETTER_0, LETTER_1, LETTER_2, LETTER_3, LETTER_4, LETTER_5, LETTER_6, LETTER_7, LETTER_8, LETTER_9,
LETTER_NEG, LETTER_A, LETTER_B, LETTER_C, LETTER_D, LETTER_E, LETTER_F, LETTER_G,LETTER_H, LETTER_I,
LETTER_J, LETTER_K, LETTER_L, LETTER_M, LETTER_N, LETTER_O, LETTER_P, LETTER_Q, LETTER_R, LETTER_S,
LETTER_T, LETTER_U, LETTER_V, LETTER_W, LETTER_X, LETTER_Y, LETTER_Z, LETTER_a, LETTER_b, LETTER_c,
LETTER_d, LETTER_e, LETTER_f, LETTER_g, LETTER_h, LETTER_i, LETTER_j, LETTER_k, LETTER_l, LETTER_m,
LETTER_n, LETTER_o, LETTER_p, LETTER_q, LETTER_r, LETTER_s, LETTER_t, LETTER_u, LETTER_v, LETTER_w,
LETTER_x, LETTER_y, LETTER_z, LETTER_times, LETTER_colon, LETTER_dot, NUM_FONTS}                                                                                                                                                                   //20
FONT_ENUM;
extern uint16_t font_spriteMap[][4];

/*Sprite enum for RUPEE*/
typedef enum
{RUPEE_GREEN_ONE = 0, RUPEE_GREEN_TWO, RUPEE_GREEN_THREE,
RUPEE_PURPLE_ONE, RUPEE_PURPLE_TWO, RUPEE_PURPLE_THREE,
RUPEE_BLUE_ONE, RUPEE_BLUE_TWO, RUPEE_BLUE_THREE,
RUPEE_RED_ONE, RUPEE_RED_TWO, RUPEE_RED_THREE}                                                                                                               //3
RUPEE_SPRITE_ENUM ;
extern uint16_t rupee_spriteMap[][4];

typedef enum {BSKEL=0,RSKEL,GEYEGORE,NUM_ENEMIES}ENEMY_TYPE;
extern char* enemy_filePath[NUM_ENEMIES];

typedef enum
{BSKEL_NORTH_1=0,BSKEL_NORTH_2,BSKEL_NORTH_3,
BSKEL_NORTH_ATTACK_1,BSKEL_NORTH_ATTACK_2,BSKEL_NORTH_ATTACK_3,
BSKEL_EAST_1,BSKEL_EAST_2,BSKEL_EAST_3,
BSKEL_EAST_ATTACK_1,BSKEL_EAST_ATTACK_2,BSKEL_EAST_ATTACK_3,
BSKEL_SOUTH_1,BSKEL_SOUTH_2,BSKEL_SOUTH_3,
BSKEL_SOUTH_ATTACK_1,BSKEL_SOUTH_ATTACK_2,BSKEL_SOUTH_ATTACK_3,
BSKEL_WEST_1,BSKEL_WEST_2,BSKEL_WEST_3,
BSKEL_WEST_ATTACK_1,BSKEL_WEST_ATTACK_2,BSKEL_WEST_ATTACK_,
RSKEL_NORTH_1,RSKEL_NORTH_2,RSKEL_NORTH_3,
RSKEL_NORTH_ATTACK_1,RSKEL_NORTH_ATTACK_2,RSKEL_NORTH_ATTACK_3,
RSKEL_EAST_1,RSKEL_EAST_2,RSKEL_EAST_3,
RSKEL_EAST_ATTACK_1,RSKEL_EAST_ATTACK_2,RSKEL_EAST_ATTACK_3,
RSKEL_SOUTH_1,RSKEL_SOUTH_2,RSKEL_SOUTH_3,
RSKEL_SOUTH_ATTACK_1,RSKEL_SOUTH_ATTACK_2,RSKEL_SOUTH_ATTACK_3,
RSKEL_WEST_1,RSKEL_WEST_2,RSKEL_WEST_3,
RSKEL_WEST_ATTACK_1,RSKEL_WEST_ATTACK_2,RSKEL_WEST_ATTACK_3,

GEYEGORE_NORTH_1,GEYEGORE_NORTH_2,GEYEGORE_NORTH_3,
GEYEGORE_EAST_1,GEYEGORE_EAST_2,GEYEGORE_EAST_3,
GEYEGORE_SOUTH_1,GEYEGORE_SOUTH_2,GEYEGORE_SOUTH_3,
GEYEGORE_WEST_1,GEYEGORE_WEST_2,GEYEGORE_WEST_3
} ENEMY_SPRITE_ENUM;
extern uint16_t enemy_spriteMap[][4];

/*The enemy names and their commands*/
extern char* enemyNames[NUM_ENEMIES];

/*Sets the collision type of the object.*/
typedef enum {TRANSPARENT=0,SOLID}OBJECT_STATUS;

