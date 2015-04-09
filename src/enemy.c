/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.07.13
 stationary object file

 オブジェクトの動きを定義する
 constructor()に初期化処理を記述、destructor()にオブジェクトが消滅するときの処理を記述
 objprocess()をオブジェクトの動作を定義する関数名に変えて各処理番号の処理を記述する。

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

// オブジェクトの動作を定義する
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
			NX_EventAction( mcp, 99, ( void * )usrprm ); // 弾に当たったか
			NX_EventAction( mship, 99, ( void * )usrprm ); // 自機に当たったか
			break;

		case 2:
			usrprm -> sp.sx += ( 0.1 * ( usrprm -> sp.sx > 0 ) ) + ( -0.1 * ( usrprm -> sp.sx < 0 ) );
			if( usrprm -> loc.y > 320 || usrprm -> loc.x < -32 || usrprm -> loc.x > 240 ){
				tmp = NX_GetRandom( 40, 200 );
				NX_AddObject( tmp, -32, 0, 0, NX_GetRandom( 5, 8 ), 0, 0, NX_ANIME, usrprm -> num, 5, 1, 1, 1, 1, &( usrprm -> rect ), enemy );
				NX_DelObject( usrprm );
			}
			NX_EventAction( mcp, 99, ( void * )usrprm ); // 弾に当たったか
			NX_EventAction( mship, 99, ( void * )usrprm ); // 自機に当たったか
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
 コンストラクター
********************************************************************/
void constructor( Puserparam usrprm )
{
	;
}
/**/

/********************************************************************
 デストラクター
********************************************************************/
void destructor( Puserparam usrprm )
{
	;
}
/**/
