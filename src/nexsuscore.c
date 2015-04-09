/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.06.22
 Object handler(source)

********************************************************************
********************************************************************
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nexsusdev.h"

static	HmasterObj			actorList;
static	unsigned long		__dispticks;

#define FPS	33L

/*******************************************************************
 基本オブジェクトの確保
 返値	 0:正常終了
		-1:メモリが足りない
********************************************************************/
short NX_AllocateObject( unsigned int objnum )
{
	unsigned long	i, j;
	short		retcode;
	PmasterObj	objWork;

	// 指定した数だけのオブジェクトを入れる箱を確保する
	actorList = ( HmasterObj )malloc( objnum * sizeof( PmasterObj ) );
	if( actorList == NULL ){ // 確保失敗
		retcode = -1;
	} else {
		for( i = 0; i < objnum; i++ ){ // 指定したオブジェクトの数だけループ
			objWork = ( PmasterObj )malloc( sizeof( masterObj ) ); // 構造体の実体を確保
			if( objWork == NULL ){ // 確保失敗
				for( j = 0; j < i; j++ ){ // すでに確保していたメモリを解放
					free( actorList[ j ] );
				}
				free( actorList ); // 入れものを解放
				retcode = -1;
			} else {
				( PmasterObj )actorList[ i ] = objWork;
				// 初期値を入れる
				objWork -> active = 0;
				objWork -> process = NULL;
				retcode = 0;
			}
		}
	}

	__dispticks = NX_GetTicks();

	return retcode;
}
/**/

/*******************************************************************
 基本オブジェクトの解放
********************************************************************/
void NX_FreeObject( unsigned int objnum )
{
	unsigned int	i;

	for( i = 0; i < objnum; i ++ ){
		free( actorList[ i ] );
	}
	free( actorList );
}
/**/

/*******************************************************************
 アニメパターンを登録する
 引数：	   pat:アニメのパターンをカンマデリミターでつないだ文字列
 返値		 0:正常終了
			-1:メモリが足りない
********************************************************************/
short NX_SetAnimePattern( char *patstr, char *timestr )
{
	short				retcode;
	short				i;
	short				loop;
	short				num;
	short				tmp;
	char				tmpstr[ 256 ];
	char				*head;
	PNX_SYSTEM_INFO		sysinfo;
	Hpatlist			pat;

	// システム情報へのポインタを取得する
	sysinfo = NX_GetSystemInfo();

	// アニメパターンリスト用メモリがあるかチェックし無かったら確保
	pat = sysinfo -> anipat.patlist;
	if( pat == NULL ){ // メモリがまだ確保されていなかったら確保する
		// アニメパターンの数だけポインタ用メモリを確保
		pat = ( Hpatlist )malloc( sizeof( Ppatlist ) * sysinfo -> ANIMENUM );
		if( pat == NULL ){
			retcode = -1;
			goto RETURN_CODE;
		} else {
			sysinfo -> anipat.patlist = pat;
			sysinfo -> anipat.patnum = 0; // 登録されているアニメパターンの数を0にする
		}
	}

	// アニメパターンとアニメタイムを入れる構造体を確保
	pat[ sysinfo -> anipat.patnum ] = ( Ppatlist )malloc( sizeof( patlist ) );
	if( pat == NULL ){
		retcode = -1;
		goto RETURN_CODE;
	} else {
		pat[ sysinfo -> anipat.patnum ] -> pat = NULL;
		pat[ sysinfo -> anipat.patnum ] -> time = NULL;
	}

	// アニメパターンの枚数をカウント
	num = 0;
	for( i = 0; i < strlen( patstr ); i++ ){
		if( patstr[ i ] == ',' ){
			num++;
		}
	}
	num++;

	// アニメパターンを入れる配列を確保
	pat[ sysinfo -> anipat.patnum ] -> pat = ( short * )malloc( sizeof( short ) * num + 1 );
	if( pat[ sysinfo -> anipat.patnum ] -> pat == NULL ){
		retcode = -1;
		goto RETURN_CODE;
	}
	// アニメパターンを登録
	head = patstr;
	pat[ sysinfo -> anipat.patnum ] -> pat[ 0 ] = num;
	for( loop = 1; loop <= num; loop++ ){
		tmp = NX_StrPos( head, "," );
		if( tmp == -1 ){
			tmp = strlen( head );
		}
		strncpy( tmpstr, head, tmp );
		tmpstr[ tmp ] = '\0';
		pat[ sysinfo -> anipat.patnum ] -> pat[ loop ] = atoi( tmpstr );
		head = &( head[ tmp + 1 ] );
	}

	// アニメタイムを入れる配列を確保
	pat[ sysinfo -> anipat.patnum ] -> time = ( short * )malloc( sizeof( short ) * num + 1 );
	if( pat[ sysinfo -> anipat.patnum ] -> time == NULL ){
		retcode = -1;
		goto RETURN_CODE;
	}
	// アニメタイムを登録
	head = timestr;
	pat[ sysinfo -> anipat.patnum ] -> time[ 0 ] = num;
	for( loop = 1; loop <= num; loop++ ){
		tmp = NX_StrPos( head, "," );
		if( tmp == -1 ){
			tmp = strlen( head );
		}
		strncpy( tmpstr, head, tmp );
		tmpstr[ tmp ] = '\0';
		pat[ sysinfo -> anipat.patnum ] -> time[ loop ] = atoi( tmpstr );
		head = &( head[ tmp + 1 ] );
	}

	sysinfo -> anipat.patnum = sysinfo -> anipat.patnum + 1; // 登録されているアニメパターンの数をインクリメントする

	retcode = 0;

RETURN_CODE:
	return retcode;
}
/**/


