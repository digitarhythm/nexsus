/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.06.22
 SDL : System Initialize(source)

********************************************************************
********************************************************************
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>

#include "nexsusdev.h"

static	NX_SYSTEM_INFO		sysinfo;
static	SDL_Joystick		*joy;

/*******************************************************************
 システム全体の初期��サ
 return code:	 0:	正常終了
				-1:	初期化失敗
********************************************************************/
short NX_SystemInit( int *argc, char **argv[] )
{
	short					retcode;
	Uint32					init_flag = 0;
	SDL_Surface				*screen;			// 表示画面へのサーフェース
	SDL_Surface				*character;			// キャラクタ画像へのサーフェース
	HNX_Rect				charamap;
	short					mtmp;
	const SDL_VideoInfo		*vinfo;

	// 初期値設定 ==============================================
	sysinfo.anipat.patlist = NULL;

	// ユーザー設定値取得 **************************************
	if( ( retcode = NX_UserDefined( &sysinfo, *argc, *argv ) ) < 0 ){ // nexsususer.cで定義
		switch( retcode ){ // エラーコード処理
			case -1:
				NX_MessageBox( "System Error", "メモリが足りません。", "OK" );
				break;
		}
		retcode = -1;
		goto RETURN_CODE;
	}
	// 初期化するためのフラグ作成
	if( sysinfo.AUDIO == 1 ){
		init_flag = SDL_INIT_AUDIO;
	}
	if( sysinfo.VIDEO == 1 ){
		init_flag |= SDL_INIT_VIDEO;
	}
	if( sysinfo.CDROM == 1 ){
		init_flag |= SDL_INIT_CDROM;
	}
	if( sysinfo.TIMER == 1 ){
		init_flag |= SDL_INIT_TIMER;
	}
	if( sysinfo.JSTCK == 1 ){
		init_flag |= SDL_INIT_JOYSTICK;
	}

	// SDL初期化処理 *******************************************
	fputs( "SDL初期化", stderr );
	if( SDL_Init( init_flag ) < 0 ){
		fputs( " --- false\n", stderr );
		NX_MessageBox( "SDL Error", "SDLの初期化に失敗しました。", "OK" );
		retcode = -1;
		goto RETURN_CODE;
	} else {
		fputs( " --- OK\n", stderr );
	}

	// SDL 画面作成 ============================================
	fputs( "SDLウィンドウ初期化", stderr );

	// 最適な色深度を取得 ======================================
	vinfo = SDL_GetVideoInfo();
	fputs( " --- OK\n", stderr );

	// OpenGL関係初期化
	if( ( sysinfo.SCREENMODE & SDL_OPENGL ) != 0 ){
		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 1 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, vinfo -> vfmt -> BitsPerPixel );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	}

	// サ−フェ−ス作成 ========================================
	fputs( "SDLサ−フェ−ス作成", stderr );
	screen = SDL_SetVideoMode( sysinfo.WIDTH, sysinfo.HEIGHT, vinfo -> vfmt -> BitsPerPixel, sysinfo.SCREENMODE );
	if ( screen == NULL ) {
		fputs( " --- false\n", stderr );
		NX_MessageBox( "SDL Error", "ウィンドウが作成できません。", "OK" );
		retcode = -1;
		goto RETURN_CODE;
	} else {
		fputs( " --- OK\n", stderr );
		sysinfo.screen = ( void * )screen;
	}

	// 二次元キャラクタ用画像読み込み ==========================
	fputs( "キャラクタ画像読み込み", stderr );
	if( ( retcode = NX_LoadBitmapFile( sysinfo.CHARACTERFNAME, sysinfo.MAPFNAME ) ) < 0 ){
		fputs( " --- false\n", stderr );
		switch( retcode ){
			case -1: // キャラクタ画像読み込みエラ−
				NX_MessageBox( "System Error", "キャラクタ画像ファイルの読み込みが出来ませんでした。", "OK" );
				break;
			case -2:
				NX_MessageBox( "System Error", "マップファイルの読み込みが出来ませんでした。", "OK" );
				break;
			case -3:
				NX_MessageBox( "System Error", "メモリが足りません。", "OK" );
				break;
		}
		retcode = -1;
		goto RETURN_CODE;
	} else {
		fputs( " --- OK\n", stderr );
		charamap = sysinfo.charamap;
		// 読み込んだオフスクリーンと表示用サーフェースの色深度が違うかチェック
		if( ( ( SDL_Surface * )sysinfo.character ) -> format -> BitsPerPixel != vinfo -> vfmt -> BitsPerPixel ){
			character = SDL_DisplayFormat( ( SDL_Surface * )sysinfo.character  );
			SDL_FreeSurface( ( SDL_Surface * )sysinfo.character );
			sysinfo.character = ( void * )character;
		} else {
			character = ( SDL_Surface * )sysinfo.character;
		}
	}

	// マウスカーソルを設定する
	mtmp = SDL_ShowCursor( sysinfo.mouse );
	if( mtmp == sysinfo.mouse ){
		SDL_ShowCursor( sysinfo.mouse );
	}

	// オブジェクト確保 ========================================
	fputs( "オブジェクト確保", stderr );
	if( NX_AllocateObject( sysinfo.OBJECTNUM ) == 0 ){
		fputs( " --- OK\n", stderr );
	} else {
		fputs( " --- false\n", stderr );
		NX_MessageBox( "System Error", "メモリが足りません。", "OK" );
		retcode = -1;
		goto RETURN_CODE;
	}

	// ジョイスティック初期化 =================================
	fputs( "ジョイスティック初期化", stderr );
	// Check for joystick
	if( SDL_NumJoysticks() > 0 ){
		// Open joystick
		joy = SDL_JoystickOpen( 0 );
		fputs( " --- OK\n", stderr );
	} else {
		fputs( " --- no joystick\n", stderr );
	}

	retcode = 0;

