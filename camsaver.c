#include <stdio.h>
#include "camera.h"
#include <dbus/dbus-glib.h>
#include <stdlib.h>

// dbus connection information
static DBusGConnection *conn;
static GError *err;
static DBusGProxy *proxy;

// dbus http://www.matthew.ath.cx/misc/dbus
// qdbus org.gnome.ScreenSaver / org.gnome.ScreenSaver.SimulateUserActivity
int init_dbus(){
  dbus_error_init(&err);
  char **name_list;
  char **name_list_ptr;  
  g_type_init ();
  conn = dbus_g_bus_get (DBUS_BUS_SESSION,
                               &err);
  if (dbus_error_is_set(&err) || conn == 0) { 
    fprintf(stderr, "DBUS Connection Error (%s)\n", err->message); 
    dbus_error_free(&err);
    exit(1);
  }
}

int main() {
  init_dbus();
  init_camera();
#ifdef DEBUG 
  cvNamedWindow( "result", CV_WINDOW_AUTOSIZE );
#endif
  IplImage *frame = 0;
  while(1) {
  start_camera();
    int res = check_face(&frame);
    if( !frame ) {
      fprintf( stderr, "Unable to check face.\n" );
      return 1;
    }
#ifdef DEBUG       
    cvShowImage( "result", frame );
    cvWaitKey(100);
#endif
    printf("found %d faces\n", res);
  stop_camera();
  cvReleaseImage(&frame);

    if(res > 0) {
      system("qdbus org.gnome.ScreenSaver / org.gnome.ScreenSaver.SimulateUserActivity");
    }
    //    sleep(5);
  }
  dbus_connection_close(conn);
}
