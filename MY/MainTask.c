/*   
		  扬州大学 测控15 杨寿晨          
		
				显示程序        

			2019/4 - 2019/6                         */

						
#include  "MainTask.h"
#include  <includes.h>
#pragma		diag_suppress 870		// 屏蔽warning 870

WM_HWIN		hDlg  = 0; 				// 主信息对话框句柄
WM_HWIN		hWin1 = 0; 				// 设置对话框句柄
WM_HWIN		hWin2 = 0;				// 关于对话框句柄 
WM_HWIN		hWin_wave1 = 0; 		// 波形显示1对话框句柄
WM_HWIN		hWin_wave2 = 0; 		// 波形显示2对话框句柄
WM_HWIN		hWin_VPP = 0; 			// 峰峰值数值显示对话框句柄
WM_HWIN		hWin_option_page1 = 0;
WM_HWIN		hWin_option_page2 = 0;
WM_HWIN		hWin_option_page3 = 0;
WM_HWIN		hWin_option_page4 = 0;
WM_HWIN		hWin_option_page5 = 0;

GRAPH_DATA_Handle	_GRAPH_DATA1;
GRAPH_DATA_Handle	_GRAPH_DATA2;
GRAPH_SCALE_Handle	_hScaleV;

uint8_t		CH_select=0;			// 通道显示选择标志位