RETURN_CODE:
	return retcode;
}
/**/

/*******************************************************************
 現在のticksを返す
*******************************************************************/
unsigned long NX_GetTicks( void ){

	return ( unsigned long )SDL_GetTicks();

}
/**/

/*******************************************************************
 Argment Initialize 引数を使った初期化処理
********************************************************************/
void NX_ArgInit( int *pargc, char **pargv[] )
{
//	gtk_set_locale();
//	gtk_init( pargc, pargv );
}
/**/

/*******************************************************************
 システム終了処理
********************************************************************/
void NX_SystemTerm( void )
{
	fputs( "ジョイスティック終了処理", stderr );
	SDL_JoystickClose( joy );
	fputs( " --- OK\n", stderr );

	fputs( "メモリー解放", stderr );
	NX_MemoryFree();
	fputs( " --- OK\n", stderr );

	SDL_Quit();
	fputs( "SDL終了処理 --- OK\n", stderr );
}
/**/

/*******************************************************************
 メモリ解放
*******************************************************************/
void NX_MemoryFree( void )
{
	short		i;
	Hpatlist	pat;

	// オブジェクトメモリ解放
	NX_FreeObject( sysinfo.OBJECTNUM );
	for( i = 0; i < sysinfo.CHARANUM; i++ ){
		free( sysinfo.charamap[ i ] );
		free( sysinfo.charareg[ i ] );
	}
	free( sysinfo.charamap );
	free( sysinfo.charareg );

	// アニメパターン用メモリ解放
	pat = sysinfo.anipat.patlist;
	for( i = 0; i < sysinfo.anipat.patnum; i++ ){
		if( pat[ i ] -> pat != NULL ){ free( pat[ i ] -> pat ); }
		if( pat[ i ] -> time != NULL ){ free( pat[ i ] -> time ); }
		if( pat[ i ] != NULL ){ free( pat[ i ] ); }
	}
	if( pat != NULL ){ free( pat ); }

	//オフスクリーンキャラクタマップ用メモリ解放
	if( sysinfo.character != NULL ){
		SDL_FreeSurface( ( SDL_Surface * )sysinfo.character );
	}
	if( sysinfo.screen != NULL ){
		SDL_FreeSurface( ( SDL_Surface * )sysinfo.screen );
	}

} /**/

/*******************************************************************
 システム情報構造体へのポインタを返す
*******************************************************************/
PNX_SYSTEM_INFO NX_GetSystemInfo( void )
{
	return &sysinfo;
}
/**/

