// �����ƥ������Ǽ���빽¤��
typedef struct {
    short           AUDIO;                  // �����ǥ�����������뤫�ե饰
    short           VIDEO;                  // �ӥǥ���������뤫�ե饰
    short           CDROM;                  // CD-ROM��������뤫�ե饰
    short           TIMER;                  // �����ޡ���������뤫�ե饰
    short           JSTCK;                  // ���祤���ƥ��å���������뤫�ե饰
    short           WIDTH;                  // ���̤β���
    short           HEIGHT;                 // ���̤ν���
    unsigned int    SCREENMODE;             // ���̥⡼��
    unsigned int    OBJECTNUM;              // �������륪�֥������Ȥο�
    char            CHARACTERFNAME[ 256 ];  // ����饯�������ե�����Υѥ�+�ե�����̾
    char            MAPFNAME[ 256 ];        // ����饯������ե�����Υѥ�+�ե�����̾
    short           CHARANUM;               // �����ѥ��ݥ�ο�
    short           ANIMENUM;               // ���˥�ѥ�����ο�
    animepattern    anipat;                 // ���˥�ѥ�����
    void            *screen;                // ����ɽ���ѥ����ե�����
    void            *character;             // ����饯�������ѥ����ե�����
    HNX_Rect        charamap;               // �ƥ���饯���κ�ɸ����
    Hcoord          charareg;               // �ƥ���饯���δ����
    short           mouse;                  // �ޥ�����������ɽ���ե饰
} NX_SYSTEM_INFO, *PNX_SYSTEM_INFO, **HNX_SYSTEM_INFO;

