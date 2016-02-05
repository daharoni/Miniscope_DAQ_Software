
// MiniScopeControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MiniScopeControl.h"
#include "MiniScopeControlDlg.h"
#include "afxdialogex.h"
#include "definitions.h"
#include "resource.h"
#include <Windows.h>

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

//other headers
//

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


	CCriticalSection msCS;
	CCriticalSection behavCS;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMiniScopeControlDlg dialog



CMiniScopeControlDlg::CMiniScopeControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMiniScopeControlDlg::IDD, pParent)
	, mValueExcitation(0)
	, mValueOpto(0)
	, mScopeCamID(0)
	, mBehaviorCamID(0)
	, mScopeExposure(0)
	, mMSCurrentFPS(0)
	//, mMsCapFrameCount(0)
	, mElapsedTime(0)
	//, mBehavCapFrameCount(0)
	, mBehavCurrentFPS(0)
	, mMouseName(_T(""))
	, mMSCamWriteFPS(0)
	, mBehavCamWriteFPS(0)
	, mNote(_T(""))
	, mRecordLength(0)
	, mMSColorCheck(FALSE)
	, mScopeGain(0)
	, mExcitationX10(FALSE)
	, mScopeThreshold(FALSE)
	, mSaturationThresh(0)
	, mRed(FALSE)
	, mGreen(FALSE)
	, mBehavExposure(0)
	, mCheckTrigRec(FALSE)
	, mMSDroppedFrames(0)
	, mMinFluor(0)
	, mMaxFluor(0)
	, mMinFluorDisplay(0)
	, mMaxFluorDisplay(0)
	, mMSFPS(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMiniScopeControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mInfoList);
	DDX_Control(pDX, IDC_SLIDEREXCITATION, mSliderExcitation);
	DDX_Control(pDX, IDC_SLIDEROPTO, mSliderOpto);
	DDX_Text(pDX, IDC_EDIT2, mValueExcitation);
	DDX_Text(pDX, IDC_EDIT3, mValueOpto);
	DDX_Text(pDX, IDC_EDIT4, mScopeCamID);
	DDX_Text(pDX, IDC_EDIT5, mBehaviorCamID);
	DDX_Control(pDX, IDC_SLIDERSCOPEEXPOSURE, mSliderScopeExposure);
	DDX_Text(pDX, IDC_EDIT6, mScopeExposure);
	DDX_Text(pDX, IDC_EDIT7, mMSCurrentFPS);
	//DDX_Text(pDX, IDC_EDIT8, mMsCapFrameCount);
	DDX_Text(pDX, IDC_EDIT9, mElapsedTime);
	//DDX_Text(pDX, IDC_EDIT10, mBehavCapFrameCount);
	DDX_Text(pDX, IDC_EDIT11, mBehavCurrentFPS);
	DDX_Text(pDX, IDC_EDIT12, mMouseName);
	DDX_Text(pDX, IDC_EDIT13, mMSCamWriteFPS);
	DDX_Text(pDX, IDC_EDIT14, mBehavCamWriteFPS);
	DDX_Text(pDX, IDC_EDIT15, mNote);
	DDX_Text(pDX, IDC_EDIT16, mRecordLength);
	DDX_Check(pDX, IDC_CHECK1, mMSColorCheck);
	DDX_Control(pDX, IDC_SLIDERSCOPEGAIN, mSliderScopeGain);
	DDX_Text(pDX, IDC_EDIT17, mScopeGain);
	DDX_Check(pDX, IDC_CHECK2, mExcitationX10);
	//	DDX_Check(pDX, IDC_CHECK3, mScopeThreshold);
	DDX_Text(pDX, IDC_EDIT18, mSaturationThresh);
	DDX_Check(pDX, IDC_RED, mRed);
	DDX_Check(pDX, IDC_GREEN, mGreen);
	DDX_Text(pDX, IDC_EDIT19, mBehavExposure);
	//DDX_Control(pDX, IDC_SLIDERBEHAVEXPOSURE2, mSliderBehavExposure);
	DDX_Check(pDX, IDC_CHECKTRIGREC, mCheckTrigRec);
	DDX_Text(pDX, IDC_EDIT20, mMSDroppedFrames);
	DDX_Text(pDX, IDC_MINFLUOR, mMinFluor);
	DDX_Text(pDX, IDC_MAXFLUOR, mMaxFluor);
	DDX_Text(pDX, IDC_MINFLUORDISPLAY, mMinFluorDisplay);
	DDX_Text(pDX, IDC_MAXFLUORDISPLAY, mMaxFluorDisplay);
	DDX_CBIndex(pDX, IDC_COMBO1, mMSFPS);
	DDX_Control(pDX, IDC_COMBO1, mMSFPSCBox);
}

