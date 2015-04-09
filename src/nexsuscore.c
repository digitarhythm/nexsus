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
 ���ܥ��֥������Ȥγ���
 ����	 0:���ｪλ
		-1:���꤬­��ʤ�
********************************************************************/
short NX_AllocateObject( unsigned int objnum )
{
	unsigned long	i, j;
	short		retcode;
	PmasterObj	objWork;

	// ���ꤷ���������Υ��֥������Ȥ������Ȣ����ݤ���
	actorList = ( HmasterObj )malloc( objnum * sizeof( PmasterObj ) );
	if( actorList == NULL ){ // ���ݼ���
		retcode = -1;
	} else {
		for( i = 0; i < objnum; i++ ){ // ���ꤷ�����֥������Ȥο������롼��
			objWork = ( PmasterObj )malloc( sizeof( masterObj ) ); // ��¤�Τμ��Τ����
			if( objWork == NULL ){ // ���ݼ���
				for( j = 0; j < i; j++ ){ // ���Ǥ˳��ݤ��Ƥ�����������
					free( actorList[ j ] );
				}
				free( actorList ); // �����Τ����
				retcode = -1;
			} else {
				( PmasterObj )actorList[ i ] = objWork;
				// ����ͤ������
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
 ���ܥ��֥������Ȥβ���
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
 ���˥�ѥ��������Ͽ����
 ������	   pat:���˥�Υѥ�����򥫥�ޥǥ�ߥ����ǤĤʤ���ʸ����
 ����		 0:���ｪλ
			-1:���꤬­��ʤ�
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

	// �����ƥ����ؤΥݥ��󥿤��������
	sysinfo = NX_GetSystemInfo();

	// ���˥�ѥ�����ꥹ���ѥ��꤬���뤫�����å���̵���ä������
	pat = sysinfo -> anipat.patlist;
	if( pat == NULL ){ // ���꤬�ޤ����ݤ���Ƥ��ʤ��ä�����ݤ���
		// ���˥�ѥ�����ο������ݥ����ѥ�������
		pat = ( Hpatlist )malloc( sizeof( Ppatlist ) * sysinfo -> ANIMENUM );
		if( pat == NULL ){
			retcode = -1;
			goto RETURN_CODE;
		} else {
			sysinfo -> anipat.patlist = pat;
			sysinfo -> anipat.patnum = 0; // ��Ͽ����Ƥ��륢�˥�ѥ�����ο���0�ˤ���
		}
	}

	// ���˥�ѥ�����ȥ��˥᥿���������빽¤�Τ����
	pat[ sysinfo -> anipat.patnum ] = ( Ppatlist )malloc( sizeof( patlist ) );
	if( pat == NULL ){
		retcode = -1;
		goto RETURN_CODE;
	} else {
		pat[ sysinfo -> anipat.patnum ] -> pat = NULL;
		pat[ sysinfo -> anipat.patnum ] -> time = NULL;
	}

	// ���˥�ѥ����������򥫥����
	num = 0;
	for( i = 0; i < strlen( patstr ); i++ ){
		if( patstr[ i ] == ',' ){
			num++;
		}
	}
	num++;

	// ���˥�ѥ�������������������
	pat[ sysinfo -> anipat.patnum ] -> pat = ( short * )malloc( sizeof( short ) * num + 1 );
	if( pat[ sysinfo -> anipat.patnum ] -> pat == NULL ){
		retcode = -1;
		goto RETURN_CODE;
	}
	// ���˥�ѥ��������Ͽ
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

	// ���˥᥿������������������
	pat[ sysinfo -> anipat.patnum ] -> time = ( short * )malloc( sizeof( short ) * num + 1 );
	if( pat[ sysinfo -> anipat.patnum ] -> time == NULL ){
		retcode = -1;
		goto RETURN_CODE;
	}
	// ���˥᥿�������Ͽ
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

	sysinfo -> anipat.patnum = sysinfo -> anipat.patnum + 1; // ��Ͽ����Ƥ��륢�˥�ѥ�����ο��򥤥󥯥���Ȥ���

	retcode = 0;

RETURN_CODE:
	return retcode;
}
/**/


/*******************************************************************
 ���֥������Ȥ���Ͽ����
 ���͡�		���֥��������ֹ�
			-1�������Ƥ��륪�֥������Ȥ�̵��
*******************************************************************/
short NX_AddObject( double x, double y, double z, double sx, double sy, double sz, double g, short kind, short parent, short patnum, short visible, short active, short loop, short intersects, PNX_Rect rect, void *process )
{
	mfunc		*mfx;
	PmasterObj	mobj;
	short		num;
	short		retcode;

	// �����Ƥ��륪�֥��������ֹ�����
	num = NX_GetFreeObject();
	if( num == -1 ){	// �����Ƥ��륪�֥������Ȥ�̵��
		retcode = -1;
		goto RETURN_CODE;
	}
	mobj = actorList[ num ];

	// �����������֥������Ȥ˾��������
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

	// ���󥹥ȥ饯��������
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
 ���֥������Ȥ����ä���
*******************************************************************/
void NX_DelMasterObject( PmasterObj mobj )
{
	mfunc	*mfx;

	mobj -> active = 0;
	mobj -> usrprm.visible = 0;

	// �ǥ��ȥ饯������
	mfx = ( mfunc * )mobj -> process;
	if( mfx != NULL ){
		mobj -> usrprm.processnum = NX_DEST;
		( *mfx )( &( mobj -> usrprm ), NULL );
	}
}
/**/

/*******************************************************************
 �����Ƥ��륪�֥��������ֹ��õ�����֤�
*******************************************************************/
short NX_GetFreeObject( void )
{
	PNX_SYSTEM_INFO		sysinfo;
	PmasterObj			mobj;
	short				i;
	short				retcode;

	// �����ƥ����ؤΥݥ��󥿤��������
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
 �ᥤ��롼��
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
 �ƥ���饯�����ư������
 ���͡����褷�����֥������Ȥο�
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

	// ���ߤ�ticks���������
	now_ticks = NX_GetTicks();

	// �����ƥ����ؤΥݥ��󥿤��������
	sysinfo = NX_GetSystemInfo();
	pat = sysinfo -> anipat.patlist;

	loop = 0;
	for( i = 0; i < sysinfo -> OBJECTNUM; i++ ){
		mobj = actorList[ i ];

		if( mobj -> active == 1 ){

			// ����ν�������1/62.5�÷ФäƤ������������
			if( __dispticks + FPS <= now_ticks ){

				// ư���ؿ������椹��
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

				// ��ɸ�򹹿�����
				mobj -> usrprm.loc.x = mobj -> usrprm.loc.x + mobj -> usrprm.sp.sx;
				mobj -> usrprm.loc.z = mobj -> usrprm.loc.z + mobj -> usrprm.sp.sz;
				mobj -> usrprm.sp.sy += mobj -> usrprm.g;
				mobj -> usrprm.loc.y = mobj -> usrprm.loc.y + mobj -> usrprm.sp.sy + mobj -> usrprm.loc.z;
			}

			// ���˥�򹹿�����
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

			// ���褹��
			if( mobj -> usrprm.visible == 1 ){
				switch( mobj -> chara.kind ){
					case NX_ANIME: // �󼡸����˥�
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
 waitJob����
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
 ���ꤷ���ֹ�Υ��֥������Ȥξ�������ι�¤�ΤΥݥ��󥿤��֤�
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
 ���ꤷ���ֹ�Υ��֥������Ȥι�¤�ΤΥݥ��󥿤��֤�
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
 ���ꤷ���ֹ�Υ��֥������Ȥ˻��ꤵ�줿�ֹ�Υ��٥�Ȥ������ȼ�äƼ¹Ԥ�����
*******************************************************************/
void NX_EventAction( short num, short ev, void *arg )
{
	PmasterObj			mobj;
	mfunc				*pfunc;
	short				bk;

	mobj = NX_GetObject( num );
	bk = mobj -> usrprm.processnum;
	mobj -> usrprm.processnum = ev;

	// ư������ؿ���ư����
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
 �Ϥ��줿2�ĤΥ��֥������Ȥλ���rect�νŤʤ�Ƚ��
 ���͡�	0 = �ŤʤäƤ��ʤ�
        1 = �ŤʤäƤ���
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