/*********************************************************************
*
*       	对话框资源表
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate [] 				= {
	{ WINDOW_CreateIndirect,	"Window",	ID_WINDOW_0,	0,		0,		170,	480,	0,  0x0, 0 },
	{ TEXT_CreateIndirect,		"Text",		ID_TEXT_0,		15,		95,		160,	20,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		"Text",		ID_TEXT_1,		105,	100,	160,	20,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		"Text",		ID_TEXT_2,		35,		130,	160,	20,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		"Text",		ID_TEXT_3,		35,		150,	160,	20,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		"地理位置:",ID_TEXT_4,		15,		165,	160,	50,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		"Text",		ID_TEXT_5,		80,		210,	160,	20,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		"Text",     ID_TEXT_6,		80,		230,	160,	20,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		"转速:",	ID_TEXT_7,		15,		260,	160,	20,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		"转速:",	ID_TEXT_8,		15,		285,	160,	20,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		"设置",		ID_TEXT_9,		32,		452,	50,		20,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		"关于",		ID_TEXT_10,		110,	452,	50,		20,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		"通道切换",	ID_TEXT_11,		95,		340,	100,	20,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		"经度",		ID_TEXT_12,		35,		210,	50,		20,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		"纬度",		ID_TEXT_13,		35,		230,	50,		20,		0, 0x64, 0 },
	{ BUTTON_CreateIndirect,    "",			ID_BUTTON_0,	25,		320,	60,		60,		0,  0x0, 0 },
	{ BUTTON_CreateIndirect,	"",			ID_BUTTON_1,	25,		400,	50,		50,		0,  0x0, 0 },
	{ BUTTON_CreateIndirect,    "",			ID_BUTTON_2,   100,		400,	50,		50,		0,  0x0, 0 },
	{ IMAGE_CreateIndirect,		"",			ID_IMAGE_0,		45,		5,		79,		79,	0,	},
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_option[]			= {
	{ FRAMEWIN_CreateIndirect,			0,			ID_FRAMEWIN_0,		250,	30,		500,	400,	0 },
	{ MULTIPAGE_CreateIndirect, "Multipage", 		ID_MULTIPAGE_0,		0,		0,		500,	400 },
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_option_page1[]	= {
	{ WINDOW_CreateIndirect,    "1",		ID_WINDOW_option_page1,		0,		0,		500,	400,	0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page1_0,		50,		40,		120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page1_1,		50,		100,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page1_2,		250,	100,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page1_3,		50,		140,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page1_4,		250,	140,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page1_5,		50,		180,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page1_6,		250,	180,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page1_7,		50,		220,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page1_8,		250,	220,	160,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page1_9,		50,		260,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page1_10,	250,	260,	120,	30,		0, 0x64, 0 },
	{ BUTTON_CreateIndirect,    0,			ID_BUTTON_option_page1_0,	250,	30,		110,	40,		0,  0x0, 0 },
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_option_page2[]	= {
	{ WINDOW_CreateIndirect,    "2",		ID_WINDOW_option_page2,		0,		0,		500,	400,	0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page2_0,		50,		40,		120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page2_1,		50,		100,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page2_2,		250,	100,	250,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page2_3,		50,		160,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page2_4,		250,	160,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page2_5,		50,		220,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page2_6,		250,	220,	120,	30,		0, 0x64, 0 },
	{ BUTTON_CreateIndirect,    0,			ID_BUTTON_option_page2_0,	250,	30,		110,	40,		0,  0x0, 0 },
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_option_page3[]	= {
	{ WINDOW_CreateIndirect,    "3",		ID_WINDOW_option_page3,		0,		0,		500,	400,	0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page3_0,		50,		40,		120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page3_1,		50,		100,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page3_2,		250,	100,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page3_3,		50,		140,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page3_4,		250,	140,	200,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page3_5,		50,		180,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page3_6,		250,	180,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page3_7,		50,		220,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page3_8,		250,	220,	120,	30,		0, 0x64, 0 },
	{ BUTTON_CreateIndirect,    0,			ID_BUTTON_option_page3_0,	250,	30,		110,	40,		0,  0x0, 0 },
	{ BUTTON_CreateIndirect,    0,			ID_BUTTON_option_page3_1,	120,	260,	96,		46,		0,  0x0, 0 },
	{ BUTTON_CreateIndirect,    0,			ID_BUTTON_option_page3_2,	320,	260,	96,		46,		0,  0x0, 0 },
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_option_page4[]	= {
	{ WINDOW_CreateIndirect,    "4",		ID_WINDOW_option_page4,		0,		0,		500,	400,	0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page4_0,		50,		40,		120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page4_1,		50,		100,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page4_2,		250,	100,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page4_3,		50,		140,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page4_4,		250,	140,	120,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page4_5,		50,		180,	120,	30,		0, 0x64, 0 },
	{ BUTTON_CreateIndirect,	0,			ID_BUTTON_option_page4_0,	250,	30,		110,	40,		0,  0x0, 0 },
	{ CHECKBOX_CreateIndirect,    0,		ID_CHECKBOX_option_page4_0,	230,	190,	120,	0,		},
	{ CHECKBOX_CreateIndirect,    0,		ID_CHECKBOX_option_page4_1,	360,	190,	120,	0,		},
	{ CHECKBOX_CreateIndirect,    0,		ID_CHECKBOX_option_page4_2,	230,	260,	120,	0,		},
	{ CHECKBOX_CreateIndirect,    0,		ID_CHECKBOX_option_page4_3,	360,	260,	150,	0,		},
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_option_page5[]	= {
	{ WINDOW_CreateIndirect,    "5",		ID_WINDOW_option_page5,		0,		0,		500,	400,	0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page5_0,		20,		20,		150,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page5_1,		20,		100,	100,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page5_2,		20,		230,	100,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page5_3,		20,		130,	100,	30,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,			ID_TEXT_option_page5_4,		20,		260,	100,	30,		0, 0x64, 0 },
	{ BUTTON_CreateIndirect,    0,			ID_BUTTON_option_page5_0,	150,	15,		110,	40,		0,  0x0, 0 },
	{ GRAPH_CreateIndirect,     0,			ID_GRAPH_option_page5_0,	120,	70,		350,	120 },
	{ GRAPH_CreateIndirect,     0,			ID_GRAPH_option_page5_1,	120,	200,	350,	120 },
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_about[] 			= {
	{ FRAMEWIN_CreateIndirect, 			0,			ID_FRAMEWIN_1,		200,	50,		500,	380 },
	{ TEXT_CreateIndirect,         "Text",			ID_TEXT_about_0,	45,		20,		400,	40,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,         "Text",			ID_TEXT_about_1,	115,	80,		400,	40,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,         "Text",			ID_TEXT_about_2,	175,	140,	200,	40,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,         "Text",			ID_TEXT_about_3,	125,	195,	100,	40,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,         "Text",			ID_TEXT_about_4,	265,	195,	100,	40,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,         "Text",			ID_TEXT_about_5,	125,	250,	100,	40,		0, 0x64, 0 },
	{ TEXT_CreateIndirect,         "Text",			ID_TEXT_about_6,	225,	250,	200,	40,		0, 0x64, 0 },
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_wave1[]			= {
	{ WINDOW_CreateIndirect,            0,				ID_WINDOW_1,     280,   0,		520,	240,  0x0, 0 },
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_wave2[]			= {
	{ WINDOW_CreateIndirect,            0,				ID_WINDOW_2,     280,	240,	520,	240,  0x0, 0 },
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_VPP[]			= {
	{ WINDOW_CreateIndirect,	0,				ID_WINDOW_3,		170,	0, 110, 480,	   0x0, 0 },
	
	{ TEXT_CreateIndirect,		0,				ID_TEXT_VPP_0,		20,	 25,  70,  30, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,				ID_TEXT_VPP_1,		20,	 85,  70,  30, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,				ID_TEXT_VPP_2,		20,	145,  70,  30, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,				ID_TEXT_VPP_3,		20,	205,  70,  30, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,				ID_TEXT_VPP_4,		20,	265,  70,  30, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,				ID_TEXT_VPP_5,		20,	325,  70,  30, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,				ID_TEXT_VPP_6,		20,	385,  70,  30, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,		0,				ID_TEXT_VPP_7,		20,	445,  70,  30, 0, 0x64, 0 },
	
	{ TEXT_CreateIndirect,     	"电涡流 X",		ID_TEXT_VPP_00,  	10,	  0,  80,  16, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "电涡流 Y",		ID_TEXT_VPP_01,  	10,	 60,  80,  16, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "电涡流 X",		ID_TEXT_VPP_02,  	10,	120,  80,  16, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "电涡流 Y",		ID_TEXT_VPP_03,  	10,	180,  80,  16, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "振动 垂直",  	ID_TEXT_VPP_04,  	10,	240,  80,  16, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "振动 水平",  	ID_TEXT_VPP_05,  	10,	300,  80,  16, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "CH 9",			ID_TEXT_VPP_06,  	12,	360,  80,  20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "CH 10",		ID_TEXT_VPP_07,  	12,	420,  80,  20, 0, 0x64, 0 },
	
	{ TEXT_CreateIndirect,     	"um",			ID_TEXT_VPP_10,  	70,	 35,  20,  16, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "um",			ID_TEXT_VPP_11,  	70,	 95,  20,  16, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "um",			ID_TEXT_VPP_12,  	70,	155,  20,  16, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "um",			ID_TEXT_VPP_13,  	70,	215,  20,  16, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "um",  			ID_TEXT_VPP_14,  	70,	275,  30,  16, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "um",  			ID_TEXT_VPP_15,  	70,	335,  30,  16, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "/",			ID_TEXT_VPP_16,  	70,	395,  30,  20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect,      "/",			ID_TEXT_VPP_17,  	70,	455,  30,  20, 0, 0x64, 0 },
};

/*********************************************************************
*
*       _cbDialog  各对话框回调函数
*/
static void _cbDialog_option_page1		(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;

  switch (pMsg->MsgId) {
		
		case WM_INIT_DIALOG:

			// Window 窗口控件 初始化
			hItem = pMsg->hWin;
			WINDOW_SetBkColor(hItem, GUI_WHITE);
		
			// Text  文本框控件 初始化
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page1_0);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," WIFI :");
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page1_1);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 工 作 模 式 :");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page1_2);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," AP 模式");
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page1_3);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 网 络 名 称 : ");
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page1_4);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," YZU-EM-Y ");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page1_5);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 网 络 模 式 :");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page1_6);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," Sever  TCP ");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page1_7);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 服 务 器 IP :");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page1_8);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 10.10.100.254 ");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page1_9);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 端 口：");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page1_10);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 8899 ");
			
			// BUTTON	按钮控件 初始化
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page1_0);
			if( WIFI_or_485 == 0)
			{
				BUTTON_SetBitmapEx(hItem,0,&bmBUTTONON,0,0);
			}
			else
			{	
				BUTTON_SetBitmapEx(hItem,0,&bmBUTTONOFF,0,0);
			}
		
			break;
		
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
		switch(Id) 
			{
				case ID_BUTTON_option_page1_0: 
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page1_0);
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED: 
							
							if( WIFI_or_485 == 1)
							{	
								BUTTON_SetBitmapEx(hItem,0,&bmBUTTONON,0,0);
								hItem = WM_GetDialogItem(hWin_option_page3, ID_BUTTON_option_page3_0);
								BUTTON_SetBitmapEx(hItem,0,&bmBUTTONOFF,0,0);
								WIFI_or_485 = 0;
								break;
							}
							else
							{	
								BUTTON_SetBitmapEx(hItem,0,&bmBUTTONOFF,0,0);
								hItem = WM_GetDialogItem(hWin_option_page3, ID_BUTTON_option_page3_0);
								BUTTON_SetBitmapEx(hItem,0,&bmBUTTONON,0,0);
								WIFI_or_485 = 1;
								break;
							}							
					}
					break;
			}
			break;
		
	default:
		WM_DefaultProc(pMsg);
		break;
  }
}

