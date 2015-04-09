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

#include <stdio.h>
#include "nexsus.h"

#define MISSILENUM 3

static void constructor( Puserparam );
static void destructor( Puserparam );

extern mfunc missile;

static short 	__missile_list[ MISSILENUM ];

void missile_control( Puserparam usrprm, void *arg )
{
	short		i;
	Pcoord		coord;
	Puserparam	pobj;
	NX_Rect		rect;

	switch( usrprm -> processnum ){

		case 1:
			break;

		case 2:	// �ߥ�����ȯ��
			for( i = 0; i < MISSILENUM; i++ ){
				if( __missile_list[ i ] == -1 ){
					coord = ( Pcoord )arg;
					rect.x1 = 0; rect.y1 = 0; rect.x2 = 10; rect.y2 = 10;
					__missile_list[ i ] = NX_AddObject( coord -> x, coord -> y, 0, 0, -16, 0, 0, NX_ANIME, usrprm -> num, 4, 1, 1, 1, 1, &rect, missile );
					break;
				}
			}
			break;

		case 3: // �ߥ��������
			for( i = 0; i < MISSILENUM; i++ ){
				if( __missile_list[ i ] == ( ( Puserparam )arg ) -> num ){
					__missile_list[ i ] = -1;
					NX_DelObject( ( Puserparam )arg );
					break;
				}
			}
			break;

		case 99: // �Ϥ��줿���֥������ȤȤ�������Ƚ��
			for( i = 0; i < MISSILENUM; i++ ){
				if( __missile_list[ i ] != -1 ){
					pobj = NX_GetObjectStructure( __missile_list[ i ] );
					if( NX_GetIntersects( pobj, ( Puserparam )arg ) != 0 ){
						__missile_list[ i ] = -1;
						NX_EventAction( ( ( Puserparam )arg ) -> num, 99, NULL );
						NX_DelObject( pobj );
						break;
					}
				}
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
	short	i;

	for( i = 0; i < MISSILENUM; i++ ){
		__missile_list[ i ] = -1;
	}
}
/**/

void destructor( Puserparam usrprm )
{
	;
}
/**/
