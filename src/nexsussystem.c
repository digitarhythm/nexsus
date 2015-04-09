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
 •∑•π•∆•‡¡¥¬Œ§ŒΩÈ¥¸±ê•µ
 return code:	 0:	¿µæÔΩ™Œª
				-1:	ΩÈ¥¸≤Ωº∫«‘
********************************************************************/
short NX_SystemInit( int *argc, char **argv[] )
{
	short					retcode;
	Uint32					init_flag = 0;
	SDL_Surface				*screen;			// …Ωº®≤ËÃÃ§ÿ§Œ•µ°º•’•ß°º•π
	SDL_Surface				*character;			// •≠•„•È•Ø•ø≤Ë¡¸§ÿ§Œ•µ°º•’•ß°º•π
	HNX_Rect				charamap;
	short					mtmp;
	const SDL_VideoInfo		*vinfo;

	// ΩÈ¥¸√Õ¿ﬂƒÍ ==============================================
	sysinfo.anipat.patlist = NULL;

	// •Ê°º•∂°º¿ﬂƒÍ√ÕºË∆¿ **************************************
	if( ( retcode = NX_UserDefined( &sysinfo, *argc, *argv ) ) < 0 ){ // nexsususer.c§«ƒÍµ¡
		switch( retcode ){ // •®•È°º•≥°º•…ΩËÕ˝
			case -1:
				NX_MessageBox( "System Error", "•·•‚•Í§¨¬≠§Í§ﬁ§ª§Û°£", "OK" );
				break;
		}
		retcode = -1;
		goto RETURN_CODE;
	}
	// ΩÈ¥¸≤Ω§π§Î§ø§·§Œ•’•È•∞∫Ó¿Æ
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

	// SDLΩÈ¥¸≤ΩΩËÕ˝ *******************************************
	fputs( "SDLΩÈ¥¸≤Ω", stderr );
	if( SDL_Init( init_flag ) < 0 ){
		fputs( " --- false\n", stderr );
		NX_MessageBox( "SDL Error", "SDL§ŒΩÈ¥¸≤Ω§Àº∫«‘§∑§ﬁ§∑§ø°£", "OK" );
		retcode = -1;
		goto RETURN_CODE;
	} else {
		fputs( " --- OK\n", stderr );
	}

	// SDL ≤ËÃÃ∫Ó¿Æ ============================================
	fputs( "SDL•¶•£•Û•…•¶ΩÈ¥¸≤Ω", stderr );

	// ∫«≈¨§ øßøº≈Ÿ§ÚºË∆¿ ======================================
	vinfo = SDL_GetVideoInfo();
	fputs( " --- OK\n", stderr );

	// OpenGL¥ÿ∑∏ΩÈ¥¸≤Ω
	if( ( sysinfo.SCREENMODE & SDL_OPENGL ) != 0 ){
		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 1 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, vinfo -> vfmt -> BitsPerPixel );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	}

	// •µ°›•’•ß°›•π∫Ó¿Æ ========================================
	fputs( "SDL•µ°›•’•ß°›•π∫Ó¿Æ", stderr );
	screen = SDL_SetVideoMode( sysinfo.WIDTH, sysinfo.HEIGHT, vinfo -> vfmt -> BitsPerPixel, sysinfo.SCREENMODE );
	if ( screen == NULL ) {
		fputs( " --- false\n", stderr );
		NX_MessageBox( "SDL Error", "•¶•£•Û•…•¶§¨∫Ó¿Æ§«§≠§ﬁ§ª§Û°£", "OK" );
		retcode = -1;
		goto RETURN_CODE;
	} else {
		fputs( " --- OK\n", stderr );
		sysinfo.screen = ( void * )screen;
	}

	// ∆Ûº°∏µ•≠•„•È•Ø•øÕ—≤Ë¡¸∆…§ﬂπ˛§ﬂ ==========================
	fputs( "•≠•„•È•Ø•ø≤Ë¡¸∆…§ﬂπ˛§ﬂ", stderr );
	if( ( retcode = NX_LoadBitmapFile( sysinfo.CHARACTERFNAME, sysinfo.MAPFNAME ) ) < 0 ){
		fputs( " --- false\n", stderr );
		switch( retcode ){
			case -1: // •≠•„•È•Ø•ø≤Ë¡¸∆…§ﬂπ˛§ﬂ•®•È°›
				NX_MessageBox( "System Error", "•≠•„•È•Ø•ø≤Ë¡¸•’•°•§•Î§Œ∆…§ﬂπ˛§ﬂ§¨Ω–ÕË§ﬁ§ª§Û§«§∑§ø°£", "OK" );
				break;
			case -2:
				NX_MessageBox( "System Error", "•ﬁ•√•◊•’•°•§•Î§Œ∆…§ﬂπ˛§ﬂ§¨Ω–ÕË§ﬁ§ª§Û§«§∑§ø°£", "OK" );
				break;
			case -3:
				NX_MessageBox( "System Error", "•·•‚•Í§¨¬≠§Í§ﬁ§ª§Û°£", "OK" );
				break;
		}
		retcode = -1;
		goto RETURN_CODE;
	} else {
		fputs( " --- OK\n", stderr );
		charamap = sysinfo.charamap;
		// ∆…§ﬂπ˛§Û§¿•™•’•π•Ø•Í°º•Û§»…Ωº®Õ—•µ°º•’•ß°º•π§Œøßøº≈Ÿ§¨∞„§¶§´•¡•ß•√•Ø
		if( ( ( SDL_Surface * )sysinfo.character ) -> format -> BitsPerPixel != vinfo -> vfmt -> BitsPerPixel ){
			character = SDL_DisplayFormat( ( SDL_Surface * )sysinfo.character  );
			SDL_FreeSurface( ( SDL_Surface * )sysinfo.character );
			sysinfo.character = ( void * )character;
		} else {
			character = ( SDL_Surface * )sysinfo.character;
		}
	}

	// •ﬁ•¶•π•´°º•Ω•Î§Ú¿ﬂƒÍ§π§Î
	mtmp = SDL_ShowCursor( sysinfo.mouse );
	if( mtmp == sysinfo.mouse ){
		SDL_ShowCursor( sysinfo.mouse );
	}

	// •™•÷•∏•ß•Ø•»≥Œ › ========================================
	fputs( "•™•÷•∏•ß•Ø•»≥Œ ›", stderr );
	if( NX_AllocateObject( sysinfo.OBJECTNUM ) == 0 ){
		fputs( " --- OK\n", stderr );
	} else {
		fputs( " --- false\n", stderr );
		NX_MessageBox( "System Error", "•·•‚•Í§¨¬≠§Í§ﬁ§ª§Û°£", "OK" );
		retcode = -1;
		goto RETURN_CODE;
	}

	// •∏•Á•§•π•∆•£•√•ØΩÈ¥¸≤Ω =================================
	fputs( "•∏•Á•§•π•∆•£•√•ØΩÈ¥¸≤Ω", stderr );
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
 ∏Ω∫ﬂ§Œticks§Ú ÷§π
