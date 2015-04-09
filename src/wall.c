/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.07.13
 stationary object file

 オブジェクトの動きを定義する
 constructor()に初期化処理を記述、destructor()にオブジェクトが消滅するときの処理を記述
 objprocess()に各処理番号の処理を記述する。

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

		case NX_CONST:	// コンストラクター
			constructor( usrprm );
		break;
		case NX_DEST:	// デストラクター
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