static void _cbDialog_option_page2		(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;

  switch (pMsg->MsgId) {
		
		case WM_INIT_DIALOG:

			// Window 窗口控件 初始化
			hItem = pMsg->hWin;
			WINDOW_SetBkColor(hItem, GUI_WHITE);
		
			// Text  文本框控件 初始化
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page2_0);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 4 G 移动网络 :");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page2_1);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 服 务 器 A :");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page2_2);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 115.159.4.173    9900 ");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page2_3);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 连 接 方 式 :");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page2_4);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," TCP ");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page2_5);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 连 接 状 态 :");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page2_6);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem, " Not online ");
			
			// BUTTON	按钮控件 初始化
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page2_0);
			BUTTON_SetBitmapEx(hItem,0,&bmBUTTONON,0,0);
					
			break;
		
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
		switch(Id) 
			{
				case ID_BUTTON_option_page2_0: 
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page2_0);
					switch(NCode) 
					{

						case WM_NOTIFICATION_RELEASED: //按钮被按下并释放

						if(GPIO_ReadOutputDataBit(_4G_POWER_KEY_PORT,_4G_POWER_KEY_PIN) == 1)
						{	BUTTON_SetBitmapEx(hItem,0,&bmBUTTONOFF,0,0);
							GPIO_ResetBits(_4G_POWER_KEY_PORT,_4G_POWER_KEY_PIN);		//4G模块关机
							break;
						}
							
						if(GPIO_ReadOutputDataBit(_4G_POWER_KEY_PORT,_4G_POWER_KEY_PIN) == 0)
						{	BUTTON_SetBitmapEx(hItem,0,&bmBUTTONON,0,0);
							GPIO_SetBits(_4G_POWER_KEY_PORT,_4G_POWER_KEY_PIN);			//4G模块开机
							break;
						}

								
					}
					break;
			}
			break;
		
		//WM_TIMER	定时器到期消息					
		case WM_TIMER:
			if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime_option_page2)
			{
							/* 刷新4G连接状态 */
							Refresh_4G(pMsg);
							
							/* 重启定时器 */
							WM_RestartTimer(pMsg->Data.v, 1000);
			}
			break;	
			
		default:
			WM_DefaultProc(pMsg);
			break;
  }
}
static void _cbDialog_option_page3		(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;

  switch (pMsg->MsgId) {
		
		case WM_INIT_DIALOG:

			// Window 窗口控件 初始化
			hItem = pMsg->hWin;
			WINDOW_SetBkColor(hItem, GUI_WHITE);
		
			// Text  文本框控件 初始化
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page3_0);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," RS 485 :");
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page3_1);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 设 备 地 址 :");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page3_2);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 03 ");
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page3_3);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 数 据 格 式 : ");
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page3_4);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," CRC-16/Modbus ");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page3_5);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 波 特 率 : ");
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page3_6);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 115200 ");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page3_7);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 继电器1 ");
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page3_8);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 继电器2 ");
			
			// BUTTON	按钮控件 初始化
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page3_0);
			if( WIFI_or_485 == 1)
			{
				BUTTON_SetBitmapEx(hItem,0,&bmBUTTONON,0,0);
			}
			else
			{	
				BUTTON_SetBitmapEx(hItem,0,&bmBUTTONOFF,0,0);
			}

			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page3_1);
			if( GPIO_ReadOutputDataBit(CONTROL1_PORT,CONTROL1_PIN) == 1)
			{
				BUTTON_SetBitmapEx(hItem,0,&bmOFF_1,0,0);
			}
			else
			{
				BUTTON_SetBitmapEx(hItem,0,&bmON_1,0,0);
			}

			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page3_2);
			if( GPIO_ReadOutputDataBit(CONTROL2_PORT,CONTROL2_PIN) == 1)
			{
				BUTTON_SetBitmapEx(hItem,0,&bmOFF_1,0,0);
			}
			else
			{
				BUTTON_SetBitmapEx(hItem,0,&bmON_1,0,0);
			}
			
			break;
		
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{
				case ID_BUTTON_option_page3_0: 
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page3_0);
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED: 
							
							if( WIFI_or_485 == 1)
							{	
								BUTTON_SetBitmapEx(hItem,0,&bmBUTTONOFF,0,0);
								hItem = WM_GetDialogItem(hWin_option_page1, ID_BUTTON_option_page1_0);
								BUTTON_SetBitmapEx(hItem,0,&bmBUTTONON,0,0);
								WIFI_or_485 = 0;
							}
							else
							{	
								BUTTON_SetBitmapEx(hItem,0,&bmBUTTONON,0,0);
								hItem = WM_GetDialogItem(hWin_option_page1, ID_BUTTON_option_page1_0);
								BUTTON_SetBitmapEx(hItem,0,&bmBUTTONOFF,0,0);
								WIFI_or_485 = 1;
							}		
								break;					
					}
					break;
					
				case ID_BUTTON_option_page3_1:  
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page3_1);
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED: 
							
							if( GPIO_ReadOutputDataBit(CONTROL1_PORT,CONTROL1_PIN) == 1)
							{	
								BUTTON_SetBitmapEx(hItem,0,&bmON_1,0,0);
								GPIO_ResetBits(CONTROL1_PORT,CONTROL1_PIN);
							}
							else
							{	
								BUTTON_SetBitmapEx(hItem,0,&bmOFF_1,0,0);
								GPIO_SetBits(CONTROL1_PORT,CONTROL1_PIN);
								break;
							}							
					}
					break;
					
				case ID_BUTTON_option_page3_2:  
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page3_2);
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED: 
							
							if( GPIO_ReadOutputDataBit(CONTROL2_PORT,CONTROL2_PIN) == 1)
							{	
								BUTTON_SetBitmapEx(hItem,0,&bmON_1,0,0);
								GPIO_ResetBits(CONTROL2_PORT,CONTROL2_PIN);
							}
							else
							{	
								BUTTON_SetBitmapEx(hItem,0,&bmOFF_1,0,0);
								GPIO_SetBits(CONTROL2_PORT,CONTROL2_PIN);
							}	
								break;							
					}
					break;
			}
			break;

	default:
		WM_DefaultProc(pMsg);
		break;
  }
}
static void _cbDialog_option_page4		(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;

  switch (pMsg->MsgId) {
		
		case WM_INIT_DIALOG:

			// Window 窗口控件 初始化
			hItem = pMsg->hWin;
			WINDOW_SetBkColor(hItem, GUI_WHITE);
		
			// Text  文本框控件 初始化
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page4_0);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," S D 存储 :");
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page4_1);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 存 储 空 间 :");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page4_2);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 16 GB ");
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page4_3);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 存 储 间 隔 : ");
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page4_4);
			TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 1 min ");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page4_5);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 存 储 选 择 : ");

			// BUTTON	按钮控件 初始化
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page4_0);
			if( SD_select ==1 )
			{
				BUTTON_SetBitmapEx(hItem,0,&bmBUTTONON,0,0);
			}
			else
			{	
				BUTTON_SetBitmapEx(hItem,0,&bmBUTTONOFF,0,0);
			}

			// CHECKBOX	复选框控件 初始化
			hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_option_page4_0);
			CHECKBOX_SetFont(hItem,GUI_FONT_16B_ASCII);
			if( SD_select_CH12 ==1 )
			{
				CHECKBOX_SetState(hItem,1);
			}
			else
			{	
				CHECKBOX_SetState(hItem,0);
			}
			CHECKBOX_SetText(hItem," CH1 / CH2 ");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_option_page4_1);
			CHECKBOX_SetFont(hItem,GUI_FONT_16B_ASCII);
			if( SD_select_CH34 ==1 )
			{
				CHECKBOX_SetState(hItem,1);
			}
			else
			{	
				CHECKBOX_SetState(hItem,0);
			}
			CHECKBOX_SetText(hItem," CH3 / CH4 ");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_option_page4_2);
			CHECKBOX_SetFont(hItem,GUI_FONT_16B_ASCII);
			if( SD_select_CH78 ==1 )
			{
				CHECKBOX_SetState(hItem,1);
			}
			else
			{	
				CHECKBOX_SetState(hItem,0);
			}
			CHECKBOX_SetText(hItem," CH7 / CH8 ");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_option_page4_3);
			CHECKBOX_SetFont(hItem,GUI_FONT_16B_ASCII);
			if( SD_select_CH910 ==1 )
			{
				CHECKBOX_SetState(hItem,1);
			}
			else
			{	
				CHECKBOX_SetState(hItem,0);
			}
			CHECKBOX_SetText(hItem," CH9 / CH10 ");
				
			break;
			
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{	
				case ID_BUTTON_option_page4_0: 
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page4_0);
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED: 
							
							if( SD_select == 1)
							{	
								BUTTON_SetBitmapEx(hItem,0,&bmBUTTONOFF,0,0);
								SD_select = 0;
							}
							else
							{	
								BUTTON_SetBitmapEx(hItem,0,&bmBUTTONON,0,0);
								SD_select = 1;
							}		
								break;					
					}
					break;
					
				case ID_CHECKBOX_option_page4_0: 
					hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_option_page4_0);
					switch(NCode) 
					{
						case WM_NOTIFICATION_VALUE_CHANGED: 
							
							if( CHECKBOX_GetState(hItem) == 1)
							{	
								SD_select_CH12 =1;
							}
							else
							{	
								SD_select_CH12 =0;
							}	
							break;					
					}
					break;
					
				case ID_CHECKBOX_option_page4_1: 
					hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_option_page4_1);
					switch(NCode) 
					{
						case WM_NOTIFICATION_VALUE_CHANGED: 
							
							if( CHECKBOX_GetState(hItem) == 1)
							{	
								SD_select_CH34 =1;
							}
							else
							{	
								SD_select_CH34 =0;
							}		
							break;					
					}
					break;
				
				case ID_CHECKBOX_option_page4_2: 
					hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_option_page4_2);
					switch(NCode) 
					{
						case WM_NOTIFICATION_VALUE_CHANGED: 
							
							if( CHECKBOX_GetState(hItem) == 1)
							{	
								SD_select_CH78 =1;
							}
							else
							{	
								SD_select_CH78 =0;
							}		
							break;					
					}
					break;
					
				case ID_CHECKBOX_option_page4_3: 
					hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_option_page4_3);
					switch(NCode) 
					{
						case WM_NOTIFICATION_VALUE_CHANGED: 
							
							if( CHECKBOX_GetState(hItem) == 1)
							{	
								SD_select_CH910 =1;
							}
							else
							{	
								SD_select_CH910 =0;
							}	
							break;						
					}
					break;
				
			}
				break;

	default:
		WM_DefaultProc(pMsg);
		break;
  }
}

