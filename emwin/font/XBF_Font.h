#ifndef __XBF_FONT_H
#define __XBF_FONT_H

#include "GUI.h"
#include "spi_flash.h"

/*---------------------------------- XBF��ʽ������ض������� ---------------------------------*/

extern GUI_XBF_DATA 	XBF_Data16;
extern GUI_FONT     	XBF_Font16;
extern void         	*XBF_file16;

/* XBF24���� */

extern GUI_XBF_DATA 	XBF_Data24;
extern GUI_FONT     	XBF_Font24;
extern void         	*XBF_file24;

/* XBF32���� */

extern GUI_XBF_DATA 	XBF_Data32;
extern GUI_FONT     	XBF_Font32;
extern void         	*XBF_file32;

/*------------------------------------- �������� ---------------------------------------------*/  		

int _cbGetData_XBF16(U32 Off, U16 NumBytes, void * pVoid, void * pBuffer);		// XBF16����Ļص�������emwin���е���
int _cbGetData_XBF24(U32 Off, U16 NumBytes, void * pVoid, void * pBuffer);		// XBF24����Ļص�������emwin���е���
int _cbGetData_XBF32(U32 Off, U16 NumBytes, void * pVoid, void * pBuffer);		// XBF32����Ļص�������emwin���е���


#endif //__XBF_FONT_H
