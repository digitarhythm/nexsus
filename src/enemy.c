/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.07.13
 stationary object file

 ���֥������Ȥ�ư�����������
 constructor()�˽���������򵭽ҡ�destructor()�˥��֥������Ȥ����Ǥ���Ȥ��ν����򵭽�
 objprocess()�򥪥֥������Ȥ�ư����������ؿ�̾���Ѥ��Ƴƽ����ֹ�ν����򵭽Ҥ��롣

********************************************************************
********************************************************************
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "nexsus.h"

extern short mcp;
extern short mship;

static void constructor( Puserparam );
static void destructor( Puserparam );

// ���֥������Ȥ�ư����������
void enemy( Puserparam usrprm, void *arg )
{
	unsigned short	tmp;
	short			i;

	switch( usrprm -> processnum ){

		case 1:
			if( NX_GetRandom( 1, 20 ) == 1 ){
				if( ( rand() % 2 ) == 0 ){
					usrprm -> pattern_num = 0;
					usrprm -> sp.sx = -1;
				} else {
					usrprm -> pattern_num = 1;
					usrprm -> sp.sx = 1;
				}
				NX_NextProcess( usrprm );
			}
			NX_EventAction( mcp, 99, ( void * )usrprm ); // �Ƥ������ä���
			NX_EventAction( mship, 99, ( void * )usrprm ); // �����������ä���
			break;

		case 2:
			usrprm -> sp.sx += ( 0.1 * ( usrprm -> sp.sx > 0 ) ) + ( -0.1 * ( usrprm -> sp.sx < 0 ) );
			if( usrprm -> loc.y > 320 || usrprm -> loc.x < -32 || usrprm -> loc.x > 240 ){
				tmp = NX_GetRandom( 40, 200 );
				NX_AddObject( tmp, -32, 0, 0, NX_GetRandom( 5, 8 ), 0, 0, NX_ANIME, usrprm -> num, 5, 1, 1, 1, 1, &( usrprm -> rect ), enemy );
				NX_DelObject( usrprm );
			}
			NX_EventAction( mcp, 99, ( void * )usrprm ); // �Ƥ������ä���
			NX_EventAction( mship, 99, ( void * )usrprm ); // �����������ä���
			break;

		case 99:
				usrprm -> pattern_num = 6;
				usrprm -> intersects = 0;
				usrprm -> sp.sx = 0;
				usrprm -> sp.sy = 0;
				NX_WaitJob( usrprm, 4, 100 );
				break;

		case 100:
				tmp = NX_GetRandom( 40, 200 );
				NX_AddObject( tmp, -32, 0, 0, NX_GetRandom( 5, 8 ), 0, 0, NX_ANIME, -1, 5, 1, 1, 1, 1, &( usrprm -> rect ), enemy );
				NX_DelObject( usrprm );
				break;

		case NX_CONST:
			constructor( usrprm );
		break;
		case NX_DEST:
			destructor( usrprm );
		break;
		default:
			break;
	}

}
/**/

/********************************************************************
 ���󥹥ȥ饯����
********************************************************************/
void constructor( Puserparam usrprm )
{
	;
}
/**/

/********************************************************************
 �ǥ��ȥ饯����
********************************************************************/
void destructor( Puserparam usrprm )
{
	;
}
/**/
