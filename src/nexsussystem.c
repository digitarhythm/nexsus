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
 �����ƥ����Τν������
 return code:	 0:	���ｪλ
				-1:	���������
********************************************************************/
short NX_SystemInit( int *argc, char **argv[] )
{
	short					retcode;
	Uint32					init_flag = 0;
	SDL_Surface				*screen;			// ɽ�����̤ؤΥ����ե�����
	SDL_Surface				*character;			// ����饯�������ؤΥ����ե�����
	HNX_Rect				charamap;
	short					mtmp;
	const SDL_VideoInfo		*vinfo;

	// ��������� ==============================================
	sysinfo.anipat.patlist = NULL;

	// �桼���������ͼ��� **************************************
	if( ( retcode = NX_UserDefined( &sysinfo, *argc, *argv ) ) < 0 ){ // nexsususer.c�����
		switch( retcode ){ // ���顼�����ɽ���
			case -1:
				NX_MessageBox( "System Error", "���꤬­��ޤ���", "OK" );
				break;
		}
		retcode = -1;
		goto RETURN_CODE;
	}
	// ��������뤿��Υե饰����
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

	// SDL��������� *******************************************
	fputs( "SDL�����", stderr );
	if( SDL_Init( init_flag ) < 0 ){
		fputs( " --- false\n", stderr );
		NX_MessageBox( "SDL Error", "SDL�ν�����˼��Ԥ��ޤ�����", "OK" );
		retcode = -1;
		goto RETURN_CODE;
	} else {
		fputs( " --- OK\n", stderr );
	}

	// SDL ���̺��� ============================================
	fputs( "SDL������ɥ������", stderr );

	// ��Ŭ�ʿ����٤���� ======================================
	vinfo = SDL_GetVideoInfo();
	fputs( " --- OK\n", stderr );

	// OpenGL�ط������
	if( ( sysinfo.SCREENMODE & SDL_OPENGL ) != 0 ){
		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 1 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, vinfo -> vfmt -> BitsPerPixel );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	}

	// ���ݥե��ݥ����� ========================================
	fputs( "SDL���ݥե��ݥ�����", stderr );
	screen = SDL_SetVideoMode( sysinfo.WIDTH, sysinfo.HEIGHT, vinfo -> vfmt -> BitsPerPixel, sysinfo.SCREENMODE );
	if ( screen == NULL ) {
		fputs( " --- false\n", stderr );
		NX_MessageBox( "SDL Error", "������ɥ��������Ǥ��ޤ���", "OK" );
		retcode = -1;
		goto RETURN_CODE;
	} else {
		fputs( " --- OK\n", stderr );
		sysinfo.screen = ( void * )screen;
	}

	// �󼡸�����饯���Ѳ����ɤ߹��� ==========================
	fputs( "����饯�������ɤ߹���", stderr );
	if( ( retcode = NX_LoadBitmapFile( sysinfo.CHARACTERFNAME, sysinfo.MAPFNAME ) ) < 0 ){
		fputs( " --- false\n", stderr );
		switch( retcode ){
			case -1: // ����饯�������ɤ߹��ߥ����
				NX_MessageBox( "System Error", "����饯�������ե�������ɤ߹��ߤ�����ޤ���Ǥ�����", "OK" );
				break;
			case -2:
				NX_MessageBox( "System Error", "�ޥåץե�������ɤ߹��ߤ�����ޤ���Ǥ�����", "OK" );
				break;
			case -3:
				NX_MessageBox( "System Error", "���꤬­��ޤ���", "OK" );
				break;
		}
		retcode = -1;
		goto RETURN_CODE;
	} else {
		fputs( " --- OK\n", stderr );
		charamap = sysinfo.charamap;
		// �ɤ߹�������ե����꡼���ɽ���ѥ����ե������ο����٤��㤦�������å�
		if( ( ( SDL_Surface * )sysinfo.character ) -> format -> BitsPerPixel != vinfo -> vfmt -> BitsPerPixel ){
			character = SDL_DisplayFormat( ( SDL_Surface * )sysinfo.character  );
			SDL_FreeSurface( ( SDL_Surface * )sysinfo.character );
			sysinfo.character = ( void * )character;
		} else {
			character = ( SDL_Surface * )sysinfo.character;
		}
	}

	// �ޥ���������������ꤹ��
	mtmp = SDL_ShowCursor( sysinfo.mouse );
	if( mtmp == sysinfo.mouse ){
		SDL_ShowCursor( sysinfo.mouse );
	}

	// ���֥������ȳ��� ========================================
	fputs( "���֥������ȳ���", stderr );
	if( NX_AllocateObject( sysinfo.OBJECTNUM ) == 0 ){
		fputs( " --- OK\n", stderr );
	} else {
		fputs( " --- false\n", stderr );
		NX_MessageBox( "System Error", "���꤬­��ޤ���", "OK" );
		retcode = -1;
		goto RETURN_CODE;
	}

	// ���祤���ƥ��å������ =================================
	fputs( "���祤���ƥ��å������", stderr );
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
 ���ߤ�ticks���֤�
*******************************************************************/
unsigned long NX_GetTicks( void ){

	return ( unsigned long )SDL_GetTicks();

}
/**/

/*******************************************************************
 Argment Initialize ������Ȥä����������
********************************************************************/
void NX_ArgInit( int *pargc, char **pargv[] )
{
//	gtk_set_locale();
//	gtk_init( pargc, pargv );
}
/**/

/*******************************************************************
 �����ƥཪλ����
********************************************************************/
void NX_SystemTerm( void )
{
	fputs( "���祤���ƥ��å���λ����", stderr );
	SDL_JoystickClose( joy );
	fputs( " --- OK\n", stderr );

	fputs( "���꡼����", stderr );
	NX_MemoryFree();
	fputs( " --- OK\n", stderr );

	SDL_Quit();
	fputs( "SDL��λ���� --- OK\n", stderr );
}
/**/

/*******************************************************************
 �������
*******************************************************************/
void NX_MemoryFree( void )
{
	short		i;
	Hpatlist	pat;

	// ���֥������ȥ������
	NX_FreeObject( sysinfo.OBJECTNUM );
	for( i = 0; i < sysinfo.CHARANUM; i++ ){
		free( sysinfo.charamap[ i ] );
		free( sysinfo.charareg[ i ] );
	}
	free( sysinfo.charamap );
	free( sysinfo.charareg );

	// ���˥�ѥ������ѥ������
	pat = sysinfo.anipat.patlist;
	for( i = 0; i < sysinfo.anipat.patnum; i++ ){
		if( pat[ i ] -> pat != NULL ){ free( pat[ i ] -> pat ); }
		if( pat[ i ] -> time != NULL ){ free( pat[ i ] -> time ); }
		if( pat[ i ] != NULL ){ free( pat[ i ] ); }
	}
	if( pat != NULL ){ free( pat ); }

	//���ե����꡼�󥭥�饯���ޥå��ѥ������
	if( sysinfo.character != NULL ){
		SDL_FreeSurface( ( SDL_Surface * )sysinfo.character );
	}
	if( sysinfo.screen != NULL ){
		SDL_FreeSurface( ( SDL_Surface * )sysinfo.screen );
	}

} /**/

/*******************************************************************
 �����ƥ����¤�ΤؤΥݥ��󥿤��֤�
*******************************************************************/
PNX_SYSTEM_INFO NX_GetSystemInfo( void )
{
	return &sysinfo;
}
/**/