*******************************************************************/
unsigned long NX_GetTicks( void ){

	return ( unsigned long )SDL_GetTicks();

}
/**/

/*******************************************************************
 Argment Initialize ∞˙øÙ§Úª»§√§øΩÈ¥¸≤ΩΩËÕ˝
********************************************************************/
void NX_ArgInit( int *pargc, char **pargv[] )
{
//	gtk_set_locale();
//	gtk_init( pargc, pargv );
}
/**/

/*******************************************************************
 •∑•π•∆•‡Ω™ŒªΩËÕ˝
********************************************************************/
void NX_SystemTerm( void )
{
	fputs( "•∏•Á•§•π•∆•£•√•ØΩ™ŒªΩËÕ˝", stderr );
	SDL_JoystickClose( joy );
	fputs( " --- OK\n", stderr );

	fputs( "•·•‚•Í°º≤Ú ¸", stderr );
	NX_MemoryFree();
	fputs( " --- OK\n", stderr );

	SDL_Quit();
	fputs( "SDLΩ™ŒªΩËÕ˝ --- OK\n", stderr );
}
/**/

/*******************************************************************
 •·•‚•Í≤Ú ¸
*******************************************************************/
void NX_MemoryFree( void )
{
	short		i;
	Hpatlist	pat;

	// •™•÷•∏•ß•Ø•»•·•‚•Í≤Ú ¸
	NX_FreeObject( sysinfo.OBJECTNUM );
	for( i = 0; i < sysinfo.CHARANUM; i++ ){
		free( sysinfo.charamap[ i ] );
		free( sysinfo.charareg[ i ] );
	}
	free( sysinfo.charamap );
	free( sysinfo.charareg );

	// •¢•À•·•—•ø°º•ÛÕ—•·•‚•Í≤Ú ¸
	pat = sysinfo.anipat.patlist;
	for( i = 0; i < sysinfo.anipat.patnum; i++ ){
		if( pat[ i ] -> pat != NULL ){ free( pat[ i ] -> pat ); }
		if( pat[ i ] -> time != NULL ){ free( pat[ i ] -> time ); }
		if( pat[ i ] != NULL ){ free( pat[ i ] ); }
	}
	if( pat != NULL ){ free( pat ); }

	//•™•’•π•Ø•Í°º•Û•≠•„•È•Ø•ø•ﬁ•√•◊Õ—•·•‚•Í≤Ú ¸
	if( sysinfo.character != NULL ){
		SDL_FreeSurface( ( SDL_Surface * )sysinfo.character );
	}
	if( sysinfo.screen != NULL ){
		SDL_FreeSurface( ( SDL_Surface * )sysinfo.screen );
	}

} /**/