BEGIN_MESSAGE_MAP(CMiniScopeControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDEREXCITATION, &CMiniScopeControlDlg::OnNMReleasedcaptureSliderexcitation)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDEROPTO, &CMiniScopeControlDlg::OnNMReleasedcaptureSlideropto)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CMiniScopeControlDlg::OnEnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, &CMiniScopeControlDlg::OnEnKillfocusEdit3)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SCOPECONNECT, &CMiniScopeControlDlg::OnBnClickedScopeconnect)
	ON_BN_CLICKED(IDC_BEHAVIORCONNECT, &CMiniScopeControlDlg::OnBnClickedBehaviorconnect)
	ON_BN_CLICKED(IDC_RECORD, &CMiniScopeControlDlg::OnBnClickedRecord)
	ON_BN_CLICKED(IDC_STOPRECORD, &CMiniScopeControlDlg::OnBnClickedStoprecord)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERSCOPEEXPOSURE, &CMiniScopeControlDlg::OnNMReleasedcaptureSliderscopeexposure)
	ON_EN_KILLFOCUS(IDC_EDIT12, &CMiniScopeControlDlg::OnEnKillfocusEdit12)
	ON_BN_CLICKED(IDC_SUBMITNOTE, &CMiniScopeControlDlg::OnBnClickedSubmitnote)
	ON_BN_CLICKED(IDC_RESETROI, &CMiniScopeControlDlg::OnBnClickedResetroi)
	ON_EN_KILLFOCUS(IDC_EDIT16, &CMiniScopeControlDlg::OnEnKillfocusEdit16)
	ON_BN_CLICKED(IDC_CHECK1, &CMiniScopeControlDlg::OnBnClickedCheck1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERSCOPEGAIN, &CMiniScopeControlDlg::OnNMReleasedcaptureSliderscopegain)
	ON_BN_CLICKED(IDC_CHECK2, &CMiniScopeControlDlg::OnBnClickedCheck2)
//	ON_BN_CLICKED(IDC_CHECK3, &CMiniScopeControlDlg::OnBnClickedCheck3)
	ON_EN_KILLFOCUS(IDC_EDIT18, &CMiniScopeControlDlg::OnEnKillfocusEdit18)
	ON_BN_CLICKED(IDC_RED, &CMiniScopeControlDlg::OnBnClickedRed)
	ON_BN_CLICKED(IDC_GREEN, &CMiniScopeControlDlg::OnBnClickedGreen)
//	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERBEHAVEXPOSURE2, &CMiniScopeControlDlg::OnNMReleasedcaptureSliderbehavexposure2)
	ON_BN_CLICKED(IDC_BEHAVPROP, &CMiniScopeControlDlg::OnBnClickedBehavprop)
	ON_BN_CLICKED(IDC_SCREENSHOT, &CMiniScopeControlDlg::OnBnClickedScreenshot)
	ON_BN_CLICKED(IDC_CHECKTRIGREC, &CMiniScopeControlDlg::OnBnClickedChecktrigrec)
	ON_EN_KILLFOCUS(IDC_MINFLUORDISPLAY, &CMiniScopeControlDlg::OnEnKillfocusMinfluordisplay)
	ON_EN_KILLFOCUS(IDC_MAXFLUORDISPLAY, &CMiniScopeControlDlg::OnEnKillfocusMaxfluordisplay)
	ON_CBN_CLOSEUP(IDC_COMBO1, &CMiniScopeControlDlg::OnCbnCloseupCombo1)
END_MESSAGE_MAP()


// CMiniScopeControlDlg message handlers

BOOL CMiniScopeControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	dFrameDrop.Create(IDD_CAMDISCONNECTED,this);
	mSliderExcitation.SetRange(0,100,1);
	mScopeExposure = 100;
	mSliderExcitation.SetTicFreq(5); 
	mSliderOpto.SetRange(0,100,1);
	mSliderOpto.SetTicFreq(5);
	mValueExcitation = 0;
	mValueOpto = 0; 

	mMinFluor = 0;
	mMaxFluor = 255;
	mMinFluorDisplay = 0;
	mMaxFluorDisplay = 255;

	behavGotROI = false;
	dragging= false;
	mScopeCamID = 0;
	mBehaviorCamID = 1;
	mMouseName = "name";
	mNote = "";
	getScreenShot = false;
	UpdateData(FALSE);

	record = false;
	scopeCamConnected = false;
	behaviorCamConnected = false;
	mMSColorCheck = FALSE;
	mExcitationX10 = FALSE;

	msReadPos = 0;
	msWritePos = 0;
	behavReadPos = 0;
	behavWritePos = 0;

	mSaturationThresh = 255;
	mElapsedTime = 0;
	mRecordLength = 0;

	mMSCamWriteFPS = 0;
	mBehavCamWriteFPS = 0;
	mMSDroppedFrames = 0;
	mSliderScopeExposure.SetRange(1,255,1);
	mSliderScopeExposure.SetTicFreq(20);

	mSliderScopeGain.SetRange(16,64,1);
	mSliderScopeGain.SetTicFreq(2);

	mSliderBehavExposure.SetRange(0,100,1);
	mSliderBehavExposure.SetTicFreq(10);

	mMsCapFrameCountGlobal = 0;
	mBehavCapFrameCountGlobal = 0;

	mMSFPS = 1;
	//------------ Timer for cameras -----------
	QueryPerformanceFrequency(&Frequency); 
	QueryPerformanceCounter(&StartingTime);

	mTimer = SetTimer(1,100,NULL);
	//-----------------------------------
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CMiniScopeControlDlg::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        if ((pMsg->wParam == VK_RETURN) || (pMsg->wParam == VK_ESCAPE))
            pMsg->wParam = VK_TAB;
    }
    return CDialog::PreTranslateMessage(pMsg);
}

void CMiniScopeControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMiniScopeControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMiniScopeControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMiniScopeControlDlg::UpdateLEDs(int ledNum, int value) {
	//only written for 1 LED right now.
	CString str;
	BYTE address = SET_CURRENT;
	UINT16 outValue;
	if (mExcitationX10 == FALSE)
		outValue = ((UINT16)(value*(0x0FFF)/100))|(0x3000); //Full range
	else
		outValue = ((UINT16)(value*(0x0FFF)/1000))|(0x3000);//0 to 10 but 10 times resolution
	
	if (scopeCamConnected==true) { //Added by Daniel and commented out COMM communication below 4_9_2015
		msCam.set(CV_CAP_PROP_HUE,(outValue>>4)&0x00FF); //Added by Daniel and commented out COMM communication below 4_9_2015

		
			str.Format(L"LED power updated: %d", mValueExcitation);
			AddListText(str);
		if (record == TRUE) {
			str.Format(L"%u\tLED excitation intensity set to %d\n",mElapsedTime,mValueExcitation);
			settingsFile.WriteString(str);
		}
	}
	else {
		str.Format(L"MINIscope must be connected to change LED");
			AddListText(str);
	}

}


void  CMiniScopeControlDlg::AddListText(CString str)
{ //Used to add text to the Infor Box List
	int index = mInfoList.GetCount();
	mInfoList.InsertString( index, str );
	mInfoList.SetTopIndex(mInfoList.GetCount() - 1);
	//m_InfoList.EnsureVisible(index, FALSE);
}


void CMiniScopeControlDlg::OnNMReleasedcaptureSliderexcitation(NMHDR *pNMHDR, LRESULT *pResult)
{
	mValueExcitation = mSliderExcitation.GetPos();
	UpdateLEDs(0,mValueExcitation);
	UpdateData(FALSE);
	*pResult = 0;
}


void CMiniScopeControlDlg::OnNMReleasedcaptureSlideropto(NMHDR *pNMHDR, LRESULT *pResult)
{
	/*mValueOpto = mSliderOpto.GetPos();
	UpdateLEDs(1,mValueOpto);
	UpdateData(FALSE);*/
	*pResult = 0;
}


void CMiniScopeControlDlg::OnEnKillfocusEdit2()
{
	UpdateData(TRUE);
	mSliderExcitation.SetPos(mValueExcitation);
	UpdateLEDs(0,mValueExcitation);
	UpdateData(FALSE);
}


void CMiniScopeControlDlg::OnEnKillfocusEdit3()
{
	/*UpdateData(TRUE);
	mSliderOpto.SetPos(mValueOpto);
	UpdateLEDs(1,mValueOpto);
	UpdateData(FALSE);*/
}


void CMiniScopeControlDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	
	/*ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

	QueryPerformanceCounter(&StartingTime);

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	mMSCurrentFPS = (int)(1000000/ElapsedMicroseconds.QuadPart);*/

	if (record == true) {
		QueryPerformanceCounter(&EndingTime);
		mElapsedTime =(EndingTime.QuadPart -startOfRecord.QuadPart)/Frequency.QuadPart;
	}

	SetDlgItemInt(IDC_EDIT9,mElapsedTime);
	SetDlgItemInt(IDC_EDIT8,mMsCapFrameCountGlobal);
	SetDlgItemInt(IDC_EDIT10,mBehavCapFrameCountGlobal);
	SetDlgItemInt(IDC_EDIT7,mMSCurrentFPS);
	SetDlgItemInt(IDC_EDIT14,mMSDroppedFrames);
	SetDlgItemInt(IDC_EDIT11,mBehavCurrentFPS);
	SetDlgItemInt(IDC_EDIT13,mMSCamWriteFPS);
	SetDlgItemInt(IDC_EDIT14,mBehavCamWriteFPS);
	
	SetDlgItemInt(IDC_MINFLUOR,mMinFluor);
	SetDlgItemInt(IDC_MAXFLUOR,mMaxFluor);

	if ((msWritePos-msReadPos) >= BUFFERLENGTH) {
		AddListText(L"Scope cam buffer error!");				
	}
	if ((behavWritePos-behavReadPos) >= BUFFERLENGTH) {
		AddListText(L"Behavior cam buffer error!");				
	}
	if (mRecordLength <= mElapsedTime && mRecordLength != 0) {
		OnBnClickedStoprecord();
	}

	//SetDlgItem(IDC_EDIT7,mMSCurrentFPS);
	
	//UpdateData(FALSE);

	CDialogEx::OnTimer(nIDEvent);
}


void CMiniScopeControlDlg::OnClose()
{
	KillTimer(mTimer);
	CDialogEx::OnClose();
}