static void _cbDialog_option_page5		(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;

	switch (pMsg->MsgId) {
		
		case WM_INIT_DIALOG:

			// Window 窗口控件 初始化
			hItem = pMsg->hWin;
			WINDOW_SetBkColor(hItem, GUI_WHITE);
		
			// Text  文本框控件 初始化
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page5_0);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," GPS 定位服务:");
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page5_1);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," CPU 温度 ");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page5_2);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," CPU 占用率 ");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page5_3);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 单位 ℃ ");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_option_page5_4);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 单位 % ");
			
			// GRAPH 曲线图形控件 初始化
			hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_option_page5_0);
			GRAPH_SetColor(hItem,GUI_WHITE,GRAPH_CI_BK);
			GRAPH_SetBorder(hItem,20,5,5,5);
			GRAPH_SetGridDistY(hItem,20);
			GRAPH_SetLineStyleH(hItem,GUI_LS_DOT);
			GRAPH_SetLineStyleV(hItem,GUI_LS_DOT);
			GRAPH_SetGridVis(hItem, 1);
			_GRAPH_DATA1 = GRAPH_DATA_YT_Create(0xff081272, 330, 0, 0);
			GRAPH_AttachData(hItem, _GRAPH_DATA1);
//			GRAPH_DATA_YT_SetAlign(_GRAPH_DATA1,GRAPH_ALIGN_LEFT);
			_hScaleV = GRAPH_SCALE_Create(18,GUI_TA_RIGHT,GRAPH_SCALE_CF_VERTICAL,20);
			GRAPH_SCALE_SetTextColor(_hScaleV, GUI_BLACK);
			GRAPH_AttachScale(hItem, _hScaleV);

			hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_option_page5_1);
			GRAPH_SetColor(hItem,GUI_WHITE,GRAPH_CI_BK);
			GRAPH_SetBorder(hItem,20,5,5,5);
			GRAPH_SetGridDistY(hItem,20);
			GRAPH_SetLineStyleH(hItem,GUI_LS_DOT);
			GRAPH_SetLineStyleV(hItem,GUI_LS_DOT);
			GRAPH_SetGridVis(hItem, 1);
			_GRAPH_DATA2 = GRAPH_DATA_YT_Create(0xff081272, 330, 0, 0);
			GRAPH_AttachData(hItem, _GRAPH_DATA2);
