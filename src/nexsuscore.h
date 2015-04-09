/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.06.22
 Object handler(header)

********************************************************************
********************************************************************
********************************************************************/

extern short		NX_AllocateObject( unsigned int objnum );
extern void			NX_FreeObject( unsigned int objnum );
extern short		NX_SetAnimePattern( char *patstr, char *timestr );
extern short		NX_AddObject( double x, double y, double z, double sx, double sy, double sz, double g, short kind, short parent, short patnum, short visible, short active, short loop, short intersects, PNX_Rect rect, void *process );
extern short		NX_GetFreeObject( void );
extern void			NX_DelMasterObject( PmasterObj );
extern void			NX_MainLoop( void );
extern short		NX_CharacterMove( void );
extern void			NX_WaitJob( Puserparam usrprm, long num, long nextproc );
extern Puserparam	NX_GetObjectStructure( short );
extern PmasterObj	NX_GetObject( short );
extern void			NX_EventAction( short, short, void * );
extern short		NX_GetIntersects( Puserparam, Puserparam );
