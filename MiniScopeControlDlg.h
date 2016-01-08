
// MiniScopeControlDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

//OpenCV Headers
#include "opencv2/calib3d.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
//#include "opencv2/flann.hpp"
#include "opencv2/hal.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/ml.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/photo.hpp"
#include "opencv2/shape.hpp"
#include "opencv2/stitching.hpp"
#include "opencv2/superres.hpp"
#include "opencv2/video.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/videostab.hpp"
#include "opencv2/world.hpp"

//OpenCV Headers
//#include "opencv2/core/core.hpp"
//#include "opencv2/flann/miniflann.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/photo/photo.hpp"
//#include "opencv2/video/video.hpp"
//#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/calib3d/calib3d.hpp"
//#include "opencv2/ml/ml.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/contrib/contrib.hpp"
//#include "opencv2/core/core_c.h"
//#include "opencv2/highgui/highgui_c.h"
//#include "opencv2/imgproc/imgproc_c.h"

//other headers

//Definitions
#define BUFFERLENGTH 256

// CMiniScopeControlDlg dialog
class CMiniScopeControlDlg : public CDialogEx
{
// Construction
public:
	CMiniScopeControlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MINISCOPECONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// For camera
	HWND hMyWindow;
	//--------
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CSliderCtrl mSliderExcitation;
	CSliderCtrl mSliderOpto;
	afx_msg void OnNMReleasedcaptureSliderexcitation(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSlideropto(NMHDR *pNMHDR, LRESULT *pResult);
	int mValueExcitation;
	int mValueOpto;
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnEnKillfocusEdit3();

	//Variables
	CListBox mInfoList;
	
	cv::VideoCapture msCam;
	cv::VideoCapture behavCam;
	cv::Mat msFrame[BUFFERLENGTH];
	cv::Mat behavFrame[BUFFERLENGTH];
	cv::Mat initialBehavFrame;
	UINT16 msReadPos;
	UINT16 msWritePos;
	UINT16 behavReadPos;
	UINT16 behavWritePos;
	UINT msCapFrameTime[BUFFERLENGTH];
	UINT behavCapFrameTime[BUFFERLENGTH];

	UINT_PTR mTimer;
	
	bool record;
	bool scopeCamConnected;
	bool behaviorCamConnected;
	int iLastX ; 
	int iLastY;
	LARGE_INTEGER startOfRecord, StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;
	CString TSFileName;
	CString settingsFIleName;
	CString folderLocation;
	CString currentTime;
	std::string msCamFileName;
	std::string behavCamFileName;
	
	int msCamMaxFrames;
	int behavCamMaxFrames;
	CStdioFile TSFile;
	CStdioFile settingsFile;
	unsigned long frameCount;
	bool behavGotROI;
	bool dragging;
	bool getScreenShot;
	cv::Rect behavROI;
	cv::Point pt1,pt2;

	
	//Functions
	void AddListText(CString);
	void UpdateLEDs(int, int);
	static void mouseClick(int event, int x, int y, int flags, void *param);
	BOOL PreTranslateMessage(MSG* pMsg);

	static UINT msCapture(LPVOID);
	static UINT behavCapture(LPVOID);
	static UINT camWrite(LPVOID);
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	int mScopeCamID;
	int mBehaviorCamID;
	afx_msg void OnBnClickedScopeconnect();
	afx_msg void OnBnClickedBehaviorconnect();
	afx_msg void OnBnClickedRecord();
	afx_msg void OnBnClickedStoprecord();
	CSliderCtrl mSliderScopeExposure;
	afx_msg void OnNMReleasedcaptureSliderscopeexposure(NMHDR *pNMHDR, LRESULT *pResult);
	int mScopeExposure;
	int mBehavExposure;
	LONGLONG mMSCurrentFPS;
	int mMsCapFrameCountGlobal;
	UINT mElapsedTime;
	int mBehavCapFrameCountGlobal;
	UINT mBehavCurrentFPS;
	CString mMouseName;
	afx_msg void OnEnKillfocusEdit12();
	UINT mMSCamWriteFPS;
	UINT mBehavCamWriteFPS;
	afx_msg void OnBnClickedSubmitnote();
	CString mNote;
	afx_msg void OnBnClickedResetroi();
	UINT mRecordLength;
	afx_msg void OnEnKillfocusEdit16();
	afx_msg void OnBnClickedCheck1();
	BOOL mMSColorCheck;
	afx_msg void OnNMReleasedcaptureSliderscopegain(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl mSliderScopeGain;
	int mScopeGain;
	BOOL mExcitationX10;
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	BOOL mScopeThreshold;
	int mSaturationThresh;
	afx_msg void OnEnKillfocusEdit18();
	BOOL mRed;
	BOOL mGreen;
	afx_msg void OnBnClickedRed();
	afx_msg void OnBnClickedGreen();
	
	CSliderCtrl mSliderBehavExposure;
	afx_msg void OnNMReleasedcaptureSliderbehavexposure2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBehavprop();
	afx_msg void OnBnClickedScreenshot();
	afx_msg void OnBnClickedChecktrigrec();
	BOOL mCheckTrigRec;
	int mMSDroppedFrames;
	CDialog dFrameDrop; //dialog box that pops up on frame drop
	double mMinFluor;
	double mMaxFluor;
	int mMinFluorDisplay;
	int mMaxFluorDisplay;
	afx_msg void OnEnKillfocusMinfluordisplay();
	afx_msg void OnEnKillfocusMaxfluordisplay();
};