/*******************************************************************
 �󼡸�����饯���Ѳ������ɤ߹���
 ���͡� 0 : ���ｪλ
       -1 : ����饯�������ɤ߹��ߥ����
       -2 : �ޥåץե������ɤ߹��ߥ����
       -3 : ���꤬­��ޤ���
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
	SDL_Surface	*character;				// ����饯�������ؤΥ����ե�����
	HNX_Rect	charamap;
	Hcoord		charareg;

	// ���ꤵ�줿�����ե�������ɤ߹���ǥ��ե����꡼����������
	spos = NX_StrPos( bitmap, "." );
	if( strcmp( &( bitmap[ spos ] ), ".png" ) == 0 ){
		character = IMG_Load( bitmap ); // PNG�����ɤ߹���
		mode = 0;
	} else {
		character = SDL_LoadBMP( bitmap ); // BMP�����ɤ߹���
		mode = 1;
	}

	// �ɤ߹���ʤ��ä�����ν���
	if( character == NULL ){
		retcode = -1;
		goto RETURN_CODE;
	} else {
		// �ɤ߹��᤿�饷���ƥ����¤�Τ˥ݥ��󥿤�����
		sysinfo.character = ( void * )character;
	}

	// ȴ���������� ===========================================
	SDL_SetColorKey( character, SDL_SRCCOLORKEY, SDL_MapRGB( character -> format, 255, 255, 255 ) );

	// MAP�ե�����򳫤�
	fp = fopen( mapfile, "r" );
	if( fp == NULL ){
		retcode = -2;
		goto RETURN_CODE;
	}

	// ��ԤŤ��ɤ߹���ǽ����򤹤�
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
 SDL�Υ��٥�Ȥ��֤�
 ���͡� 0:���٥��̵��
		1:������ɥ����Ĥ���줿
        2:�����������줿
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
 ���ꤵ�줿�����˥�ѥ������ֹ�λ��ꤵ�줿�ֹ�γ��򡢻��ꤵ�줿�����꡼��κ�ɸ��ž������
 ������patnum = ���˥��ֹ�
       grnum  = ���ꤵ�줿���˥��ֹ����β����ֹ�
	   x, y   = ž����β��̤κ�ɸ
*******************************************************************/
void NX_CharacterBlit( short patnum, short grnum, long x, long y )
{
	SDL_Rect		dstrect, screenrect;
	SDL_Surface		*character;			// ����饯�������ؤΥ����ե�����
	SDL_Surface		*screen;			// ɽ�����̤ؤΥ����ե�����
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

	// �����ե������Υ���åԥ� =============================
	cliprect.x = 0;
	cliprect.y = 0;
	cliprect.h = screen -> h;
	cliprect.w = screen -> w;
	SDL_SetClipRect( screen, &cliprect );

	// �ΰ��ž�� =============================================
	SDL_BlitSurface( character, &dstrect, screen, &screenrect );
}
/**/

/*******************************************************************
 ���̤򹹿�����
*******************************************************************/
void NX_UpdateStage( void  )
{
	SDL_Surface		*screen;			// ɽ�����̤ؤΥ����ե�����
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
 ���ꤵ�줿���������ɤΥ�����������Ƥ��뤫�����å�����
 ������SDL�Υ���������
 ���͡�0 = ������Ƥ��ʤ�
 	   1 = ������Ƥ���
*******************************************************************/
short NX_isKeypress( short keycode )
{
	Uint8 *keystate;

	keystate = SDL_GetKeyState( NULL );

	return keystate[ keycode ];
}
/**/

/*******************************************************************
 ����ȥ���ξ��֤��������
 NX_UP_CURSOR : ���祤���ƥ��å��ξ塢�������륭���ξ塢�ƥ󥭡���8
 NX_DW_CURSOR : ���祤���ƥ��å��β����������륭���β����ƥ󥭡���2
 NX_LF_CURSOR : ���祤���ƥ��å��κ����������륭���κ����ƥ󥭡���4
 NX_RT_CURSOR : ���祤���ƥ��å��α����������륭���α����ƥ󥭡���6
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

