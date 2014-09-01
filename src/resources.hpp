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
typedef enum {SELECT_CMD=0, MOVE_CMD, LEFT_CMD, RIGHT_CMD, ATTACK_CMD, GOTO_CMD, WAIT_CMD, ACTIVATE_CMD, DEATH_CMD, SHOOT_CMD, SKIP_CMD, THROW_CMD, WARHAMMER_CMD, NUM_CMD_TYPES} CMD_TYPE;
extern std::string cmdNames[NUM_CMD_TYPES][NUM_CMD_SPELLINGS];

/* Predicate types and spellings */
#define NUM_PRED_SPELLINGS 2
typedef enum {ALWAYS_PRED=0, NEVER_PRED, READY_PRED, ALIVE_PRED, DEAD_PRED, DAMAGE_PRED, HIT_PRED, SCORE_PRED, WINNING_PRED, LOSING_PRED, BLOCKED_PRED, COLLECT_PRED, ACTIVATE_PRED, PUSHABLE_PRED, NUM_PRED_TYPES} PRED_TYPE;
extern std::string predNames[NUM_PRED_TYPES][NUM_PRED_SPELLINGS];


/* Sound effect file enum */
typedef enum {SFX_ARROWHIT, SFX_GETITEM, SFX_GETRUPEE, SFX_LINKARROW, SFX_LINKCHOKE, SFX_HEY,
SFX_LINKHURT_1, SFX_LINKSLASH_1, SFX_LINKSLASH_2, SFX_LINKSLASH3, SFX_LINKSLASH4, SFX_OPENCHEST,
SFX_STONESTEP, SFX_EYEGORE, SFX_SKELETON, SFFX_FIREBALL, SFX_ENEMYHIT, SFX_ENEMYKILL, SFX_FIREBALL,
SFX_SWTICH, SFX_EXPLOSION, SFX_THROW, SFX_HAMMER_SWING, SFX_HAMMER_HIT, NUM_SFX} SFX_ENUM;
extern std::string sfxFiles[NUM_SFX];

/* Music file enum */
//NOTE: this doesn't point anywhere yet
typedef enum {MUSIC_MAIN=0, MUSIC_ANNIVERSARY, NUM_MUSIC} MUSIC_ENUM;
extern std::string musicFiles[NUM_MUSIC];

 /* Texture file enum */
typedef enum {TEX_BASIC_ROOM=0, TEX_BLUE_LINK, TEX_GREEN_LINK, TEX_PURPLE_LINK, TEX_RED_LINK, TEX_FONTS, TEX_RUPEE, TEX_ENEMIES, TEX_NAVI, NUM_TEXTURES} TEXTURE_ENUM;
extern std::string texFiles[NUM_TEXTURES];

/* Depth enum */
typedef enum {FONT_DEPTH=60000, OVERLAY_DEPTH=60001, FRONT_DEPTH,OBJECT_DEPTH, CORNER_DEPTH, WALL_DEPTH, FLOOR_DEPTH, BACK_DEPTH} DEPTH_ENUM;

/* Camera state enum */
typedef enum {CAMERA_INIT=0, CAMERA_PAN_LEFT, CAMERA_PAN_RIGHT, CAMERA_PAN_UP, CAMERA_PAN_DOWN, CAMERA_ZOOM_IN, CAMERA_ZOOM_OUT, CAMERA_TEAM_1, CAMERA_TEAM_2, CAMERA_TEAM_3, CAMERA_TEAM_4, CAMERA_IDLE, CAMERA_NEXT_LINK, CAMERA_PREV_LINK} CAMERA_ENUM;

/* Camera zoom distance enum*/
typedef enum {ZOOM_FAR=0, ZOOM_MID, ZOOM_CLOSE} CAMERA_ZOOM;

/* Direction enum */
typedef enum {DIRECTION_NORTH=0, DIRECTION_EAST, DIRECTION_SOUTH, DIRECTION_WEST} DIRECTION_TYPE;
extern int16_t direction_Modifier[4][2];

