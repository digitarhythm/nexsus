/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.06.22
 system main process

********************************************************************
********************************************************************
********************************************************************/

#include <stdlib.h>
//#include <gtk/gtk.h>
#include <SDL.h>

#include "nexsusdev.h"

extern mfunc  enemy;
extern mfunc  enemy2;
extern mfunc  wall;
extern mfunc  myship;
extern mfunc  missile_control;

short mcp;		// ミサイルコントロールオブジェクト番号格納用
short mship;	// 自機オブジェクト番号格納用

int main( int argc, char *argv[] )
{
	NX_Rect	rect;
	Puserparam tmp;

	// argment initialize
	NX_ArgInit( &argc, &argv );

	// Init System
	if( NX_SystemInit( &argc, &argv ) < 0 ){ // Error
		exit( 1 );
	}

NX_AddObject( 0, -320, 0, 0, 1, 0, 0, NX_ANIME, -1, 2, 1, 1, 1, 0, NULL, wall );
NX_AddObject( 0,    0, 0, 0, 1, 0, 0, NX_ANIME, -1, 2, 1, 1, 1, 0, NULL, wall );

rect.x1 = 17; rect.y1 = 17; rect.x2 = 18; rect.y2 = 18;
mship = NX_AddObject( 96, 240, 0, 0, 0, 0, 0, NX_ANIME, -1, 3, 1, 1, 1, 1, &rect, myship );
tmp = NX_GetObjectStructure( mship );
tmp -> processnum = 98;
tmp -> visible = 0;

mcp = NX_AddObject( 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 1, NULL, missile_control );

rect.x1 = 10; rect.y1 = 10; rect.x2 = 21; rect.y2 = 24;
NX_AddObject( NX_GetRandom( 40, 200 ), -32, 0, 0, NX_GetRandom( 10, 20 ), 0, 0, NX_ANIME, -1, 7, 1, 1, 1, 1, &rect, enemy );
NX_AddObject( NX_GetRandom( 40, 200 ), -32, 0, 0, NX_GetRandom( 10, 20 ), 0, 0, NX_ANIME, -1, 7, 1, 1, 1, 1, &rect, enemy );
NX_AddObject( NX_GetRandom( 40, 200 ), -32, 0, 0, NX_GetRandom( 10, 20 ), 0, 0, NX_ANIME, -1, 7, 1, 1, 1, 1, &rect, enemy );
NX_AddObject( NX_GetRandom( 40, 200 ), -32, 0, 0, NX_GetRandom( 10, 20 ), 0, 0, NX_ANIME, -1, 7, 1, 1, 1, 1, &rect, enemy );
NX_AddObject( NX_GetRandom( 40, 200 ), -32, 0, 0, NX_GetRandom( 5, 8 ), 0, 0, NX_ANIME, -1, 5, 1, 1, 1, 1, &rect, enemy2 );
NX_AddObject( NX_GetRandom( 40, 200 ), -32, 0, 0, NX_GetRandom( 5, 8 ), 0, 0, NX_ANIME, -1, 5, 1, 1, 1, 1, &rect, enemy2 );
NX_AddObject( NX_GetRandom( 40, 200 ), -32, 0, 0, NX_GetRandom( 5, 8 ), 0, 0, NX_ANIME, -1, 5, 1, 1, 1, 1, &rect, enemy2 );
NX_AddObject( NX_GetRandom( 40, 200 ), -32, 0, 0, NX_GetRandom( 5, 8 ), 0, 0, NX_ANIME, -1, 5, 1, 1, 1, 1, &rect, enemy2 );

	NX_MainLoop();

	// End System
	NX_SystemTerm();
}
/**/