void CMiniScopeControlDlg::OnBnClickedScopeconnect()
{
	UpdateData(TRUE);
	CString str;
	if (behaviorCamConnected == false) 
		GetDlgItem(IDC_RECORD)->EnableWindow(TRUE);

	cv::namedWindow("msCam",CV_WINDOW_NORMAL);// CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO
	cv::moveWindow("msCam", 1100,1);
	//cv::resizeWindow("msCam",752,480);
	//cv::resizeWindow("msCam",1280,1024);
	msCam.open(mScopeCamID);
	
	//msCam.set(CV_CAP_PROP_CONVERT_RGB,FALSE); //Added to fix messed up top 8 bit of pixel stream

	//str.Format(L"Mat Channel: %d", msFrame[0].channels());
	//		AddListText(str);
	GetDlgItem(IDC_SCREENSHOT)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);

	GetDlgItem(IDC_SLIDERSCOPEEXPOSURE)->EnableWindow(TRUE);
	GetDlgItem(IDC_SLIDERSCOPEGAIN)->EnableWindow(TRUE);
	//mScopeExposure = msCam.get(CV_CAP_PROP_BRIGHTNESS);
	//mSliderScopeExposure.SetPos(mScopeExposure);
	UpdateData(FALSE);
	
	/*GetDlgItem(IDC_SLIDERSCOPEEXPOSURE)->EnableWindow(TRUE);
	mScopeExposure = msCam.get(CV_CAP_PROP_EXPOSURE);
	mSliderScopeExposure.SetPos(mScopeExposure/255*100);*/
	
	msCam.set(CV_CAP_PROP_SATURATION, SET_CMOS_SETTINGS); //Initiallizes CMOS sensor (FPS, gain and exposure enabled...)

	mScopeExposure = 255;
	mSliderScopeExposure.SetPos(mScopeExposure);
	msCam.set(CV_CAP_PROP_BRIGHTNESS,mScopeExposure);

	mScopeGain = 16;
	mSliderScopeGain.SetPos(mScopeGain);
	msCam.set(CV_CAP_PROP_GAIN,mScopeGain);

	

	UpdateData(FALSE);
	scopeCamConnected = true;

	mValueExcitation = 0;
	mSliderExcitation.SetPos(mValueExcitation);
	UpdateLEDs(0,0);

	AfxBeginThread(msCapture,(LPVOID)this);
}


void CMiniScopeControlDlg::OnBnClickedBehaviorconnect()
{
	
	UpdateData(TRUE);
	GetDlgItem(IDC_RECORD)->EnableWindow(FALSE);
	cv::namedWindow("behavCam");
	cv::moveWindow("behavCam", 1000,400);
	behavCam.open(mBehaviorCamID);
	
	GetDlgItem(IDC_SLIDERBEHAVEXPOSURE)->EnableWindow(TRUE);
	mBehavExposure = behavCam.get(CV_CAP_PROP_BRIGHTNESS);
	mSliderBehavExposure.SetPos(mBehavExposure);

	//behavCam.set(CV_CAP_PROP_FRAME_WIDTH,424);
	//behavCam.set(CV_CAP_PROP_FRAME_HEIGHT,240);

	behavCam.set(CV_CAP_PROP_GAIN,behavCam.get(CV_CAP_PROP_GAIN));
	behavCam.set(CV_CAP_PROP_CONTRAST,behavCam.get(CV_CAP_PROP_CONTRAST));
	behavCam.set(CV_CAP_PROP_SATURATION,behavCam.get(CV_CAP_PROP_SATURATION));
	behavCam.set(CV_CAP_PROP_EXPOSURE,behavCam.get(CV_CAP_PROP_EXPOSURE));

	
	//behavCam.set(CV_CAP_PROP_SETTINGS,1);

	UpdateData(FALSE);
	GetDlgItem(IDC_BEHAVPROP)->EnableWindow(TRUE);
	behavCam.grab();
	behavCam.retrieve(behavFrame[behavWritePos%BUFFERLENGTH]);
	//cv::imshow("behavCam", initialBehavFrame);
	cv::setMouseCallback("behavCam",mouseClick,this);
	AddListText(L"Select Behavior Cam ROI");

	//while(!behavGotROI) {}

	behaviorCamConnected = true;
	AfxBeginThread(behavCapture,(LPVOID)this);
}
void CMiniScopeControlDlg::mouseClick(int event, int x, int y, int flags, void *param)
{
	CMiniScopeControlDlg* self = (CMiniScopeControlDlg*)param;
	if (!self->behavGotROI) {
		switch(event)
		{
			case CV_EVENT_LBUTTONDOWN:
			{
				self->pt1.x = x;
				self->pt1.y = y;
				self->dragging=true;
				break;
			}
			case CV_EVENT_MOUSEMOVE:
			{
				self->pt2 = cv::Point(x, y);
				/* mouse dragged. ROI being selected */
				break;
			}
			case CV_EVENT_LBUTTONUP:
			{
				self->pt2.x = x;
				self->pt2.y = y;
				self->behavROI = cv::Rect(self->pt1,self->pt2);
				self->behavGotROI = true;
				self->dragging=false;
				self->AddListText(L"ROI Set");
				self->GetDlgItem(IDC_RECORD)->EnableWindow(TRUE);
				self->GetDlgItem(IDC_RESETROI)->EnableWindow(TRUE);
				break;  
			}
		}
	}
}


