/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.07.13
 stationary object file

 ���֥������Ȥ�ư�����������
 constructor()�˽���������򵭽ҡ�destructor()�˥��֥������Ȥ����Ǥ���Ȥ��ν����򵭽�
 objprocess()�˳ƽ����ֹ�ν����򵭽Ҥ��롣

********************************************************************
********************************************************************
********************************************************************/

#include "SDL.h"
#include "nexsus.h"

extern mfunc missile_control;
extern short mcp;

static void constructor( Puserparam );
static void destructor( Puserparam );

void myship( Puserparam usrprm, void *arg )
{
	switch( usrprm -> processnum ){

		case 1:
			if( NX_isStick( NX_UP_CURSOR ) == 1 ){
				usrprm -> loc.y -= 2;
				if( usrprm -> loc.y < -21 ){
					usrprm -> loc.y = -21;
				}
			}
			if( NX_isStick( NX_DW_CURSOR ) == 1 ){
				usrprm -> loc.y += 2;
				if( usrprm -> loc.y > 299 ){
					usrprm -> loc.y = 299;
				}
			}
			if( NX_isStick( NX_LF_CURSOR ) == 1 ){
				usrprm -> loc.x -= 2;
				if( usrprm -> loc.x < -21 ){
					usrprm -> loc.x = -21;
				}
			}
			if( NX_isStick( NX_RT_CURSOR ) == 1 ){
				usrprm -> loc.x += 2;
				if( usrprm -> loc.x > 219 ){
					usrprm -> loc.x = 219;
				}
			}
			if( NX_isKeypress( SDLK_c ) == 1 ){
				NX_EventAction( mcp, 2, ( void * )&( usrprm -> loc ) );
			}

			break;

		case 98: // �����и�
			if( NX_isKeypress( SDLK_s ) == 1 ){
				usrprm -> loc.x = 120 - 24;
				usrprm -> loc.y = 240;
				usrprm -> visible = 1;
				usrprm -> processnum = 1;
				usrprm -> pattern_num = 3;
				usrprm -> intersects = 1;
			}
			break;

		case 99: // Ũ�������ä���
			if( NX_GetIntersects( usrprm, ( Puserparam )arg ) != 0 ){
				usrprm -> intersects = 0;
				usrprm -> pattern_num = 6;
				NX_WaitJob( usrprm, 4, 100 );
			}
			break;

		case 100:
			usrprm -> visible = 0;
			usrprm -> processnum = 98;
			break;

		case NX_CONST:	// ���󥹥ȥ饯����
			constructor( usrprm );
		break;
		case NX_DEST:	// �ǥ��ȥ饯����
			destructor( usrprm );
		break;
		default:
			break;
	}
}
/**/

void constructor( Puserparam usrprm )
{
	;
}
/**/

void destructor( Puserparam usrprm )
{
	;
}
/**/
