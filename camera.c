#include <stdio.h>
#include "camera.h"

// Create memory for calculations
static CvMemStorage* storage = 0;
// Create a new Haar classifier
static CvHaarClassifierCascade* cascade = 0;
const char* cascade_name = "haarcascade_frontalface_default.xml";
CvCapture *capture = 0;

int init_camera() {
  // Load the HaarClassifierCascade
  cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
  if( !cascade ) {
    fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
    return 1;
  }
  // Allocate the memory storage
  storage = cvCreateMemStorage(0);
  cvClearMemStorage( storage );
 
}

int start_camera() {
 capture = cvCaptureFromCAM( 0 );
  if ( !capture ) {
    fprintf( stderr, "Cannot open initialize webcam!\n" );
    return 1;
  }
}

int stop_camera() {
  cvReleaseCapture( &capture );
}

int check_face(IplImage **img) {
  IplImage  *frame = 0;
  int face_count = 0;
  if(capture) {
    frame = cvQueryFrame( capture );  
    CvSeq* faces = cvHaarDetectObjects( frame, cascade, storage,
					1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
					cvSize(40, 40) );
    *img = frame;
    face_count = faces->total;
  }
  return face_count;
}