/*******************************************************************
 二次元キャラクタ用画像を読み込む
 返値： 0 : 正常終了
       -1 : キャラクタ画像読み込みエラ−
       -2 : マップファイル読み込みエラ−
       -3 : メモリが足りません
*******************************************************************/
short NX_LoadBitmapFile( char *bitmap, char *mapfile )
{
	FILE		*fp;
	short		retcode;
	short		loop;
	short		spos;
	short		mode;
	char		tmp[ 256 ];
	char		*x1, *y1, *x2, *y2, *rx, *ry;
	SDL_Surface	*character;				// キャラクタ画像へのサーフェース
	HNX_Rect	charamap;
	Hcoord		charareg;

	// 指定された画像ファイルを読み込んでオフスクリーンを作成する
	spos = NX_StrPos( bitmap, "." );
	if( strcmp( &( bitmap[ spos ] ), ".png" ) == 0 ){
		character = IMG_Load( bitmap ); // PNG画像読み込み
		mode = 0;
	} else {
		character = SDL_LoadBMP( bitmap ); // BMP画像読み込み
		mode = 1;
	}

	// 読み込めなかったら場合の処理
	if( character == NULL ){
		retcode = -1;
		goto RETURN_CODE;
	} else {
		// 読み込めたらシステム情報構造体にポインタを設定
		sysinfo.character = ( void * )character;
	}

	// 抜き色の設定 ===========================================
	SDL_SetColorKey( character, SDL_SRCCOLORKEY, SDL_MapRGB( character -> format, 255, 255, 255 ) );

	// MAPファイルを開く
	fp = fopen( mapfile, "r" );
	if( fp == NULL ){
		retcode = -2;
		goto RETURN_CODE;
	}

	// 一行づつ読み込んで処理をする
	fgets( tmp, sizeof( tmp ), fp );
	sysinfo.CHARANUM = atoi( tmp );
	charamap = ( HNX_Rect )malloc( sizeof( PNX_Rect ) * sysinfo.CHARANUM );
	charareg = ( Hcoord )malloc( sizeof( Pcoord ) * sysinfo.CHARANUM );
	if( charamap == NULL || charareg == NULL ){
		retcode = -3;
		sysinfo.CHARANUM = 0;
		fclose( fp );
		goto RETURN_CODE;
	} else {
		sysinfo.charamap = charamap;
		sysinfo.charareg = charareg;
	}

	for( loop = 0; loop < sysinfo.CHARANUM; loop++ ){
		charamap[ loop ] = ( PNX_Rect )malloc( sizeof( NX_Rect ) );
		charareg[ loop ] = ( Pcoord )malloc( sizeof( coord ) );
		if( charamap[ loop ] == NULL || charareg[ loop ] == NULL ){
			retcode = -3;
			sysinfo.CHARANUM = loop;
			fclose( fp );
			goto RETURN_CODE;
		}
		fgets( tmp, sizeof( tmp ), fp );
		x1 = strtok( tmp, "," );
		charamap[ loop ] -> x1 = atoi( x1 );
		y1 = strtok( NULL, "," );
		charamap[ loop ] -> y1 = atoi( y1 );
		x2 = strtok( NULL, "," );
		charamap[ loop ] -> x2 = atoi( x2 );
		y2 = strtok( NULL, "," );
		charamap[ loop ] -> y2 = atoi( y2 );
		rx = strtok( NULL, "," );
		charareg[ loop ] -> x = atof( rx );
		ry = strtok( NULL, "," );
		charareg[ loop ] -> y = atof( ry );

//sprintf( tmp, "%d = %d, %d, %d, %d", loop, charamap[ loop ] -> x1, charamap[ loop ] -> y1, charamap[ loop ] -> x2, charamap[ loop ] -> y2 ); puts( tmp );
//NX_MessageBox( "debug", tmp, "OK" );

	}
	fclose( fp );

RETURN_CODE:
	return retcode;
}
/**/

/*******************************************************************
 SDLのイベントを返す
 返値： 0:イベント無し
		1:ウィンドウが閉じられた
        2:キーが押された
*******************************************************************/
short NX_GetSDLEvent( short *result )
{
	SDL_Event	event;
	short		retcode;

	retcode = 0;
	SDL_PollEvent( &event );
	switch( event.type ){
		case SDL_QUIT:
			retcode = NX_QUIT;
			*result = 0;
			break;
		case SDL_KEYDOWN:
			retcode = NX_KEYDOWN;
			*result = event.key.keysym.sym;
			break;
		default:
			break;
	}

	return retcode;
}
/**/