//			GRAPH_DATA_YT_SetAlign(_GRAPH_DATA2,GRAPH_ALIGN_LEFT);
			_hScaleV = GRAPH_SCALE_Create(18,GUI_TA_RIGHT,GRAPH_SCALE_CF_VERTICAL,20);
			GRAPH_SCALE_SetTextColor(_hScaleV, GUI_BLACK);
			GRAPH_AttachScale(hItem, _hScaleV);			
								
			// BUTTON	按钮控件 初始化
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page5_0);
			if(	GPS_select ==1 )
			{
				BUTTON_SetBitmapEx(hItem,0,&bmBUTTONON,0,0);
			}
			else
			{
				BUTTON_SetBitmapEx(hItem,0,&bmBUTTONOFF,0,0);
			}
		
			break;
			
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{	
				case ID_BUTTON_option_page5_0: 
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_option_page5_0);
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED: 

								if(	GPS_select ==1 )
								{
									BUTTON_SetBitmapEx(hItem,0,&bmBUTTONOFF,0,0);
									GPS_select =0;
								}
								else
								{
									BUTTON_SetBitmapEx(hItem,0,&bmBUTTONON,0,0);
									GPS_select =1;
								}
		
							break;					
					}
					break;
					
			}
			break;
			
		//WM_TIMER	定时器到期消息					
		case WM_TIMER:
			  if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime_option_page5)
				{	
					
					//STM32F4芯片温度检测
					temperature = (int)  ADC_GetTemp()  ;
					GRAPH_DATA_YT_AddValue(_GRAPH_DATA1, temperature);
					
					GRAPH_DATA_YT_AddValue(_GRAPH_DATA2, OSStatTaskCPUUsage / 100);
					
					/* 重启定时器 */
					WM_RestartTimer(pMsg->Data.v, 200);
				}
				break;			
	default:
		WM_DefaultProc(pMsg);
		break;
  }
}
static void _cbDialog_option			(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	WM_HWIN hWinPage;

	switch (pMsg->MsgId) {
		
		case WM_INIT_DIALOG:

			hItem = pMsg->hWin;
			FRAMEWIN_AddCloseButton(hItem, FRAMEWIN_BUTTON_LEFT, 0);
			FRAMEWIN_SetClientColor(hItem,GUI_WHITE);
			FRAMEWIN_SetTextColor(hItem,GUI_BLACK);
			FRAMEWIN_SetTitleHeight(hItem,25);
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIPAGE_0);
			MULTIPAGE_SetFont(hItem,&XBF_Font16);
			MULTIPAGE_SetTabHeight(hItem,40);
		
			hWinPage = GUI_CreateDialogBox(_aDialogCreate_option_page1, GUI_COUNTOF(_aDialogCreate_option_page1), _cbDialog_option_page1, pMsg->hWin, 0, 0); 
			hWin_option_page1 = hWinPage;
			MULTIPAGE_AddEmptyPage(hItem, hWinPage, ""); 
			MULTIPAGE_SetBitmap(hItem,&bmwifi,0,MULTIPAGE_BI_SELECTED | MULTIPAGE_BI_UNSELECTED);
			MULTIPAGE_SetTabWidth(hItem, 95,0);
		
			hWinPage = GUI_CreateDialogBox(_aDialogCreate_option_page2, GUI_COUNTOF(_aDialogCreate_option_page2), _cbDialog_option_page2, pMsg->hWin, 0, 0);
			hWin_option_page2 = hWinPage;
			WM_CreateTimer(WM_GetClientWindow(hWinPage),ID_TimerTime_option_page2,10,0);   			//创建一个定时器 
			MULTIPAGE_AddEmptyPage(hItem, hWinPage, ""); 
			MULTIPAGE_SetBitmap(hItem,&bm4G,1,MULTIPAGE_BI_SELECTED | MULTIPAGE_BI_UNSELECTED );
			MULTIPAGE_SetTabWidth(hItem, 95,1);

			hWinPage = GUI_CreateDialogBox(_aDialogCreate_option_page3, GUI_COUNTOF(_aDialogCreate_option_page3), _cbDialog_option_page3, pMsg->hWin, 0, 0);
			hWin_option_page3 = hWinPage;
			MULTIPAGE_AddEmptyPage(hItem, hWinPage, ""); 
			MULTIPAGE_SetBitmap(hItem,&bmRS485,2,MULTIPAGE_BI_SELECTED | MULTIPAGE_BI_UNSELECTED );
			MULTIPAGE_SetTabWidth(hItem, 95,2);
	
			hWinPage = GUI_CreateDialogBox(_aDialogCreate_option_page4, GUI_COUNTOF(_aDialogCreate_option_page4), _cbDialog_option_page4, pMsg->hWin, 0, 0);
			hWin_option_page4 = hWinPage;
			MULTIPAGE_AddEmptyPage(hItem, hWinPage, ""); 
			MULTIPAGE_SetBitmap(hItem,&bmSD,3,MULTIPAGE_BI_SELECTED | MULTIPAGE_BI_UNSELECTED );
			MULTIPAGE_SetTabWidth(hItem, 95,3);

			hWinPage = GUI_CreateDialogBox(_aDialogCreate_option_page5, GUI_COUNTOF(_aDialogCreate_option_page5), _cbDialog_option_page5, pMsg->hWin, 0, 0);
			hWin_option_page5 = hWinPage;
			WM_CreateTimer(WM_GetClientWindow(hWinPage),ID_TimerTime_option_page5,10,0);   			//创建一个定时器 
			MULTIPAGE_AddEmptyPage(hItem, hWinPage, " 系统 "); 
			MULTIPAGE_SetTabWidth(hItem, 105,4);
			
			MULTIPAGE_SelectPage(hItem,0);
			
			break;
			
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

static void _cbDialog_about				(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;

  switch (pMsg->MsgId) {
		
		case WM_INIT_DIALOG:

			hItem = pMsg->hWin;
			FRAMEWIN_AddCloseButton(hItem, FRAMEWIN_BUTTON_LEFT, 0);
			FRAMEWIN_SetClientColor(hItem,0xFF1E2F2D);
			FRAMEWIN_SetTitleHeight(hItem,25);
		
			// Text  文本框控件 初始化
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_about_0);
			TEXT_SetFont(hItem,GUI_FONT_24B_1);
			TEXT_SetTextColor(hItem, GUI_WHITE	);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," Electromechanical Monitoring Device ");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_about_1);
			TEXT_SetFont(hItem,GUI_FONT_16B_1);
			TEXT_SetTextColor(hItem, GUI_WHITE	);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," Copyright  2019  YangZhou university ");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_about_2);
			TEXT_SetFont(hItem,GUI_FONT_16B_1);
			TEXT_SetTextColor(hItem, GUI_WHITE	);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 2019 / 4 - 2019 / 6 ");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_about_3);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_WHITE	);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 版本号 ");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_about_4);
			TEXT_SetFont(hItem,GUI_FONT_16B_1);
			TEXT_SetTextColor(hItem, GUI_WHITE	);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," V  1.0 ");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_about_5);
			TEXT_SetFont(hItem,&XBF_Font16);
			TEXT_SetTextColor(hItem, GUI_WHITE	);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," 制作者 ");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_about_6);
			TEXT_SetFont(hItem,GUI_FONT_16B_1);
			TEXT_SetTextColor(hItem, GUI_WHITE	);
			TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
			TEXT_SetText(hItem," YANG SHOU CHEN ");
			
			break;
		
	default:
		WM_DefaultProc(pMsg);
		break;
  }
}