/* Sprite enum for LINK objects */
typedef enum
{LINK_SLASH_NORTH_1 = 0, LINK_SLASH_NORTH_2, LINK_SLASH_NORTH_3, LINK_SLASH_NORTH_4, LINK_SLASH_NORTH_5,
LINK_SLASH_NORTH_6, LINK_SLASH_NORTH_7, LINK_SLASH_NORTH_8, LINK_SLASH_NORTH_9, LINK_SLASH_NORTH_10,
LINK_SLASH_NORTH_11, LINK_SLASH_NORTH_12, LINK_SLASH_NORTH_13, LINK_SLASH_NORTH_14, LINK_SLASH_NORTH_15,
LINK_SLASH_NORTH_16, LINK_SLASH_NORTH_17, LINK_SLASH_NORTH_18, LINK_SLASH_NORTH_19, LINK_SLASH_NORTH_20,

LINK_SLASH_WEST_1, LINK_SLASH_WEST_2, LINK_SLASH_WEST_3, LINK_SLASH_WEST_4, LINK_SLASH_WEST_5,
LINK_SLASH_WEST_6, LINK_SLASH_WEST_7, LINK_SLASH_WEST_8, LINK_SLASH_WEST_9, LINK_SLASH_WEST_10,
LINK_SLASH_WEST_11, LINK_SLASH_WEST_12, LINK_SLASH_WEST_13, LINK_SLASH_WEST_14, LINK_SLASH_WEST_15,
LINK_SLASH_WEST_16, LINK_SLASH_WEST_17, LINK_SLASH_WEST_18, LINK_SLASH_WEST_19, LINK_SLASH_WEST_20,

LINK_SLASH_SOUTH_1, LINK_SLASH_SOUTH_2, LINK_SLASH_SOUTH_3, LINK_SLASH_SOUTH_4, LINK_SLASH_SOUTH_5,
LINK_SLASH_SOUTH_6, LINK_SLASH_SOUTH_7, LINK_SLASH_SOUTH_8, LINK_SLASH_SOUTH_9,   LINK_SLASH_SOUTH_10,
LINK_SLASH_SOUTH_11, LINK_SLASH_SOUTH_12, LINK_SLASH_SOUTH_13, LINK_SLASH_SOUTH_14, LINK_SLASH_SOUTH_15,
LINK_SLASH_SOUTH_16, LINK_SLASH_SOUTH_17, LINK_SLASH_SOUTH_18, LINK_SLASH_SOUTH_19, LINK_SLASH_SOUTH_20,

LINK_WALKING_NORTH_1, LINK_WALKING_NORTH_2, LINK_WALKING_NORTH_3, LINK_WALKING_NORTH_4, LINK_WALKING_NORTH_5,LINK_WALKING_NORTH_6,                                                                                                                                                          //14
LINK_WALKING_WEST_1, LINK_WALKING_WEST_2, LINK_WALKING_WEST_3, LINK_WALKING_WEST_4, LINK_WALKING_WEST_5,LINK_WALKING_WEST_6,                                                                                                                                                            //16
LINK_WALKING_SOUTH_1, LINK_WALKING_SOUTH_2, LINK_WALKING_SOUTH_3, LINK_WALKING_SOUTH_4, LINK_WALKING_SOUTH_5,LINK_WALKING_SOUTH_6,

LINK_DYING_1, LINK_DYING_2, LINK_DYING_3, LINK_DYING_4, LINK_DYING_5,

LINK_DYING_6,LINK_ARROW_NORTH_1,LINK_ARROW_NORTH_2,LINK_ARROW_NORTH_3,LINK_ARROW_NORTH_4,LINK_ARROW_NORTH_5,LINK_ARROW_NORTH_6,
LINK_ARROW_WEST_1,LINK_ARROW_WEST_2,LINK_ARROW_WEST_3,LINK_ARROW_WEST_4,LINK_ARROW_WEST_5,LINK_ARROW_WEST_6,
LINK_ARROW_SOUTH_1,LINK_ARROW_SOUTH_2,LINK_ARROW_SOUTH_3,LINK_ARROW_SOUTH_4,LINK_ARROW_SOUTH_5,LINK_ARROW_SOUTH_6,
LINK_THROW_NORTH_1,LINK_THROW_NORTH_2,LINK_THROW_NORTH_3,LINK_THROW_NORTH_4,LINK_THROW_NORTH_5,LINK_THROW_NORTH_6,
LINK_THROW_WEST_1,LINK_THROW_WEST_2,LINK_THROW_WEST_3,LINK_THROW_WEST_4,LINK_THROW_WEST_5,LINK_THROW_WEST_6,
LINK_THROW_SOUTH_1,LINK_THROW_SOUTH_2,LINK_THROW_SOUTH_3,LINK_THROW_SOUTH_4,LINK_THROW_SOUTH_5,LINK_THROW_SOUTH_6,

LINK_WARHAMMER_NORTH_1,LINK_WARHAMMER_NORTH_2,LINK_WARHAMMER_NORTH_3,LINK_WARHAMMER_NORTH_4,LINK_WARHAMMER_NORTH_5,LINK_WARHAMMER_NORTH_6,
LINK_WARHAMMER_WEST_1,LINK_WARHAMMER_WEST_2,LINK_WARHAMMER_WEST_3,LINK_WARHAMMER_WEST_4,LINK_WARHAMMER_WEST_5,LINK_WARHAMMER_WEST_6,
LINK_WARHAMMER_SOUTH_1,LINK_WARHAMMER_SOUTH_2,LINK_WARHAMMER_SOUTH_3,LINK_WARHAMMER_SOUTH_4,LINK_WARHAMMER_SOUTH_5,LINK_WARHAMMER_SOUTH_6
}
LINK_SPRITE_ENUM;
extern uint16_t link_object_spriteMap[][4];