void CMiniScopeControlDlg::OnBnClickedRecord()
{
	CString str;
	CTime time = CTime::GetCurrentTime();
	std::string tempString;

	UpdateData(TRUE);

	CreateDirectory(L"data",NULL);
	str.Format(L"data\\%u_%u_%u",time.GetMonth(),time.GetDay(),time.GetYear());
	CreateDirectory(str,NULL);
	str.Format(L"data\\%u_%u_%u\\H%u_M%u_S%u",time.GetMonth(),time.GetDay(),time.GetYear(),time.GetHour(),time.GetMinute(),time.GetSecond());
	CreateDirectory(str,NULL);
	TSFileName.Format(L"data\\%u_%u_%u\\H%u_M%u_S%u\\%s",time.GetMonth(),time.GetDay(),time.GetYear(),time.GetHour(),time.GetMinute(),time.GetSecond(), L"timestamp.dat");
	settingsFIleName.Format(L"data\\%u_%u_%u\\H%u_M%u_S%u\\%s",time.GetMonth(),time.GetDay(),time.GetYear(),time.GetHour(),time.GetMinute(),time.GetSecond(), L"settings_and_notes.dat");

	str.Format(L"Files created in %s", str);
	AddListText(str);

	std::ostringstream os, os2;
	os << "data\\" << time.GetMonth() << "_"  << time.GetDay() << "_"  << time.GetYear() << "\\H"  << time.GetHour() << "_M"  << time.GetMinute() << "_S" << time.GetSecond() << "\\msCam";
	msCamFileName = os.str();
	os2  << "data\\" << time.GetMonth() << "_" << time.GetDay() << "_" << time.GetYear() << "\\H" << time.GetHour() << "_M" << time.GetMinute() << "_S" << time.GetSecond() << "\\behavCam";
	behavCamFileName = os2.str();
	
	


	TSFile.Open(TSFileName, CFile::modeCreate|CFile::modeWrite, NULL);
	str.Format(L"camNum\tframeNum\tsysClock\tbuffer\n");
	TSFile.WriteString(str);

	settingsFile.Open(settingsFIleName, CFile::modeCreate|CFile::modeWrite, NULL);
	str.Format(L"animal\texcitation\tmsCamExposure\trecordLength\n");
	settingsFile.WriteString(str);
	str.Format(L"%s\t%i\t%i\t%i\n\nelapsedTime\tNote\n",mMouseName,mValueExcitation,mScopeExposure,mRecordLength);
	settingsFile.WriteString(str);
	

	msCamMaxFrames = 1000;
	behavCamMaxFrames = 1000;
	
	QueryPerformanceCounter(&startOfRecord);
	GetDlgItem(IDC_RECORD)->EnableWindow(FALSE);
	if (mCheckTrigRec==false)
		GetDlgItem(IDC_STOPRECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_SUBMITNOTE)->EnableWindow(TRUE);
	GetDlgItem(IDC_RESETROI)->EnableWindow(FALSE);
	record = true;
	msReadPos = msWritePos;
	behavReadPos = behavWritePos;

	msCam.set(CV_CAP_PROP_SATURATION,RECORD_START); //Added by Daniel and start Frame Capture Trigger 6_22_2015
	AfxBeginThread(camWrite,(LPVOID)this,THREAD_PRIORITY_HIGHEST);
}


void CMiniScopeControlDlg::OnBnClickedStoprecord()
{
	msCam.set(CV_CAP_PROP_SATURATION,RECORD_END); //Added by Daniel and start Frame Capture Trigger 6_22_2015
	record = false;
}


void CMiniScopeControlDlg::OnNMReleasedcaptureSliderscopeexposure(NMHDR *pNMHDR, LRESULT *pResult)
{
	mScopeExposure = mSliderScopeExposure.GetPos();
	msCam.set(CV_CAP_PROP_BRIGHTNESS,mScopeExposure);
	UpdateData(FALSE);
	*pResult = 0;
}

