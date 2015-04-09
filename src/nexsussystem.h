/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.06.22
 SDL : System Initialize(header)

********************************************************************
********************************************************************
********************************************************************/

extern void					NX_ArgInit( int *, char *** );
extern short				NX_SystemInit( int *, char *** ); // nexsusシステムを初期化する
extern PNX_SYSTEM_INFO		NX_GetSystemInfo( void );
extern short				NX_LoadBitmapFile( char *, char * );
extern void					NX_MemoryFree( void );
extern short				NX_GetSDLEvent( short * );
extern unsigned long		NX_GetTicks( void );
extern void					NX_CharacterBlit( short, short, long, long );
extern void					NX_UpdateStage( void );
extern short				NX_isKeypress( short );
extern short				NX_isStick( short );