/*******************************************************************
 オブジェクトを登録する
 返値：		オブジェクト番号
			-1：空いているオブジェクトが無い
*******************************************************************/
short NX_AddObject( double x, double y, double z, double sx, double sy, double sz, double g, short kind, short parent, short patnum, short visible, short active, short loop, short intersects, PNX_Rect rect, void *process )
{
	mfunc		*mfx;
	PmasterObj	mobj;
	short		num;
	short		retcode;

	// 空いているオブジェクト番号を取得
	num = NX_GetFreeObject();
	if( num == -1 ){	// 空いているオブジェクトは無い
		retcode = -1;
		goto RETURN_CODE;
	}
	mobj = actorList[ num ];

	// 取得したオブジェクトに情報を設定
	mobj -> usrprm.num = num;
	mobj -> usrprm.loc.x = x;
	mobj -> usrprm.loc.y = y;
	mobj -> usrprm.loc.z = z;
	mobj -> usrprm.sp.sx = sx;
	mobj -> usrprm.sp.sy = sy;
	mobj -> usrprm.sp.sz = sz;
	mobj -> usrprm.g = g;
	mobj -> usrprm.parent = parent;
	mobj -> usrprm.visible = visible;
	mobj -> usrprm.intersects = intersects;
	mobj -> usrprm.pattern_num = patnum;

	mobj -> chara.kind = kind;
	mobj -> chara.animechara.anime_num = 1;
	mobj -> chara.animechara.loop = loop;
	mobj -> chara.animechara.timer = NX_GetTicks();
	mobj -> active = active;
	mobj -> process = process;

	mobj -> waitjob = 0;
	if( rect != NULL ){
		mobj -> usrprm.rect.x1 = rect -> x1;
		mobj -> usrprm.rect.y1 = rect -> y1;
		mobj -> usrprm.rect.x2 = rect -> x2;
		mobj -> usrprm.rect.y2 = rect -> y2;
	}

	// コンストラクター処理
	mfx = ( mfunc * )process;
	if( mfx != NULL ){
		mobj -> usrprm.processnum = NX_CONST;
		( *mfx )( &( mobj -> usrprm ), NULL );
	}

	mobj -> usrprm.processnum = 1;

	retcode = num;

RETURN_CODE:
	return retcode;
}
/**/

/*******************************************************************
 オブジェクトを抹消する
*******************************************************************/
void NX_DelMasterObject( PmasterObj mobj )
{
	mfunc	*mfx;

	mobj -> active = 0;
	mobj -> usrprm.visible = 0;

	// デストラクタ処理
	mfx = ( mfunc * )mobj -> process;
	if( mfx != NULL ){
		mobj -> usrprm.processnum = NX_DEST;
		( *mfx )( &( mobj -> usrprm ), NULL );
	}
}
/**/

/*******************************************************************
 空いているオブジェクト番号を探して返す
*******************************************************************/
short NX_GetFreeObject( void )
{
	PNX_SYSTEM_INFO		sysinfo;
	PmasterObj			mobj;
	short				i;
	short				retcode;

	// システム情報へのポインタを取得する
	sysinfo = NX_GetSystemInfo();

	retcode = -1;
	for( i = 0; i < sysinfo -> OBJECTNUM; i++ ){
		mobj = actorList[ i ];
		if( mobj -> active == 0 ){
			retcode = i;
			break;
		}
	}

	return retcode;
}
/**/

