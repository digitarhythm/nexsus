/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.06.22
 User's Constractor(source)

********************************************************************
********************************************************************
********************************************************************/

#include <stdio.h>
#include <SDL.h>

#include "nexsusdev.h"

/*******************************************************************
 初期化する為の設定をする
 返値	 0:正常終了
 		-1:メモリが足りない
********************************************************************/
short NX_UserDefined( NX_SYSTEM_INFO *sysinfo, int argc, char *argv[] )
{
	Uint32	fscrn;

	fscrn = 0;
	if( argc > 1 ){
		if( strcmp( argv[ 1 ], "-fs" ) == 0 ){
			fscrn = SDL_FULLSCREEN;
		}
	}

	// システム情報を登録する
	sysinfo -> AUDIO = 1;								// オーディオの初期化(0=しない/1=する)
	sysinfo -> VIDEO = 1;								// ビデオの初期化(0=しない/1=する)
	sysinfo -> CDROM = 1;								// CD-ROMの初期化(0=しない/1=する)
	sysinfo -> TIMER = 1;								// タイマーの初期化(0=しない/1=する)
	sysinfo -> JSTCK = 1;								// ジョイスティックの初期化(0=しない/1=する)
	sysinfo -> WIDTH = 240;								// 画面の横幅
	sysinfo -> HEIGHT = 320;							// 画面の縦
	sysinfo -> SCREENMODE = SDL_ANYFORMAT | SDL_ASYNCBLIT | SDL_DOUBLEBUF | fscrn;			// 画面モード
	sysinfo -> OBJECTNUM = 256;							// 作成するオブジェクトの数
	strcpy( sysinfo -> CHARACTERFNAME, "chara.bmp" );	// 使用する二次元キャラクタファイル名
//	strcpy( sysinfo -> CHARACTERFNAME, "chara.png" );	// 使用する二次元キャラクタファイル名
	strcpy( sysinfo -> MAPFNAME, "chara.map" );			// キャラクタ定義ファイル名
	sysinfo -> mouse = 0;								// マウスカーソル表示フラグ

	// アニメパターンを登録する
	sysinfo -> ANIMENUM = 256;							// アニメパターンの数
	if( NX_SetAnimePattern( "0,1,2,3,4,5,6,7", "30,30,30,30,30,30,30,30" ) == -1 ){ return -1; }
	if( NX_SetAnimePattern( "7,6,5,4,3,2,1,0", "30,30,30,30,30,30,30,30" ) == -1 ){ return -1; }
	if( NX_SetAnimePattern( "8", "1000" ) == -1 ){ return -1; }
	if( NX_SetAnimePattern( "9", "1000" ) == -1 ){ return -1; }
	if( NX_SetAnimePattern( "10", "1000" ) == -1 ){ return -1; }
	if( NX_SetAnimePattern( "0", "1000" ) == -1 ){ return -1; }
	if( NX_SetAnimePattern( "11,12,13", "60,60,60" ) == -1 ){ return -1; }
	if( NX_SetAnimePattern( "14", "1000" ) == -1 ){ return -1; }
	if( NX_SetAnimePattern( "14,15,16,17,18,19,20,21", "30,30,30,30,30,30,30,30" ) == -1 ){ return -1; }
	if( NX_SetAnimePattern( "21,20,19,18,17,16,15,14", "30,30,30,30,30,30,30,30" ) == -1 ){ return -1; }

	return 0;
}
/**/
