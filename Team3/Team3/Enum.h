#pragma once

enum DIRECTION { DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_END };


enum BULLET_TYPE { PLAYER_BULLET, MONSTER_BULLET, BULLET_END};
enum OBJID { OBJ_PLAYER, OBJ_ITEM, OBJ_WALL, OBJ_BULLET, OBJ_MONSTER, OBJ_MONSTERBULLET, OBJ_MOUSE, OBJ_SHIELD, OBJ_BUTTON, OBJ_END };

enum TILETYPE { TILE_A, TILE_B, TILE_C, TILE_D, TILE_E, TILE_F, TILE_G, TILE_END };

//enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE, SC_END };

enum UIID { UI_FRONT, UI_BACK, UI_END };

enum RENDERID { RENDER_BACKGROUND, RENDER_GAMEOBJECT, RENDER_EFFECT, RENDER_UI, RENDER_END };

enum GAMESCENE { GAME_MENU, GAME_JUNKYU, GAME_SEOKGYUN, GAME_HAEHO, GAME_SON, GAME_END };