/*******************************************************************
 指定された、アニメパターン番号の指定された番号の絵を、指定されたスクリーンの座標に転送する
 引数：patnum = アニメ番号
       grnum  = 指定されたアニメ番号の中の画像番号
	   x, y   = 転送先の画面の座標
*******************************************************************/
void NX_CharacterBlit( short patnum, short grnum, long x, long y )
{
	SDL_Rect		dstrect, screenrect;
	SDL_Surface		*character;			// キャラクタ画像へのサーフェース
	SDL_Surface		*screen;			// 表示画面へのサーフェース
	HNX_Rect		charamap;
	Hpatlist		pat;
	long			xdiff, ydiff;
	SDL_Rect		cliprect;

	screen = ( SDL_Surface * )sysinfo.screen;
	character = ( SDL_Surface * )sysinfo.character;
	charamap = sysinfo.charamap;

	pat = sysinfo.anipat.patlist;
	xdiff = ( charamap[ pat[ patnum ] -> pat[ grnum ] ] -> x2 ) - ( charamap[ pat[ patnum ] -> pat[ grnum ] ] -> x1 ) + 1;
	ydiff = ( charamap[ pat[ patnum ] -> pat[ grnum ] ] -> y2 ) - ( charamap[ pat[ patnum ] -> pat[ grnum ] ] -> y1 ) + 1;
	dstrect.x = charamap[ pat[ patnum ] -> pat[ grnum ] ] -> x1;
	dstrect.y = charamap[ pat[ patnum ] -> pat[ grnum ] ] -> y1;
	dstrect.w = xdiff;
	dstrect.h = ydiff;

	screenrect.x = x + sysinfo.charareg[ pat[ patnum ] -> pat[ grnum ] ] -> x;
	screenrect.y = y + sysinfo.charareg[ pat[ patnum ] -> pat[ grnum ] ] -> y;
	screenrect.w = xdiff;
	screenrect.h = ydiff;

	// サーフェースのクリッピング =============================
	cliprect.x = 0;
	cliprect.y = 0;
	cliprect.h = screen -> h;
	cliprect.w = screen -> w;
	SDL_SetClipRect( screen, &cliprect );

	// 領域の転送 =============================================
	SDL_BlitSurface( character, &dstrect, screen, &screenrect );
}
/**/

/*******************************************************************
 画面を更新する
*******************************************************************/
void NX_UpdateStage( void  )
{
	SDL_Surface		*screen;			// 表示画面へのサーフェース
	SDL_Rect		screenrect;

	screen = ( SDL_Surface * )sysinfo.screen;
	SDL_Flip( screen );

	screenrect.x = 0;
	screenrect.y = 0;
	screenrect.w = screen -> w;
	screenrect.h = screen -> h;
	SDL_FillRect( screen, &screenrect, SDL_MapRGB( screen -> format, 0, 0, 0 ) );
}
/**/

/*******************************************************************
 指定されたキーコードのキーが押されているかチェックする
 引数：SDLのキーコード
 返値：0 = 押されていない
 	   1 = 押されている
*******************************************************************/
short NX_isKeypress( short keycode )
{
	Uint8 *keystate;

	keystate = SDL_GetKeyState( NULL );

	return keystate[ keycode ];
}
/**/

/*******************************************************************
 コントローラの状態を取得する
 NX_UP_CURSOR : ジョイスティックの上、カーソルキーの上、テンキーの8
 NX_DW_CURSOR : ジョイスティックの下、カーソルキーの下、テンキーの2
 NX_LF_CURSOR : ジョイスティックの左、カーソルキーの左、テンキーの4
 NX_RT_CURSOR : ジョイスティックの右、カーソルキーの右、テンキーの6
*******************************************************************/
short NX_isStick( short keycode )
{
	Uint8 *keystate;
	short result;

//int tmp;
//tmp = SDL_JoystickGetAxis( joy, 0 );
//PRINTNUM( tmp );

	keystate = SDL_GetKeyState( NULL );

	result = 0;
	switch( keycode ){
		case NX_UP_CURSOR:
			result = ( keystate[ SDLK_UP ] != 0 ) | ( keystate[ SDLK_KP8 ] != 0 );
			break;
		case NX_DW_CURSOR:
			result = ( keystate[ SDLK_DOWN ] != 0 ) | ( keystate[ SDLK_KP2 ] != 0 );
			break;
		case NX_LF_CURSOR:
			result = ( keystate[ SDLK_LEFT ] != 0 ) | ( keystate[ SDLK_KP4 ] != 0 );
			break;
		case NX_RT_CURSOR:
			result = ( keystate[ SDLK_RIGHT ] != 0 ) | ( keystate[ SDLK_KP6 ] != 0 );
			break;
	}

	return result;
}
/**/