/*******************************************************************
 •∑•π•∆•‡æ ÛπΩ¬§¬Œ§ÿ§Œ•›•§•Û•ø§Ú ÷§π
*******************************************************************/
PNX_SYSTEM_INFO NX_GetSystemInfo( void )
{
	return &sysinfo;
}
/**/

/*******************************************************************
 ∆Ûº°∏µ•≠•„•È•Ø•øÕ—≤Ë¡¸§Ú∆…§ﬂπ˛§‡
  ÷√Õ°ß 0 : ¿µæÔΩ™Œª
       -1 : •≠•„•È•Ø•ø≤Ë¡¸∆…§ﬂπ˛§ﬂ•®•È°›
       -2 : •ﬁ•√•◊•’•°•§•Î∆…§ﬂπ˛§ﬂ•®•È°›
       -3 : •·•‚•Í§¨¬≠§Í§ﬁ§ª§Û
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
	SDL_Surface	*character;				// •≠•„•È•Ø•ø≤Ë¡¸§ÿ§Œ•µ°º•’•ß°º•π
	HNX_Rect	charamap;
	Hcoord		charareg;

	// ªÿƒÍ§µ§Ï§ø≤Ë¡¸•’•°•§•Î§Ú∆…§ﬂπ˛§Û§«•™•’•π•Ø•Í°º•Û§Ú∫Ó¿Æ§π§Î
	spos = NX_StrPos( bitmap, "." );
	if( strcmp( &( bitmap[ spos ] ), ".png" ) == 0 ){
		character = IMG_Load( bitmap ); // PNG≤Ë¡¸∆…§ﬂπ˛§ﬂ
		mode = 0;
	} else {
		character = SDL_LoadBMP( bitmap ); // BMP≤Ë¡¸∆…§ﬂπ˛§ﬂ
		mode = 1;
	}

	// ∆…§ﬂπ˛§·§ §´§√§ø§ÈæÏπÁ§ŒΩËÕ˝
	if( character == NULL ){
		retcode = -1;
		goto RETURN_CODE;
	} else {
		// ∆…§ﬂπ˛§·§ø§È•∑•π•∆•‡æ ÛπΩ¬§¬Œ§À•›•§•Û•ø§Ú¿ﬂƒÍ
		sysinfo.character = ( void * )character;
	}

	// »¥§≠øß§Œ¿ﬂƒÍ ===========================================
	SDL_SetColorKey( character, SDL_SRCCOLORKEY, SDL_MapRGB( character -> format, 255, 255, 255 ) );

	// MAP•’•°•§•Î§Ú≥´§Ø
	fp = fopen( mapfile, "r" );
	if( fp == NULL ){
		retcode = -2;
		goto RETURN_CODE;
	}

	// ∞Ïπ‘§≈§ƒ∆…§ﬂπ˛§Û§«ΩËÕ˝§Ú§π§Î
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
 SDL§Œ•§•Ÿ•Û•»§Ú ÷§π
  ÷√Õ°ß 0:•§•Ÿ•Û•»Ãµ§∑
		1:•¶•£•Û•…•¶§¨ ƒ§∏§È§Ï§ø
        2:•≠°º§¨≤°§µ§Ï§ø
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
 ªÿƒÍ§µ§Ï§ø°¢•¢•À•·•—•ø°º•Û»÷πÊ§ŒªÿƒÍ§µ§Ï§ø»÷πÊ§Œ≥®§Ú°¢ªÿƒÍ§µ§Ï§ø•π•Ø•Í°º•Û§Œ∫¬…∏§À≈æ¡˜§π§Î
 ∞˙øÙ°ßpatnum = •¢•À•·»÷πÊ
       grnum  = ªÿƒÍ§µ§Ï§ø•¢•À•·»÷πÊ§Œ√Ê§Œ≤Ë¡¸»÷πÊ
	   x, y   = ≈æ¡˜¿Ë§Œ≤ËÃÃ§Œ∫¬…∏
*******************************************************************/
void NX_CharacterBlit( short patnum, short grnum, long x, long y )
{
	SDL_Rect		dstrect, screenrect;
	SDL_Surface		*character;			// •≠•„•È•Ø•ø≤Ë¡¸§ÿ§Œ•µ°º•’•ß°º•π
	SDL_Surface		*screen;			// …Ωº®≤ËÃÃ§ÿ§Œ•µ°º•’•ß°º•π
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

	// •µ°º•’•ß°º•π§Œ•Ø•Í•√•‘•Û•∞ =============================
	cliprect.x = 0;
	cliprect.y = 0;
	cliprect.h = screen -> h;
	cliprect.w = screen -> w;
	SDL_SetClipRect( screen, &cliprect );

	// ŒŒ∞Ë§Œ≈æ¡˜ =============================================
	SDL_BlitSurface( character, &dstrect, screen, &screenrect );
}
/**/