/*******************************************************************
 メインループ
*******************************************************************/
void NX_MainLoop( void )
{
	short	result;
	short	endflag;
	short	ret;

	endflag = 0;
	while( endflag == 0 ){
		ret = NX_GetSDLEvent( &result );
		switch( ret ){
			case NX_QUIT:
				endflag = 1;
				break;
			case NX_KEYDOWN:
				if( result == 0x71 ){
					endflag = 1;
				}
				break;
			default:
				break;
		}

		NX_CharacterMove();
		NX_UpdateStage();
	}
}
/**/

/*******************************************************************
 各キャラクタを活動させる
 返値：描画したオブジェクトの数
*******************************************************************/
short NX_CharacterMove( void )
{
	PNX_SYSTEM_INFO		sysinfo;
	PmasterObj			mobj;
	short				i;
	short				pnum, tnum;
	Hpatlist			pat;
	short				loop;
	long				now_ticks;
	long				coordtmp;
	mfunc				*pfunc;

	// 現在のticksを取得する
	now_ticks = NX_GetTicks();

	// システム情報へのポインタを取得する
	sysinfo = NX_GetSystemInfo();
	pat = sysinfo -> anipat.patlist;

	loop = 0;
	for( i = 0; i < sysinfo -> OBJECTNUM; i++ ){
		mobj = actorList[ i ];

		if( mobj -> active == 1 ){

			// 前回の処理から1/62.5秒経っていたら処理する
			if( __dispticks + FPS <= now_ticks ){

				// 動作を関数で制御する
				pfunc = mobj -> process;
				if( pfunc != NULL ){
					pfunc( &( mobj -> usrprm ), NULL );
				}

				if( mobj -> usrprm.processnum == NX_WAITJOB ){
					mobj -> waitjob--;
					if( mobj -> waitjob == 0 ){
						mobj -> usrprm.processnum = mobj -> nextprocess;
					}
				}

				// 座標を更新する
				mobj -> usrprm.loc.x = mobj -> usrprm.loc.x + mobj -> usrprm.sp.sx;
				mobj -> usrprm.loc.z = mobj -> usrprm.loc.z + mobj -> usrprm.sp.sz;
				mobj -> usrprm.sp.sy += mobj -> usrprm.g;
				mobj -> usrprm.loc.y = mobj -> usrprm.loc.y + mobj -> usrprm.sp.sy + mobj -> usrprm.loc.z;
			}

			// アニメを更新する
			pnum = mobj -> usrprm.pattern_num;
			tnum = mobj -> chara.animechara.anime_num;

			if( mobj -> chara.animechara.anime_num > pat[ pnum ] -> pat[ 0 ] ){
				mobj -> chara.animechara.anime_num = 1;
			}

			if( mobj -> chara.animechara.timer + pat[ pnum ] -> time[ tnum ] < now_ticks ){
				mobj -> chara.animechara.timer = now_ticks;
				if( tnum + 1 > pat[ pnum ] -> pat[ 0 ] ){
					if( mobj -> chara.animechara.loop == 1 ){
						mobj -> chara.animechara.anime_num = 1;
					}
				} else {
					mobj -> chara.animechara.anime_num = tnum + 1;
				}
			}

			// 描画する
			if( mobj -> usrprm.visible == 1 ){
				switch( mobj -> chara.kind ){
					case NX_ANIME: // 二次元アニメ
						NX_CharacterBlit( mobj -> usrprm.pattern_num,
						mobj -> chara.animechara.anime_num, ( long )( mobj -> usrprm.loc.x ), ( long )( mobj -> usrprm.loc.y ) );
						break;
					default:
						break;
				}
			}

			loop++;
		}

	}

	if( __dispticks + FPS <= now_ticks ){
		__dispticks = now_ticks;
	}

	return loop + 1;
}
/**/

/*******************************************************************
 waitJob処理
*******************************************************************/
void NX_WaitJob( Puserparam usrprm, long num, long nextproc )
{
	PmasterObj mobj;

	mobj = NX_GetObject( usrprm -> num );

	mobj -> waitjob = num;
	if( nextproc == 0 ){
		mobj -> nextprocess = mobj -> usrprm.processnum + 1;
	} else {
		mobj -> nextprocess = nextproc;
	}
	mobj -> usrprm.processnum = NX_WAITJOB;
}
/**/

/*******************************************************************
 指定した番号のオブジェクトの情報だけの構造体のポインタを返す
*******************************************************************/
Puserparam NX_GetObjectStructure( short objnum )
{
	if( objnum >= 0 ){
		return &( actorList[ objnum ] -> usrprm );
	} else {
		return NULL;
	}
}
/**/

