/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.07.13
 stationary object file

 オブジェクトの動きを定義する
 constructor()に初期化処理を記述、destructor()にオブジェクトが消滅するときの処理を記述
 objprocess()に各処理番号の処理を記述しオブジェクトの動作を定義する関数の名前に変える

********************************************************************
********************************************************************
********************************************************************/

#include "nexsus.h"

static void constructor( Puserparam );
static void destructor( Puserparam );

void objprocess( Puserparam usrprm, void *arg )
{
	switch( usrprm -> processnum ){

		case 1:	// オブジェクトの動作の定義
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