UINT CMiniScopeControlDlg::msCapture(LPVOID pParam )
{
	CMiniScopeControlDlg* self = (CMiniScopeControlDlg*)pParam;
	CSingleLock msSingleLock(&msCS);

	LARGE_INTEGER previousTime;
	LARGE_INTEGER currentTime;
	currentTime = self->startOfRecord;

	cv::Mat frame; //moved from inside else loop by Daniel 3_27_2015

	// Added by Daniel 6_22_2015 to try and stop software from crashing on camera disconnect
	bool status;
	//----------------------------
	CString str;
	CString str2;
	std::string tempString;

	std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(0);
	cv::Mat droppedFrameImage = cv::imread("droppedFrameImage.bmp", CV_LOAD_IMAGE_COLOR);
	unsigned char temp;

	//cv::Mat trash;
	//self->msCam.read(trash);

	while(1) {	
		//Added for triggerable recording
		if (self->mCheckTrigRec == true) {
			temp = self->msCam.get(CV_CAP_PROP_SATURATION);
			//str.Format(L"GPIO State: %u",temp);
			//self->AddListText(str);
			if ((temp & TRIG_RECORD_EXT) == TRIG_RECORD_EXT) {
				if (self->record == false)
					self->UpdateLEDs(0,self->mValueExcitation);
					self->OnBnClickedRecord();//Start recording
			}
			else {
				if(self->record == true)
					self->UpdateLEDs(0,0);
					self->OnBnClickedStoprecord();
			}
		}
		//-------------------------------
		status = self->msCam.grab();
		if (status == false) {
			self->record = false;
			self->AddListText(L"msCam frame grab error! Recording ended.");
			break;
		}
		previousTime = currentTime;
		QueryPerformanceCounter(&currentTime);
		self->mMSCurrentFPS = 1/(((double)currentTime.QuadPart - previousTime.QuadPart)/self->Frequency.QuadPart);
		
		self->msCapFrameTime[self->msWritePos%BUFFERLENGTH] = 1000*((double)currentTime.QuadPart - self->startOfRecord.QuadPart)/self->Frequency.QuadPart;
		
		status = self->msCam.retrieve(self->msFrame[self->msWritePos%BUFFERLENGTH]);
		if (status == false) {
			self->record = false; //Commented out to not end recording Daniel 11_10_2015
			self->mMSDroppedFrames++; //Added frame drop tracker Daniel 11_10_2015
			self->AddListText(L"msCam frame retrieve error! Recording ended.");
			//self->dFrameDrop.ShowWindow(SW_SHOW);//popup dialog box Daniel 11_10_2015
			cv::imshow("msCam",droppedFrameImage);
			break; //removed break Daniel 11_10_2015
		}
		else {//Added else Daniel 11_10_2015
			if (self->getScreenShot == true) {
			
				CT2CA pszConvertedAnsiString = self->folderLocation + "\\" + self->mMouseName + "_" + self->mNote + "_" + self->currentTime + ".png";
				tempString = pszConvertedAnsiString;
				cv::imwrite(tempString,self->msFrame[self->msWritePos%BUFFERLENGTH],compression_params);
				self->getScreenShot = false;
				str.Format(L"Image saved in %s",self->folderLocation);
				self->AddListText(str);
				self->mNote = "";
				self->UpdateData(FALSE);
			}
			//cv::cvtColor(self->msFrame[self->msWritePos%BUFFERLENGTH],frame,CV_YUV2GRAY_YUYV);//added to correct green color stream

			if (self->mMSColorCheck == FALSE) {
				cv::cvtColor(self->msFrame[self->msWritePos%BUFFERLENGTH],frame,CV_BGR2GRAY);//added to correct green color stream

				cv::minMaxLoc(frame,&self->mMinFluor,&self->mMaxFluor);
				frame.convertTo(frame, CV_8U, 255.0/(self->mMaxFluorDisplay - self->mMinFluorDisplay), -self->mMinFluorDisplay * 255.0/(self->mMaxFluorDisplay - self->mMinFluorDisplay));

				if (self->record == true)
					//cv::imshow("msCam", self->msFrame[self->msWritePos%BUFFERLENGTH]);
					cv::imshow("msCam",frame);//added to correct green color stream
				else {
					cv::Mat dst;
					//cv::threshold(self->msFrame[self->msWritePos%BUFFERLENGTH],dst,self->mSaturationThresh,0,4);
					//cv::threshold(frame,dst,self->mSaturationThresh,0,4);//added to correct green color stream
					//cv::imshow("msCam", dst);
					cv::imshow("msCam",frame);

				}
			}
			else { 
				//cv::Mat frame;
			
				//cv::Mat channel[3];
				cv::cvtColor(self->msFrame[self->msWritePos%BUFFERLENGTH],frame,CV_BGR2GRAY);
				//cv::cvtColor(self->msFrame[self->msWritePos%BUFFERLENGTH],frame,CV_YUV2GRAY_YUY2);//added to correct green color stream
				cv::cvtColor(frame,frame,CV_BayerRG2BGR);
				if (self->mRed == TRUE || self->mGreen == TRUE) {
					cv::Mat bgrChannels[3];
					cv::split(frame,bgrChannels);
					bgrChannels[0] = cv::Mat::zeros(frame.rows,frame.cols,CV_8UC1);
					if (self->mRed == FALSE) 
						bgrChannels[2] = cv::Mat::zeros(frame.rows,frame.cols,CV_8UC1);
					if (self->mGreen == FALSE)
						bgrChannels[1] = cv::Mat::zeros(frame.rows,frame.cols,CV_8UC1);
					cv::merge(bgrChannels,3,frame);
				}

			
				cv::imshow("msCam", frame);
			}
	
			if (self->record == true) {
				msSingleLock.Lock();  // Attempt to lock the shared resource
				if (msSingleLock.IsLocked()) { // Resource has been locked
					self->msWritePos++;
					msSingleLock.Unlock();
				}
			}
		}
	}
	return 0;
}
UINT CMiniScopeControlDlg::behavCapture(LPVOID pParam )
{
	CMiniScopeControlDlg* self = (CMiniScopeControlDlg*)pParam;
	CSingleLock behavSingleLock(&behavCS);

	LARGE_INTEGER previousTime;
	LARGE_INTEGER currentTime;
	currentTime = self->startOfRecord;;
	while(1) {
		self->behavCam.grab();
		previousTime = currentTime;
		QueryPerformanceCounter(&currentTime);
		self->mBehavCurrentFPS = 1/(((double)currentTime.QuadPart - previousTime.QuadPart)/self->Frequency.QuadPart);

		self->behavCapFrameTime[self->behavWritePos%BUFFERLENGTH] = 1000*((double)currentTime.QuadPart - self->startOfRecord.QuadPart)/self->Frequency.QuadPart;
		self->behavCam.retrieve(self->behavFrame[self->behavWritePos%BUFFERLENGTH]);
		
		if (self->dragging == true) {
			rectangle(self->behavFrame[self->behavWritePos%BUFFERLENGTH], self->pt1, self->pt2, CV_RGB(255, 0, 0), 3, 8, 0);
		}

		if (self->behavGotROI)
			cv::imshow("behavCam", self->behavFrame[self->behavWritePos%BUFFERLENGTH](self->behavROI));
		else
			cv::imshow("behavCam", self->behavFrame[self->behavWritePos%BUFFERLENGTH]);

		if (self->record == true) {
			behavSingleLock.Lock();  // Attempt to lock the shared resource
			if (behavSingleLock.IsLocked()) { // Resource has been locked
				self->behavWritePos++;
				behavSingleLock.Unlock();
			}
		}
		
	}
	return 0;
}
UINT CMiniScopeControlDlg::camWrite(LPVOID pParam )
{

	cv::VideoWriter msOutVid;
	cv::VideoWriter behavOutVid;

	CMiniScopeControlDlg* self = (CMiniScopeControlDlg*)pParam;
	CSingleLock msSingleLock(&msCS);
	CSingleLock behavSingleLock(&behavCS);

	CString str;
	std::string tempString;

	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;

	int msCamFileNumber = 1;
	int behavCamFileNumber = 1;
	int mMsCapFrameCount = 0;
	int mBehavCapFrameCount = 0;

	if (self->scopeCamConnected == true) {
		tempString = self->msCamFileName + std::to_string(msCamFileNumber) + ".avi";
		msOutVid.open(tempString,CV_FOURCC('D', 'I', 'B', ' '),20,cv::Size(self->msCam.get(CV_CAP_PROP_FRAME_WIDTH),self->msCam.get(CV_CAP_PROP_FRAME_HEIGHT)),false);
	}
	if (self->behaviorCamConnected == true) {
		tempString = self->behavCamFileName + std::to_string(msCamFileNumber) + ".avi";;
		behavOutVid.open(tempString,CV_FOURCC('D', 'I', 'B', ' '),20,cv::Size(self->behavROI.width,self->behavROI.height),true);
	}

	while(1) {
		msSingleLock.Lock();  // Attempt to lock the shared resource
		if (msSingleLock.IsLocked()) { // Resource has been locked
			if (self->msReadPos != self->msWritePos) { //use to be an if statement
				QueryPerformanceCounter(&startTime);
				mMsCapFrameCount++;
				self->mMsCapFrameCountGlobal = mMsCapFrameCount;

				msOutVid.write(self->msFrame[self->msReadPos%BUFFERLENGTH]);
			
				str.Format(L"%u\t%u\t%li\t%u\n", self->mScopeCamID, mMsCapFrameCount, self->msCapFrameTime[self->msReadPos%BUFFERLENGTH],self->msWritePos-self->msReadPos);
				self->TSFile.WriteString(str);

				if (mMsCapFrameCount%self->msCamMaxFrames == 0) {
					msOutVid.release();
					msCamFileNumber++;
					tempString = self->msCamFileName + std::to_string(msCamFileNumber) + ".avi";
					msOutVid.open(tempString,CV_FOURCC('D', 'I', 'B', ' '),20,cv::Size(self->msCam.get(CV_CAP_PROP_FRAME_WIDTH),self->msCam.get(CV_CAP_PROP_FRAME_HEIGHT)),false);
				}
				self->msReadPos++;
				QueryPerformanceCounter(&endTime);
				self->mMSCamWriteFPS = 1/(((double)endTime.QuadPart - startTime.QuadPart)/self->Frequency.QuadPart);
			
			}
			msSingleLock.Unlock();
		}
		behavSingleLock.Lock();  // Attempt to lock the shared resource
		if (behavSingleLock.IsLocked()) { // Resource has been locked
			if (self->behavReadPos != self->behavWritePos) { //use to be an if statement
				QueryPerformanceCounter(&startTime);
				mBehavCapFrameCount++;
				self->mBehavCapFrameCountGlobal = mBehavCapFrameCount;

				behavOutVid.write(self->behavFrame[self->behavReadPos%BUFFERLENGTH](self->behavROI));

				str.Format(L"%u\t%u\t%li\t%u\n", self->mBehaviorCamID, mBehavCapFrameCount, self->behavCapFrameTime[self->behavReadPos%BUFFERLENGTH],self->behavWritePos-self->behavReadPos);
				self->TSFile.WriteString(str); 

				if (mBehavCapFrameCount%self->behavCamMaxFrames == 0) {
					behavOutVid.release();
					behavCamFileNumber++;
					tempString = self->behavCamFileName + std::to_string(behavCamFileNumber) + ".avi";
					behavOutVid.open(tempString,CV_FOURCC('D', 'I', 'B', ' '),20,cv::Size(self->behavROI.width,self->behavROI.height),true);
				}

				self->behavReadPos++;
				QueryPerformanceCounter(&endTime);
				self->mBehavCamWriteFPS = 1/(((double)endTime.QuadPart - startTime.QuadPart)/self->Frequency.QuadPart);

			}
			behavSingleLock.Unlock();
		}
		if (self->record == false && self->behavReadPos == self->behavWritePos && self->msReadPos == self->msWritePos) {
			msOutVid.release();
			behavOutVid.release();
			self->TSFile.Close();
			self->settingsFile.Close();
			mMsCapFrameCount = 0;
			mBehavCapFrameCount = 0;
			self->mElapsedTime = 0;
			self->GetDlgItem(IDC_RECORD)->EnableWindow(TRUE);
			self->GetDlgItem(IDC_STOPRECORD)->EnableWindow(FALSE);
			self->GetDlgItem(IDC_SUBMITNOTE)->EnableWindow(FALSE);
			if (self->behavGotROI)
				self->GetDlgItem(IDC_RESETROI)->EnableWindow(TRUE);
			break;
		}
	}

	self->AddListText(L"Recording Files Closed");
	return 0;
}