static void _cbDialog_wave1				(WM_MESSAGE * pMsg) { 
	WM_HWIN hItem;

	switch (pMsg->MsgId) 
	{
		case WM_INIT_DIALOG:
					// Window 窗口控件 初始化
					hItem = pMsg->hWin;
					WINDOW_SetBkColor(hItem, GUI_BLACK	);
		
			break;
		
		case WM_PAINT:
			
			Refresh_wave1_grid();		//绘制坐标系
		
			switch(CH_select){
				case 0 :
						GUI_SetColor(0x00A64D00);			
						GUI_DrawGraph((I16 * )&AD_Value_FIR_CH1,500,20,120); 

						GUI_SetColor(0x00006064);			
						GUI_DrawGraph((I16 * )&AD_Value_FIR_CH2,500,20,120); 
				break;
				
				case 1 :
						GUI_SetColor(0x00A64D00);			
						GUI_DrawGraph((I16 * )&AD_Value_FIR_CH3,500,20,120); 

						GUI_SetColor(0x00006064);			
						GUI_DrawGraph((I16 * )&AD_Value_FIR_CH4,500,20,120); 
				break;
				
				case 2 :
						GUI_SetColor(0x00A64D00);			
						GUI_DrawGraph((I16 * )&AD_Value_FIR_CH7,500,20,120); 

						GUI_SetColor(0x00006064);			
						GUI_DrawGraph((I16 * )&AD_Value_FIR_CH8,500,20,120); 
				break;
				
				case 3 :
						GUI_SetColor(0x00A64D00);			
						GUI_DrawGraph((I16 * )&AD_Value_FIR_CH9,500,20,120); 

						GUI_SetColor(0x00006064);			
						GUI_DrawGraph((I16 * )&AD_Value_FIR_CH10,500,20,120); 
				break;
			}
			break;
			
	case WM_NOTIFY_PARENT:

		
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

static void _cbDialog_wave2				(WM_MESSAGE * pMsg) { 
	WM_HWIN hItem;

	uint16_t	circumference=0;
	uint16_t	i=0;
	switch (pMsg->MsgId) 
	{
		case WM_INIT_DIALOG:
					// Window 窗口控件 初始化
					hItem = pMsg->hWin;
					WINDOW_SetBkColor(hItem, GUI_BLACK);
			break;
		
		case WM_PAINT:

			Refresh_wave2_grid();		//绘制坐标系
		
			switch(CH_select){
				case 0 :
						GUI_SetColor(0x00A64D00);
						for(i=0;i<260;i+=4)
						{
							GUI_DrawLine( 20+i,AD_Value_FFT_CH1[i/4]+238,20+i+4,AD_Value_FFT_CH1[i/4+1]+238);
						}

						
						GUI_SetColor(0x00006064);			
						for(i=0;i<260;i+=4)
						{
							GUI_DrawLine( 20+i,AD_Value_FFT_CH2[i/4]+120,20+i+4,AD_Value_FFT_CH2[i/4+1]+120);
						}						
						
						if(AD_Value_CH1_VPP !=0 && AD_Value_CH2_VPP !=0) {
							circumference = (int)60 * 4000 / 2 / CH5_SPEED * 2;// "/2" 测速通道采样速率/其他通道采样速率 "*2" 显示两圈
							GUI_SetColor(GUI_WHITE);
							GUI_SetPenSize(2);			
							for(i=256;i<circumference+256;i++)
							{	
								if(AD_Value_CH1_VPP *0.61 < 120 && AD_Value_CH2_VPP *0.61 < 120)
								{	
									GUI_DrawLine((400+AD_Value_FIR_CH1[i]),(130-AD_Value_FIR_CH2[i]),(400+AD_Value_FIR_CH1[i+1]),(130-AD_Value_FIR_CH2[i+1]));
								}
								else
								{
									GUI_DrawLine((400+(int)AD_Value_FIR_CH1[i]/2),(130-(int)AD_Value_FIR_CH2[i]/2),(400+(int)AD_Value_FIR_CH1[i+1]/2),(130-(int)AD_Value_FIR_CH2[i+1]/2));
								}
							}
							GUI_SetPenSize(1);
						}
				break;
				
				case 1 :
						GUI_SetColor(0x00A64D00);
						for(i=0;i<260;i+=4)
						{
							GUI_DrawLine( 20+i,AD_Value_FFT_CH3[i/4]+230,20+i+4,AD_Value_FFT_CH3[i/4+1]+230);
						}						
				
						GUI_SetColor(0x00006064);			
						for(i=0;i<260;i+=4)
						{
							GUI_DrawLine( 20+i,AD_Value_FFT_CH4[i/4]+120,20+i+4,AD_Value_FFT_CH4[i/4+1]+120);
						}						
						
						if(AD_Value_CH3_VPP !=0 && AD_Value_CH4_VPP !=0) {
							circumference = (int)60 * 4000 / 2 /CH6_SPEED * 2;// "/2" 测速通道采样速率/其他通道采样速率 "*2" 显示两圈
							GUI_SetColor(GUI_WHITE);
							GUI_SetPenSize(2);			
							for(i=256;i<circumference+256;i++)
							{	
								if(AD_Value_CH3_VPP *0.61 < 120 && AD_Value_CH4_VPP *0.61 < 120)
								{
									GUI_DrawLine((400+AD_Value_FIR_CH3[i]),(130-AD_Value_FIR_CH4[i]),(400+AD_Value_FIR_CH3[i+1]),(130-AD_Value_FIR_CH4[i+1]));
								}
								else
								{
									GUI_DrawLine((400+(int)AD_Value_FIR_CH3[i]/2),(130-(int)AD_Value_FIR_CH4[i]/2),(400+(int)AD_Value_FIR_CH3[i+1]/2),(130-(int)AD_Value_FIR_CH4[i+1]/2));
								}
							}
							GUI_SetPenSize(1);
						}
				break;
						
				case 2 :
						GUI_SetColor(0x00A64D00);
						for(i=0;i<500;i+=4)
						{
							GUI_DrawLine( 20+i,AD_Value_FFT_CH7[i/4]+238,20+i+4,AD_Value_FFT_CH7[i/4+1]+238);
						}

						GUI_SetColor(0x00006064);			
						for(i=0;i<500;i+=4)
						{
							GUI_DrawLine( 20+i,AD_Value_FFT_CH8[i/4]+120,20+i+4,AD_Value_FFT_CH8[i/4+1]+120);
						}
				break;
				
				case 3 :
						GUI_SetColor(0x00A64D00);			
						GUI_DrawGraph((I16 * )&AD_Value_FFT_CH9,500,20,238);

						GUI_SetColor(0x00006064);			
						GUI_DrawGraph((I16 * )&AD_Value_FFT_CH10,500,20,120); 
				break;
			}
			break;
			
	case WM_NOTIFY_PARENT:

		break;
		
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}


static void _cbDialog_VPP				(WM_MESSAGE * pMsg) { 
	WM_HWIN hItem;

	char buf[10];
	
	switch (pMsg->MsgId) 
	{
		case WM_INIT_DIALOG:
					// Window 窗口控件 初始化
					hItem = pMsg->hWin;
					WINDOW_SetBkColor(hItem,GUI_BLACK);
					// Text  文本框控件 初始化
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_0);
					TEXT_SetFont(hItem,GUI_FONT_32B_ASCII);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
		
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_1);
					TEXT_SetFont(hItem,GUI_FONT_32B_ASCII);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
		
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_2);
					TEXT_SetFont(hItem,GUI_FONT_32B_ASCII);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
		
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_3);
					TEXT_SetFont(hItem,GUI_FONT_32B_ASCII);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_4);
					TEXT_SetFont(hItem,GUI_FONT_32B_ASCII);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_5);
					TEXT_SetFont(hItem,GUI_FONT_32B_ASCII);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_6);
					TEXT_SetFont(hItem,GUI_FONT_32B_ASCII);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_7);
					TEXT_SetFont(hItem,GUI_FONT_32B_ASCII);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_00);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_01);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_02);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_03);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_04);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_05);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_06);
					TEXT_SetFont(hItem,GUI_FONT_20B_1 );
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_07);
					TEXT_SetFont(hItem,GUI_FONT_20B_1 );
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_10);
					TEXT_SetFont(hItem,GUI_FONT_16B_1 );
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_11);
					TEXT_SetFont(hItem,GUI_FONT_16B_1 );
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_12);
					TEXT_SetFont(hItem,GUI_FONT_16B_1 );
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_13);
					TEXT_SetFont(hItem,GUI_FONT_16B_1 );
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_14);
					TEXT_SetFont(hItem,GUI_FONT_16B_1 );
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_15);
					TEXT_SetFont(hItem,GUI_FONT_16B_1 );
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_16);
					TEXT_SetFont(hItem,GUI_FONT_16B_1 );
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_17);
					TEXT_SetFont(hItem,GUI_FONT_16B_1 );
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, TEXT_CF_LEFT | TEXT_CF_VCENTER);
					
			break;
			
	case WM_NOTIFY_PARENT:

		break;
		
		//WM_TIMER	定时器到期消息					
		case WM_TIMER:
			  if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime_VPP)
				{	
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_0);
					memset(buf, 0, sizeof(buf));
					sprintf((char *)buf, "%d", (int)(AD_Value_CH1_VPP * 0.61));		// *0.61 转化为 um 单位
					if(CH_select == 0)
					{	TEXT_SetTextColor(hItem, 0x00A64D00);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}
					TEXT_SetText(hItem, buf);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_1);
					memset(buf, 0, sizeof(buf));
					sprintf((char *)buf, "%d", (int)(AD_Value_CH2_VPP * 0.61));		// *0.61 转化为 um 单位
					if(CH_select == 0)
					{	TEXT_SetTextColor(hItem, 0x00006064);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}
					TEXT_SetText(hItem, buf);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_2);
					memset(buf, 0, sizeof(buf));
					sprintf((char *)buf, "%d", (int)(AD_Value_CH3_VPP * 0.61));		// *0.61 转化为 um 单位
					if(CH_select == 1)
					{	TEXT_SetTextColor(hItem, 0x00A64D00);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}
					TEXT_SetText(hItem, buf);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_3);
					memset(buf, 0, sizeof(buf));
					sprintf((char *)buf, "%d", (int)(AD_Value_CH4_VPP * 0.61));		// *0.61 转化为 um 单位
					if(CH_select == 1)
					{	TEXT_SetTextColor(hItem, 0x00006064);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}
					TEXT_SetText(hItem, buf);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_4);
					memset(buf, 0, sizeof(buf));
					sprintf((char *)buf, "%d", (int)(AD_Value_CH7_VPP * 0.61));		// *0.61 转化为 um 单位
					if(CH_select == 2)
					{	TEXT_SetTextColor(hItem, 0x00A64D00);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}
					TEXT_SetText(hItem, buf);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_5);
					memset(buf, 0, sizeof(buf));
					sprintf((char *)buf, "%d", (int)(AD_Value_CH8_VPP * 0.61));		// *0.61 转化为 um 单位
					if(CH_select == 2)
					{	TEXT_SetTextColor(hItem, 0x00006064);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}
					TEXT_SetText(hItem, buf);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_6);
					memset(buf, 0, sizeof(buf));
					sprintf((char *)buf, "%d", AD_Value_CH9_VPP);
					if(CH_select == 3)
					{	TEXT_SetTextColor(hItem, 0x00A64D00);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}
					TEXT_SetText(hItem, buf);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_7);
					memset(buf, 0, sizeof(buf));
					sprintf((char *)buf, "%d", AD_Value_CH10_VPP);
					if(CH_select == 3)
					{	TEXT_SetTextColor(hItem, 0x00006064);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}
					TEXT_SetText(hItem, buf);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_00);
					if(CH_select == 0)
					{	TEXT_SetTextColor(hItem, 0x00A64D00);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_01);
					if(CH_select == 0)
					{	TEXT_SetTextColor(hItem, 0x00006064);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_02);
					if(CH_select == 1)
					{	TEXT_SetTextColor(hItem, 0x00A64D00);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_03);
					if(CH_select == 1)
					{	TEXT_SetTextColor(hItem, 0x00006064);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_04);
					if(CH_select == 2)
					{	TEXT_SetTextColor(hItem, 0x00A64D00);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_05);
					if(CH_select == 2)
					{	TEXT_SetTextColor(hItem, 0x00006064);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_06);
					if(CH_select == 3)
					{	TEXT_SetTextColor(hItem, 0x00A64D00);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VPP_07);
					if(CH_select == 3)
					{	TEXT_SetTextColor(hItem, 0x00006064);}
					else
					{	TEXT_SetTextColor(hItem, GUI_WHITE);}
					
					/* 重启定时器 */
					WM_RestartTimer(pMsg->Data.v, 500);
				}
				break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

