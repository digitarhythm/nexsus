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
 ���������٤�����򤹤�
 ����	 0:���ｪλ
 		-1:���꤬­��ʤ�
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

	// �����ƥ�������Ͽ����
	sysinfo -> AUDIO = 1;								// �����ǥ����ν����(0=���ʤ�/1=����)
	sysinfo -> VIDEO = 1;								// �ӥǥ��ν����(0=���ʤ�/1=����)
	sysinfo -> CDROM = 1;								// CD-ROM�ν����(0=���ʤ�/1=����)
	sysinfo -> TIMER = 1;								// �����ޡ��ν����(0=���ʤ�/1=����)
	sysinfo -> JSTCK = 1;								// ���祤���ƥ��å��ν����(0=���ʤ�/1=����)
	sysinfo -> WIDTH = 240;								// ���̤β���
	sysinfo -> HEIGHT = 320;							// ���̤ν�
	sysinfo -> SCREENMODE = SDL_ANYFORMAT | SDL_ASYNCBLIT | SDL_DOUBLEBUF | fscrn;			// ���̥⡼��
	sysinfo -> OBJECTNUM = 256;							// �������륪�֥������Ȥο�
	strcpy( sysinfo -> CHARACTERFNAME, "chara.bmp" );	// ���Ѥ����󼡸�����饯���ե�����̾
//	strcpy( sysinfo -> CHARACTERFNAME, "chara.png" );	// ���Ѥ����󼡸�����饯���ե�����̾
	strcpy( sysinfo -> MAPFNAME, "chara.map" );			// ����饯������ե�����̾
	sysinfo -> mouse = 0;								// �ޥ�����������ɽ���ե饰

	// ���˥�ѥ��������Ͽ����
	sysinfo -> ANIMENUM = 256;							// ���˥�ѥ�����ο�
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