void CMiniScopeControlDlg::OnEnKillfocusEdit12()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}


void CMiniScopeControlDlg::OnBnClickedSubmitnote()
{
	// TODO: Add your control notification handler code here
	CString str;
	UpdateData(TRUE);
	str.Format(L"%u\t",mElapsedTime);
	settingsFile.WriteString(str);
	settingsFile.WriteString(mNote);
	settingsFile.WriteString(L"\n");
	mNote = "";
	UpdateData(FALSE);


}


void CMiniScopeControlDlg::OnBnClickedResetroi()
{
	// TODO: Add your control notification handler code here
	behavGotROI = false;
	GetDlgItem(IDC_RESETROI)->EnableWindow(FALSE);
	GetDlgItem(IDC_RECORD)->EnableWindow(FALSE);
}


void CMiniScopeControlDlg::OnEnKillfocusEdit16()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}


void CMiniScopeControlDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (mMSColorCheck == TRUE) {
		GetDlgItem(IDC_RED)->EnableWindow(TRUE);
		GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_RED)->EnableWindow(FALSE);
		GetDlgItem(IDC_GREEN)->EnableWindow(FALSE);
	}

}


void CMiniScopeControlDlg::OnNMReleasedcaptureSliderscopegain(NMHDR *pNMHDR, LRESULT *pResult)
{
	mScopeGain = mSliderScopeGain.GetPos();
	if (mScopeGain>=32 && (mScopeGain%2)==1)
		mScopeGain++; //Gains between 32 and 64 must be even for MT9V032
	msCam.set(CV_CAP_PROP_GAIN,mScopeGain);
	UpdateData(FALSE);
	*pResult = 0;
}