static void _cbDialog 					(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;

	switch (pMsg->MsgId) {
		
				case WM_INIT_DIALOG:
					
					// Window 窗口控件 初始化
					hItem = pMsg->hWin;
					WINDOW_SetBkColor(hItem, 0x007D5430);
				
					// IMAGE 图像控件 初始化
					hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_0);
					IMAGE_SetBitmap(hItem,&bmyzu_yzu);
				
					// Text  文本框控件 初始化
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
					TEXT_SetFont(hItem,GUI_FONT_24B_ASCII);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
				
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
					TEXT_SetFont(hItem,GUI_FONT_13_1);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
				
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem,GUI_FONT_20B_1);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem,GUI_FONT_20B_1);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_11);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_12);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_13);
					TEXT_SetTextColor(hItem, GUI_WHITE);
					TEXT_SetFont(hItem,&XBF_Font16);
					TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);	
					
					//BUTTON  按钮控件 初始化
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
					BUTTON_SetBitmapEx(hItem,0,&bmswitch,0,0);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
					BUTTON_SetBitmapEx(hItem,0,&bmsetting,0,0);
					
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
					BUTTON_SetBitmapEx(hItem,0,&bmabout,0,0);

							
				break;
				
				case WM_NOTIFY_PARENT:
					Id    = WM_GetId(pMsg->hWinSrc);
					NCode = pMsg->Data.v;
					switch(Id) {			
								case ID_BUTTON_0:
									switch(NCode) {
									case WM_NOTIFICATION_CLICKED:
										CH_select++;
										if(CH_select==4)CH_select=0;
										WM_InvalidateWindow(hWin_wave1);	//失效该窗口，使其重绘曲线
										WM_InvalidateWindow(hWin_wave2);	//失效该窗口，使其重绘曲线
										GUI_Exec();							//立即重绘
										break;
									}
									break;	
									
								case ID_BUTTON_1: 
									switch(NCode) {
									case WM_NOTIFICATION_CLICKED:		
										hWin1=GUI_CreateDialogBox(_aDialogCreate_option, GUI_COUNTOF(_aDialogCreate_option), _cbDialog_option, WM_HBKWIN, 0, 0);         //创建子对话框
										break;
									}
									break;		
									
								case ID_BUTTON_2:
									switch(NCode) {
									case WM_NOTIFICATION_CLICKED:		
										hWin2=GUI_CreateDialogBox(_aDialogCreate_about, GUI_COUNTOF(_aDialogCreate_about), _cbDialog_about, WM_HBKWIN, 0, 0);         //创建子对话框
										break;
									}
									break;
					          }
					break;
										
				//WM_TIMER	定时器到期消息					
				case WM_TIMER:
					  if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime)
						{
							/* 刷新GPS、RTC信息 */
							Refresh_RTC_GPS(pMsg);

							/* 刷新DHT11温湿度 */
							Refresh_DHT11(pMsg);									
							
							/* 刷新机组转速 */
							Refresh_SPEED(pMsg);
							
							/* 重启定时器 */
							WM_RestartTimer(pMsg->Data.v, 200);
						}
						break;
								
	default:
		WM_DefaultProc(pMsg);
		break;
  }
}


