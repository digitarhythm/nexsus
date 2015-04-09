// システム情報を格納する構造体
typedef struct {
    short           AUDIO;                  // オーディオ初期化するかフラグ
    short           VIDEO;                  // ビデオ初期化するかフラグ
    short           CDROM;                  // CD-ROM初期化するかフラグ
    short           TIMER;                  // タイマー初期化するかフラグ
    short           JSTCK;                  // ジョイスティック初期化するかフラグ
    short           WIDTH;                  // 画面の横幅
    short           HEIGHT;                 // 画面の縦幅
    unsigned int    SCREENMODE;             // 画面モード
    unsigned int    OBJECTNUM;              // 作成するオブジェクトの数
    char            CHARACTERFNAME[ 256 ];  // キャラクタ画像ファイルのパス+ファイル名
    char            MAPFNAME[ 256 ];        // キャラクタ定義ファイルのパス+ファイル名
    short           CHARANUM;               // 画像パタ−ンの数
    short           ANIMENUM;               // アニメパターンの数
    animepattern    anipat;                 // アニメパターン
    void            *screen;                // 画面表示用サーフェース
    void            *character;             // キャラクタ画像用サーフェース
    HNX_Rect        charamap;               // 各キャラクタの座標情報
    Hcoord          charareg;               // 各キャラクタの基準点
    short           mouse;                  // マウスカーソル表示フラグ
} NX_SYSTEM_INFO, *PNX_SYSTEM_INFO, **HNX_SYSTEM_INFO;