void CMiniScopeControlDlg::OnBnClickedCheck2()
{
	UpdateData(TRUE);
	UpdateLEDs(0,mValueExcitation);
}





void CMiniScopeControlDlg::OnEnKillfocusEdit18()
{
	UpdateData(TRUE);
}


void CMiniScopeControlDlg::OnBnClickedRed()
{
	UpdateData(TRUE);
}


void CMiniScopeControlDlg::OnBnClickedGreen()
{
	UpdateData(TRUE);
}


void CMiniScopeControlDlg::OnNMReleasedcaptureSliderbehavexposure2(NMHDR *pNMHDR, LRESULT *pResult)
{
	mBehavExposure = mSliderBehavExposure.GetPos();
	behavCam.set(CV_CAP_PROP_BRIGHTNESS,mBehavExposure);
	UpdateData(FALSE);
	*pResult = 0;
}


void CMiniScopeControlDlg::OnBnClickedBehavprop()
{
	behavCam.set(CV_CAP_PROP_SETTINGS,1);
}


void CMiniScopeControlDlg::OnBnClickedScreenshot()
{

	CTime time = CTime::GetCurrentTime();

	UpdateData(TRUE);

	CreateDirectory(L"data",NULL);
	folderLocation.Format(L"data\\%u_%u_%u",time.GetMonth(),time.GetDay(),time.GetYear());
	CreateDirectory(folderLocation,NULL);

	currentTime.Format(L"H%u_M%u_S%u",time.GetHour(),time.GetMinute(),time.GetSecond());
	
	getScreenShot = true;
}


void CMiniScopeControlDlg::OnBnClickedChecktrigrec()
{

		

	UpdateData(TRUE);
	if (mCheckTrigRec == TRUE) {
		GetDlgItem(IDC_STOPRECORD)->EnableWindow(FALSE);
		GetDlgItem(IDC_RECORD)->EnableWindow(FALSE);
		UpdateLEDs(0,0);
	}
	else
	{
		GetDlgItem(IDC_STOPRECORD)->EnableWindow(TRUE);
		if (record == false)
			GetDlgItem(IDC_RECORD)->EnableWindow(TRUE);
		UpdateLEDs(0,mValueExcitation);
	}
}

void CMiniScopeControlDlg::OnEnKillfocusMinfluordisplay()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}


void CMiniScopeControlDlg::OnEnKillfocusMaxfluordisplay()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}


void CMiniScopeControlDlg::OnCbnCloseupCombo1()
{
	UpdateData(TRUE);
	CString str,str2;
	mMSFPSCBox.GetLBText(mMSFPSCBox.GetCurSel(),str2);
	int cBoxVal = _ttoi(str2);
	switch(cBoxVal) 
	{
		case (5):
			msCam.set(CV_CAP_PROP_SATURATION, FPS5);
			break;
		case (10):
			msCam.set(CV_CAP_PROP_SATURATION, FPS10);
			break;
		case (15):
			msCam.set(CV_CAP_PROP_SATURATION, FPS15);
			break;
		case (20):
			msCam.set(CV_CAP_PROP_SATURATION, FPS20);
			break;
		case (30):
			msCam.set(CV_CAP_PROP_SATURATION, FPS30);
			break;
		case (60):
			msCam.set(CV_CAP_PROP_SATURATION, FPS60);
			break;
		default:
			break;
	}
	str.Format(L"Scope FPS updated: %d", cBoxVal);
			AddListText(str);

}