/*********************************************************************
*
*       MainTask   显示主函数
*/
void MainTask(void);
void MainTask(void) {

	hDlg 	   = GUI_CreateDialogBox(_aDialogCreate,		GUI_COUNTOF(_aDialogCreate),		_cbDialog, 			WM_HBKWIN, 0, 0);
	hWin_VPP   = GUI_CreateDialogBox(_aDialogCreate_VPP, 	GUI_COUNTOF(_aDialogCreate_VPP),	_cbDialog_VPP,		WM_HBKWIN, 0, 0);
	hWin_wave1 = GUI_CreateDialogBox(_aDialogCreate_wave1, 	GUI_COUNTOF(_aDialogCreate_wave1),	_cbDialog_wave1,	WM_HBKWIN, 0, 0);
	hWin_wave2 = GUI_CreateDialogBox(_aDialogCreate_wave2,	GUI_COUNTOF(_aDialogCreate_wave2),	_cbDialog_wave2,	WM_HBKWIN, 0, 0);
	
	WM_CreateTimer(WM_GetClientWindow(hDlg),ID_TimerTime,10,0);   			//主对话框				创建一个定时器
	WM_CreateTimer(WM_GetClientWindow(hWin_VPP),ID_TimerTime_VPP,10,0);		//峰峰值数值显示对话框	创建一个定时器 
	
	while (1) {

		if(data_ready_display==1)
		{   
			WM_InvalidateWindow(hWin_wave1);   //失效该窗口，使其重绘曲线
			WM_InvalidateWindow(hWin_wave2);   //失效该窗口，使其重绘曲线
			data_ready_display=0;
		}

		GUI_Delay(10);		//屏幕刷新周期10ms 100Hz
	}
}