/*******************************************************************
 指定した番号のオブジェクトの構造体のポインタを返す
*******************************************************************/
PmasterObj NX_GetObject( short objnum )
{
	if( objnum >= 0 ){
		return actorList[ objnum ];
	} else {
		return NULL;
	}
}
/**/

/*******************************************************************
 指定した番号のオブジェクトに指定された番号のイベントを引数を伴って実行させる
*******************************************************************/
void NX_EventAction( short num, short ev, void *arg )
{
	PmasterObj			mobj;
	mfunc				*pfunc;
	short				bk;

	mobj = NX_GetObject( num );
	bk = mobj -> usrprm.processnum;
	mobj -> usrprm.processnum = ev;

	// 動作定義関数を起動する
	pfunc = mobj -> process;
	if( pfunc != NULL ){
		pfunc( &( mobj -> usrprm ), arg );
	}
	if( mobj -> usrprm.processnum == ev ){
		mobj -> usrprm.processnum = bk;
	}
}
/**/

/*******************************************************************
 渡された2つのオブジェクトの持つrectの重なり判定
 返値：	0 = 重なっていない
        1 = 重なっている
*******************************************************************/
short NX_GetIntersects( Puserparam obj1, Puserparam obj2 )
{
	PNX_SYSTEM_INFO		sysinfo;
	NX_Rect				aRect1, aRect2;
	short				ret;
	short				pnum, tnum;
	coord				reg;
	Hpatlist			pat;
	PmasterObj			mobj1, mobj2;

	if( obj1 -> intersects == 0 || obj2 -> intersects == 0 ){
		return 0;
	}

	sysinfo = NX_GetSystemInfo();
	pat = sysinfo -> anipat.patlist;
	mobj1 = NX_GetObject( obj1 -> num );
	mobj2 = NX_GetObject( obj2 -> num );

	pnum = obj1 -> pattern_num;
	tnum = mobj1 -> chara.animechara.anime_num;
	reg.x = sysinfo -> charareg[ pat[ pnum ] -> pat[ tnum ] ] -> x;
	reg.y = sysinfo -> charareg[ pat[ pnum ] -> pat[ tnum ] ] -> y;

	aRect1.x1 = obj1 -> loc.x + obj1 -> rect.x1 + reg.x;
	aRect1.y1 = obj1 -> loc.y + obj1 -> rect.y1 + reg.y;
	aRect1.x2 = obj1 -> loc.x + obj1 -> rect.x2 + reg.x;
	aRect1.y2 = obj1 -> loc.y + obj1 -> rect.y2 + reg.y;

	pnum = obj2 -> pattern_num;
	tnum = mobj2 -> chara.animechara.anime_num;
	reg.x = sysinfo -> charareg[ pat[ pnum ] -> pat[ tnum ] ] -> x;
	reg.y = sysinfo -> charareg[ pat[ pnum ] -> pat[ tnum ] ] -> y;

	aRect2.x1 = obj2 -> loc.x + obj2 -> rect.x1 + reg.x;
	aRect2.y1 = obj2 -> loc.y + obj2 -> rect.y1 + reg.y;
	aRect2.x2 = obj2 -> loc.x + obj2 -> rect.x2 + reg.x;
	aRect2.y2 = obj2 -> loc.y + obj2 -> rect.y2 + reg.y;

	ret = 0;
	if( ( aRect1.x2 > aRect2.x1 ) && ( aRect1.x2 < aRect2.x2 ) && ( aRect1.y2 > aRect2.y1 ) && ( aRect1.y2 < aRect2.y2 ) ){
		ret = 1;
	}
	if( ( aRect2.x2 > aRect1.x1 ) && ( aRect2.x2 < aRect1.x2 ) && ( aRect2.y2 > aRect1.y1 ) && ( aRect2.y2 < aRect1.y2 ) ){
		ret = 1;
	}
	if( ( aRect1.x1 > aRect2.x1 ) && ( aRect1.x1 < aRect2.x2 ) && ( aRect1.y2 > aRect2.y1 ) && ( aRect1.y2 < aRect2.y2 ) ){
		ret = 1;
	}
	if( ( aRect2.x1 > aRect1.x1 ) && ( aRect2.x1 < aRect1.x2 ) && ( aRect2.y2 > aRect1.y1 ) && ( aRect2.y2 < aRect1.y2 ) ){
		ret = 1;
	}

	return ret;
}
/**/
