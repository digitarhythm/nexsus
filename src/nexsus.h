/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.06.22
 user common header

********************************************************************
********************************************************************
********************************************************************/

#include "nexsusdef.h"
#include "sysinfo.h"
#include "nexsussystem.h"
#include "nexsuscore.h"
#include "nexsusutil.h"
#include "nexsusobj.h"

// ���֥������Ȥμ�������
#define NX_ANIME			1
#define NX_3DIM				2

// ���顼���������
#define NX_OUTOFMEMORY		-1
#define NX_NOERR			0

// ���٥�����
#define NX_QUIT				1
#define NX_KEYDOWN			2

// �ץ�����
#define NX_WAITJOB			-2
#define NX_DEST				-1
#define NX_CONST			0

// ���ƥ��å�������
#define NX_UP_CURSOR		1
#define NX_DW_CURSOR		2
#define NX_LF_CURSOR		3
#define NX_RT_CURSOR		4

static char debug[ 256 ];
