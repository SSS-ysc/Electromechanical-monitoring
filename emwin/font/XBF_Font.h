#ifndef __XBF_FONT_H
#define __XBF_FONT_H

#include "GUI.h"
#include "spi_flash.h"

/*---------------------------------- XBF格式字体相关定义声明 ---------------------------------*/

extern GUI_XBF_DATA 	XBF_Data16;
extern GUI_FONT     	XBF_Font16;
extern void         	*XBF_file16;

/* XBF24点阵 */

extern GUI_XBF_DATA 	XBF_Data24;
extern GUI_FONT     	XBF_Font24;
extern void         	*XBF_file24;

/* XBF32点阵 */

extern GUI_XBF_DATA 	XBF_Data32;
extern GUI_FONT     	XBF_Font32;
extern void         	*XBF_file32;

/*------------------------------------- 函数声明 ---------------------------------------------*/  		

int _cbGetData_XBF16(U32 Off, U16 NumBytes, void * pVoid, void * pBuffer);		// XBF16字体的回调函数，emwin自行调用
int _cbGetData_XBF24(U32 Off, U16 NumBytes, void * pVoid, void * pBuffer);		// XBF24字体的回调函数，emwin自行调用
int _cbGetData_XBF32(U32 Off, U16 NumBytes, void * pVoid, void * pBuffer);		// XBF32字体的回调函数，emwin自行调用


#endif //__XBF_FONT_H
