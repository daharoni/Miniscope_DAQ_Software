# Miniscope DAQ Software

This software interfaces with a Miniscope and additional behavioral camera to stream and record video

## Getting Started

This software has been test on PCs running Windows 10. The ".exe" requires the additional download of a couple OpenCV 3.4.3 dll's to run. See below for how to download them.

### Prerequisites

You will need to download the OpenCV 2.4.13 .dlls and place them in the same folder containing "MiniScopeControl.exe". 

* You can download all of OpenCV here, https://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.13/opencv-2.4.13.6-vc14.exe/download.
* Find the required dll's in "opencv/build/x64/vc14/bin"
* You need:
  * opencv_core2413.dll
  * opencv_highgui2413.dll
  * opencv_imgproc2413.dll

