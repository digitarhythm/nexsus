/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.06.22
 common header

********************************************************************
********************************************************************
********************************************************************/

// 座標
typedef struct {
    double  x;              // x座標
    double  y;              // y座標
    long    z;              // z座標
} coord, *Pcoord, **Hcoord;

// 四角
typedef struct {
    short x1;
    short y1;
    short x2;
    short y2;
} NX_Rect, *PNX_Rect, **HNX_Rect;

// 移動量
typedef struct {
    double  sx;             // 水平方向移動量
    double  sy;             // 垂直方向移動頼ハ
    double  sz;             // 奥行き方向移動量
} speed, *Pspeed, **Hspeed;

// 2Dアニメ
typedef struct {
	short	anime_num;		// 現在表示しているアニメパターン内の画像番号
	short	loop;			// アニメパターンをループさせるか(0:しない 1:する)
	long	timer;			// アニメを表示するためのタイマー
} anime, *Panime, **Hanime;

// アニメパターンと表示時間のリスト
typedef struct {
	short	*pat;			// アニメパターンリスト
	short	*time;			// 表示時間リスト
} patlist, *Ppatlist, **Hpatlist;

// 2Dアニメパターン
typedef struct {
	short		patnum;		// 登録されているパターンの数
	Hpatlist	patlist;	// アニメパターンの配列ポインタの配列
} animepattern, *Panimepattern, **Hanimepattern;

// エレメント定義
typedef struct {
	short	kind;
	anime	animechara;
} element, *Pelement, **Helement;

// ユーザーの操作出来る要素
typedef struct {
    short   num;                // オブジェクト番号
    short   parent;             // 親オブジェクト番号
    coord   loc;                // 座標
    speed   sp;                 // 移動量
    double  g;                  // 重力
    short   visible;            // 表示／非表示フラグ
    short   processnum;         // 内部で使用するプロセス番号
    short   intersects;         // 当たり判定を取るか
    short   pattern_num;        // 現在使用しているアニメパターン番号
    NX_Rect rect;               // 当たり判定用矩形
} userparam, *Puserparam, **Huserparam;

// 基本オブジェクト
typedef struct {
        userparam       usrprm;                 // ユーザーが操作出来る要素
        element         chara;                  // オブジェクトが持つエレメント(動作を定義するオブジェクトならNULL)
        short           active;                 // このオブジェクトが使用されているか(0:使用されていない 1:使用されている)
        void            *process;               // 動作を記述してある関数ポインタ
        void            *proc;                  // 各オブジェクトが独自に持つ情報格納用
        long            waitjob;                // waitJob処理用
        long            nextprocess;    // waitjobの時に次に移るプロセス番号
} masterObj, *PmasterObj, **HmasterObj;

// 関数ポインタ型
typedef int *mfunc( Puserparam, void * );
