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

#include "nexsus.h"

static void constructor( Puserparam );
static void destructor( Puserparam );

void wall( Puserparam usrprm, void *arg )
{
	switch( usrprm -> processnum ){

		case 1:
			if( usrprm -> loc.y >= 320 ){
				usrprm -> loc.y = -320;
			}
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