/*******************************************************************
 ≤ËÃÃ§Úππø∑§π§Î
*******************************************************************/
void NX_UpdateStage( void  )
{
	SDL_Surface		*screen;			// …Ωº®≤ËÃÃ§ÿ§Œ•µ°º•’•ß°º•π
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
 ªÿƒÍ§µ§Ï§ø•≠°º•≥°º•…§Œ•≠°º§¨≤°§µ§Ï§∆§§§Î§´•¡•ß•√•Ø§π§Î
 ∞˙øÙ°ßSDL§Œ•≠°º•≥°º•…
  ÷√Õ°ß0 = ≤°§µ§Ï§∆§§§ §§
 	   1 = ≤°§µ§Ï§∆§§§Î
*******************************************************************/
short NX_isKeypress( short keycode )
{
	Uint8 *keystate;

	keystate = SDL_GetKeyState( NULL );

	return keystate[ keycode ];
}
/**/

/*******************************************************************
 •≥•Û•»•Ì°º•È§Œæı¬÷§ÚºË∆¿§π§Î
 NX_UP_CURSOR : •∏•Á•§•π•∆•£•√•Ø§ŒæÂ°¢•´°º•Ω•Î•≠°º§ŒæÂ°¢•∆•Û•≠°º§Œ8
 NX_DW_CURSOR : •∏•Á•§•π•∆•£•√•Ø§Œ≤º°¢•´°º•Ω•Î•≠°º§Œ≤º°¢•∆•Û•≠°º§Œ2
 NX_LF_CURSOR : •∏•Á•§•π•∆•£•√•Ø§Œ∫∏°¢•´°º•Ω•Î•≠°º§Œ∫∏°¢•∆•Û•≠°º§Œ4
 NX_RT_CURSOR : •∏•Á•§•π•∆•£•√•Ø§Œ±¶°¢•´°º•Ω•Î•≠°º§Œ±¶°¢•∆•Û•≠°º§Œ6
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