extern int16_t link_sprite_move[][2];
;extern uint16_t link_object_spriteMap_centers[][2];

/*Sprite for Navi enum*/
typedef enum
{GREEN_NAVI_1, GREEN_NAVI_2, GREEN_NAVI_3, GREEN_NAVI_4, GREEN_NAVI_5, GREEN_NAVI_6,
PURPLE_NAVI_1, PURPLE_NAVI_2, PURPLE_NAVI_3, PURPLE_NAVI_4, PURPLE_NAVI_5, PURPLE_NAVI_6,
BLUE_NAVI_1, BLUE_NAVI_2, BLUE_NAVI_3, BLUE_NAVI_4, BLUE_NAVI_5, BLUE_NAVI_6,
RED_NAVI_1, RED_NAVI_2, RED_NAVI_3,RED_NAVI_4, RED_NAVI_5, RED_NAVI_6
} NAVI_SPRITE_ENUM;
extern uint16_t navi_object_spriteMap[][4];

/*Sprite enum for ROOM*/
typedef enum
{WALL_TOP_LEFT,     WALL_TOP_CENTER,   WALL_TOP_RIGHT,     DOOR_LEFT,      DOOR_TOP,        //0-4
 DOOR_RIGHT,        WALL_LEFT,         FLOOR_TILE,         WALL_RIGHT,     DOOR_BOTTOM,     //5-9
 WALL_BOTTOM_LEFT,  WALL_BOTTOM,       WALL_BOTTOM_RIGHT,  CHEST,          CHEST_OPEN,      //10-14
 POT,               POT_TILE,          BUTTON,             TORCH_UNLIT,    TORCH_LIT,       //15-19
 DEFAULT_BLOCK,     VOID_BLOCK,        RUPEE_GREEN_1,      RUPEE_GREEN_2,  RUPEE_GREEN_3,   //20-14
 RUPEE_PURPLE_1,    RUPEE_PURPLE_2,    RUPEE_PURPLE_3,     RUPEE_BLUE_1,   RUPEE_BLUE_2,    //25-29
 RUPEE_BLUE_3,      RUPEE_ORANGE_1,    RUPEE_ORANGE_2,     RUPEE_ORANGE_3, RUPEE_RED_1,     //30-34
 RUPEE_RED_2,       RUPEE_RED_3,       KEY,                ARROW_NORTH,    ARROW_EAST,      //35-39
 ARROW_SOUTH,       ARROW_WEST,        FIREBALL_NORTH,     FIREBALL_EAST,  FIREBALL_SOUTH,  //40-44
 FIREBALL_WEST,     BOMB_1,            BOMB_2,             BOMB_3,         BOMB_4,          //45-49
 BOMB_5,            BOMB_6,            BOMB_7,             BOMB_8,         BOMB_9,          //50-54
 GOLD_BLOCK,        LEVER_OFF,         LEVER_ON,           SMALL_ROOM
}
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
LETTER_x, LETTER_y, LETTER_z, LETTER_times, LETTER_colon, LETTER_dot, NUM_FONTS, GRADIENT,GRASS}                                                                                                                                                                   //20
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
/*Blue skeleton*/
{BSKEL_NORTH_1=0,BSKEL_NORTH_2,BSKEL_NORTH_3,
BSKEL_NORTH_ATTACK_1,BSKEL_NORTH_ATTACK_2,BSKEL_NORTH_ATTACK_3,
BSKEL_EAST_1,BSKEL_EAST_2,BSKEL_EAST_3,
BSKEL_EAST_ATTACK_1,BSKEL_EAST_ATTACK_2,BSKEL_EAST_ATTACK_3,
BSKEL_SOUTH_1,BSKEL_SOUTH_2,BSKEL_SOUTH_3,
BSKEL_SOUTH_ATTACK_1,BSKEL_SOUTH_ATTACK_2,BSKEL_SOUTH_ATTACK_3,
BSKEL_WEST_1,BSKEL_WEST_2,BSKEL_WEST_3,
BSKEL_WEST_ATTACK_1,BSKEL_WEST_ATTACK_2,BSKEL_WEST_ATTACK_,
/*Red Skeleton*/
RSKEL_NORTH_1,RSKEL_NORTH_2,RSKEL_NORTH_3,
RSKEL_NORTH_ATTACK_1,RSKEL_NORTH_ATTACK_2,RSKEL_NORTH_ATTACK_3,
RSKEL_EAST_1,RSKEL_EAST_2,RSKEL_EAST_3,
RSKEL_EAST_ATTACK_1,RSKEL_EAST_ATTACK_2,RSKEL_EAST_ATTACK_3,
RSKEL_SOUTH_1,RSKEL_SOUTH_2,RSKEL_SOUTH_3,
RSKEL_SOUTH_ATTACK_1,RSKEL_SOUTH_ATTACK_2,RSKEL_SOUTH_ATTACK_3,
RSKEL_WEST_1,RSKEL_WEST_2,RSKEL_WEST_3,
RSKEL_WEST_ATTACK_1,RSKEL_WEST_ATTACK_2,RSKEL_WEST_ATTACK_3,
/*Green Eyegore*/
GEYEGORE_NORTH_1,GEYEGORE_NORTH_2,GEYEGORE_NORTH_3,
GEYEGORE_EAST_1,GEYEGORE_EAST_2,GEYEGORE_EAST_3,
GEYEGORE_SOUTH_1,GEYEGORE_SOUTH_2,GEYEGORE_SOUTH_3,
GEYEGORE_WEST_1,GEYEGORE_WEST_2,GEYEGORE_WEST_3,
GEYEGORE_NORTH_ATTACK_1,GEYEGORE_NORTH_ATTACK_2,GEYEGORE_NORTH_ATTACK_3,
GEYEGORE_EAST_ATTACK_1,GEYEGORE_EAST_ATTACK_2,GEYEGORE_EAST_ATTACK_3,
GEYEGORE_SOUTH_ATTACK_1,GEYEGORE_SOUTH_ATTACK_2,GEYEGORE_SOUTH_ATTACK_3,
GEYEGORE_WEST_ATTACK_1,GEYEGORE_WEST_ATTACK_2,GEYEGORE_WEST_ATTACK_3
} ENEMY_SPRITE_ENUM;
extern uint16_t enemy_spriteMap[][4];

/*The enemy names and their commands*/
extern char* enemyNames[NUM_ENEMIES];

/*Put the amount of damage any enemy is supposed to do on a given attack here*/
extern uint8_t enemyDamage[NUM_ENEMIES];

/*Sets the collision type of the object.*/
typedef enum {TRANSPARENT=0,SOLID}OBJECT_STATUS;
