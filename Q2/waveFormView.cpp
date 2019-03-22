
#include "waveFormDoc.h"
#include "waveFormView.h"
#include <stdlib.h>
#include <cmath> 
#include <iostream> 
#include  <string> 
#include <stdio.h> 

using namespace std;


CwaveFormView::CwaveFormView()
{

}

CwaveFormView::~CwaveFormView()
{
}

BOOL CwaveFormView::PreCreateWindow(CREATESTRUCT& op)
{

	return CView::PreCreateWindow(op);
}
void CwaveFormView::drawWav(CDC* pointer1, WaveView* pointer2)
{
	CRect rect;
	GetClientRect(&rect);
	CPen gpen(PS_SOLID, 1, RGB(250, 0, 0));
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	pointer1->SelectObject(&gpen);
	float Val = pow(2.0, 8.0*pointer2->BytesPerSample - 1);	//#include<cmath> 
	if (pointer2->channel == 1)
	{
		int x = 0, y = rect.Height() / 2;
		while (x<rect.Width())
		{
			int minVal = INT_maxVal;
			int maxVal = INT_maxVal + 1;
			int lineVal1=2;
			int lineVal2=4;
			for (int j = x * pointer2->num / rect.Width(); j<(x + 1)*pointer2->num / rect.Width(); j++)
			{
				if (j>0 )
				{
					if(j<pointer2->num)
					{
						if (pointer2->data[j]<minVal)
						{
							minVal = pointer2->data[j];
						}
					}

			
				}
				if (j>0 )
				{
					if (j<pointer2->num)
					{
						if (maxVal<pointer2->data[j])
						{
							maxVal = pointer2->data[j];
						}
					}
					
				}
			}
			if (x!=0&&y!=0)
			{
				pointer1->MoveTo(x, y + (maxVal*rect.Height() / lineVal1 / Val));
				pointer1->LineTo(x, y + (minVal*rect.Height() / lineVal1/ Val));
			}
			
			x++;
		}
		pointer1->SelectObject(&pen);
		pointer1->MoveTo(0, rect.Height() / 2);
		pointer1->LineTo(rect.Width(), rect.Height() / 2);
	}
	else if (pointer2->channel == 2)
	{
		int x = 0;
		int	y = rect.Height() / 4;
		while (x<rect.Width())
		{
			int minVal = INT_maxVal;
			int	maxVal = INT_minVal;
			for (int j = x * pointer2->num / 2 / rect.Width(); j<(x + 1)*pointer2->num / 2 / rect.Width(); j++)
			{
				if (j>0)
				{
					if (j<pointer2->num)
					{
						if (pointer2->LData[j]<minVal)
						{
							minVal = pointer2->LData[j];
						}
					}
					
				}
				if (j>0 )
				{
					if (j<pointer2->num)
					{
						if (pointer2->LData[j]>maxVal)
						{
							maxVal = pointer2->LData[j];
						}
					}
				}
			}
			if (x!=0&&y!=0)
			{
				pointer1->MoveTo(x, y + (maxVal*rect.Height() / lineVal2 / Val));
				pointer1->LineTo(x, y + (minVal*rect.Height() / lineVal2/ Val));
			}
			
			x++;

		}
		x = 0, y = 3 * rect.Height() / 4;
		while (x<rect.Width())
		{
			int minVal = INT_maxVal, maxVal = INT_minVal;
			for (int j = x * pointer2->num / 2 / rect.Width(); j<(x + 1)*pointer2->num / 2 / rect.Width(); j++)
			{
				if (j>0)
				{
					if (j<pointer2->num)
					{
						if (pointer2->DATA[j]<minVal)
						{
							minVal = pointer2->DATA[j];
						}
					}
				}
				if (j>0)
				{
					if (j<pointer2->num)
					{
						if (maxVal<pointer2->DATA[j])
						{
							maxVal = pointer2->DATA[j];
						}
					}
				}
			}
			gpen.DeleteObject();
			gpen.CreatePen(PS_SOLID, 1, RGB(0, 0, 250));
			pointer1->SelectObject(&gpen);
			if (x!=0&&y!=0)
			{
				pointer1->MoveTo(x, y + (maxVal*rect.Height() / lineVal2 / Val));
				pointer1->LineTo(x, y + (minVal*rect.Height() / lineVal2/ Val));
			}
			
			x++;
		}
	}
	char arr1[1000];
	char arr2[1000];
	sprintf_s(arr2, "Total numbers of samples: %d ", pointer2->num);
	pointer2->num = 0;
	sprintf_s(arr1, "maxVal value: %d", pointer2->maxValValue);
	pointer2->maxValValue = 0;
	CString a(arr1);
	CString b(arr2);
	pointer1->TextOut(60, 40, a);
	pointer1->TextOut(60, 80, b);
}

void CwaveFormView::OnDraw(CDC* pointer1)
{
	WaveView* pointer2 = GetDocument();
	ASSERT_VALID(pointer2);
	CRect rect;
	char arr3[1000];
	sprintf_s(arr3, "Click here to LoadFile !!!");
	CString s2(arr3);
	pointer1->TextOut(1000, 40, s2);
	GetClientRect(&rect);
	if (pointer2->type != 0)
	{
		return;
	}
	else
	{
		drawWav(pointer1, pointer2);
	}
	
}

void CwaveFormView::OnLButtonDown(UINT nFlags, CPoint point)
{

	if (abs(point.x - 1100) < 124 )
	{
		if (abs(point.y - 30) < 30)
		{
			WaveView* pointer2 = GetDocument();
			pointer2->OnOpenwav();
		}
		WaveView* pointer2 = GetDocument();
		pointer2->OnOpenwav();
	}
}

