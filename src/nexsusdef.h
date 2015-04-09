/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.06.22
 common header

********************************************************************
********************************************************************
********************************************************************/

// ��ɸ
typedef struct {
    double  x;              // x��ɸ
    double  y;              // y��ɸ
    long    z;              // z��ɸ
} coord, *Pcoord, **Hcoord;

// �ͳ�
typedef struct {
    short x1;
    short y1;
    short x2;
    short y2;
} NX_Rect, *PNX_Rect, **HNX_Rect;

// ��ư��
typedef struct {
    double  sx;             // ��ʿ������ư��
    double  sy;             // ��ľ������ư���
    double  sz;             // ���Ԥ�������ư��
} speed, *Pspeed, **Hspeed;

// 2D���˥�
typedef struct {
	short	anime_num;		// ����ɽ�����Ƥ��륢�˥�ѥ�������β����ֹ�
	short	loop;			// ���˥�ѥ������롼�פ����뤫(0:���ʤ� 1:����)
	long	timer;			// ���˥��ɽ�����뤿��Υ����ޡ�
} anime, *Panime, **Hanime;

// ���˥�ѥ������ɽ�����֤Υꥹ��
typedef struct {
	short	*pat;			// ���˥�ѥ�����ꥹ��
	short	*time;			// ɽ�����֥ꥹ��
} patlist, *Ppatlist, **Hpatlist;

// 2D���˥�ѥ�����
typedef struct {
	short		patnum;		// ��Ͽ����Ƥ���ѥ�����ο�
	Hpatlist	patlist;	// ���˥�ѥ����������ݥ��󥿤�����
} animepattern, *Panimepattern, **Hanimepattern;

// ����������
typedef struct {
	short	kind;
	anime	animechara;
} element, *Pelement, **Helement;

// �桼�����������������
typedef struct {
    short   num;                // ���֥��������ֹ�
    short   parent;             // �ƥ��֥��������ֹ�
    coord   loc;                // ��ɸ
    speed   sp;                 // ��ư��
    double  g;                  // ����
    short   visible;            // ɽ������ɽ���ե饰
    short   processnum;         // �����ǻ��Ѥ���ץ����ֹ�
    short   intersects;         // ������Ƚ����뤫
    short   pattern_num;        // ���߻��Ѥ��Ƥ��륢�˥�ѥ������ֹ�
    NX_Rect rect;               // ������Ƚ���Ѷ��
} userparam, *Puserparam, **Huserparam;

// ���ܥ��֥�������
typedef struct {
        userparam       usrprm;                 // �桼�����������������
        element         chara;                  // ���֥������Ȥ����ĥ������(ư���������륪�֥������Ȥʤ�NULL)
        short           active;                 // ���Υ��֥������Ȥ����Ѥ���Ƥ��뤫(0:���Ѥ���Ƥ��ʤ� 1:���Ѥ���Ƥ���)
        void            *process;               // ư��򵭽Ҥ��Ƥ���ؿ��ݥ���
        void            *proc;                  // �ƥ��֥������Ȥ��ȼ��˻��ľ����Ǽ��
        long            waitjob;                // waitJob������
        long            nextprocess;    // waitjob�λ��˼��˰ܤ�ץ����ֹ�
} masterObj, *PmasterObj, **HmasterObj;

// �ؿ��ݥ��󥿷�
typedef int *mfunc( Puserparam, void * );
