/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.07.13
 stationary object file

 ���֥������Ȥ�ư�����������
 constructor()�˽���������򵭽ҡ�destructor()�˥��֥������Ȥ����Ǥ���Ȥ��ν����򵭽�
 objprocess()�˳ƽ����ֹ�ν����򵭽Ҥ����֥������Ȥ�ư����������ؿ���̾�����Ѥ���

********************************************************************
********************************************************************
********************************************************************/

#include "nexsus.h"

static void constructor( Puserparam );
static void destructor( Puserparam );

void missile( Puserparam usrprm, void *arg )
{
	short	i;

	switch( usrprm -> processnum ){

		case 1:	// ���֥������Ȥ�ư������
			if( usrprm -> loc.y < -16 ){
				NX_EventAction( usrprm -> parent, 3, ( void * )usrprm );
			}
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

void constructor( Puserparam usrprm )
{
	;
}
/**/

void destructor( Puserparam usrprm )
{
}
/**/
