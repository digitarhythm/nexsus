/*******************************************************************
********************************************************************
********************************************************************

 NEXSUS GAME Create System created 2001.06.22
 gtk+ : Utility routine(source)

********************************************************************
********************************************************************
********************************************************************/

#include <stdlib.h>
//#include "gtk/gtk.h"

#include "nexsusdev.h"
/*
//*******************************************************************
// Message Box
//*******************************************************************
gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data )
{
	return FALSE;
}

void destroy( GtkWidget *widget, GdkEvent *event, gpointer data )
{
	gtk_main_quit();
}

void clicked( GtkWidget *widget, GtkWidget *window )
{
	gtk_widget_destroy( window );
	gtk_main_quit();
}
*/
/*******************************************************************
 指定したウィンドウタイトルで指定したテキストと指定した文字のボタンのダイアログを表示する
*******************************************************************/
void NX_MessageBox( char *title, char *str, char *btitle )
{
/*	GtkWidget	*window;
	GtkWidget	*pack;
	GtkWidget	*button;
	GtkWidget	*text;

	gtk_rc_parse( "~/gtkrc" );
	window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	gtk_window_set_title( GTK_WINDOW( window ), title );
	text = gtk_label_new( str );
	button = gtk_button_new_with_label( btitle );
	pack = gtk_vbox_new( 0, 2 );
	gtk_box_pack_start( GTK_BOX( pack ), text, TRUE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX( pack ), button, TRUE, FALSE, 2 );
	gtk_container_add( GTK_CONTAINER( window ), pack );
	gtk_signal_connect( GTK_OBJECT( window ), "delete_event", GTK_SIGNAL_FUNC( delete_event ), NULL );
	gtk_signal_connect( GTK_OBJECT( window ), "destroy", GTK_SIGNAL_FUNC( destroy ), NULL );
	gtk_signal_connect( GTK_OBJECT( button ), "clicked", GTK_SIGNAL_FUNC( clicked ), window );
	gtk_widget_show( window );
	gtk_widget_show( pack );
	gtk_widget_show( button );
	gtk_widget_show( text );
	gtk_main();*/
}
/**/

//#################################################################
// 文字列str1の中に文字列str2が含まれているか
// 含まれている場合はstr1内でのstr2の始まりの場所(複数ある場合は最初に出現したもの)を返す
// 含まれていない場合は-1が返る
//#################################################################
short NX_StrPos( char *str1, char *str2 )
{
	short	i, j;
	short	retcode;

	for( i = 0; i < strlen( str1 ); i++ ){ // str1のループ
		if( str1[ i ] == str2[ 0 ] ){ // str2の最初の一文字目が見付かった
			for( j = 1; j < strlen( str2 ); j++ ){ // str2のループ
				if( str1[ i + j ] != str2[ j ] ){ // 違う文字が見付かった
					break;
				}
			}
			if( j == strlen( str2 ) ){ // str2に完全に一致する文字列が含まれていた
				retcode = i;
				goto RETURN_CODE;
			}
		}
	}

	retcode = -1; // str2は含まれていなかった

RETURN_CODE:
	return retcode;
}
/**/

//#################################################################
// 指定された範囲の乱数を返す
//#################################################################
long NX_GetRandom( long st, long ed )
{
	return  ( rand() % ( ed - st + 1 ) ) + st;
}
/**/
