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

void objprocess( Puserparam usrprm, void *arg )
{
	switch( usrprm -> processnum ){

		case 1:	// ���֥������Ȥ�ư������
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
	;
}
/**/
