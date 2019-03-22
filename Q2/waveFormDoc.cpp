
#include "waveForm.h"
#include "waveFormDoc.h"
#include "waveFormView.h"
#include  <mmsystem.h>
#include  <atlconv.h >		
#include  <atlbase.h>
#include  <string>
#define ID_RIFF mmioFOURCC('R', 'I', 'F', 'F')
#define ID_WAVE mmioFOURCC('W', 'A', 'V', 'E')
#define ID_data mmioFOURCC('d', 'a', 't', 'a')
#define ID_fmt mmioFOURCC('f', 'm', 't', '\x20')
#define ID_fact mmioFOURCC('f', 'a', 'c', 't')

// WaveView

IMPLEMENT_DYNCREATE(WaveView, CDocument)

BEGIN_MESSAGE_MAP(WaveView, CDocument)
	ON_COMMAND(ID_OPENWAV, &WaveView::OnOpenwav)
	ON_COMMAND(ID_FILE_OPEN, &WaveView::OnOpenwav)
END_MESSAGE_MAP()



WaveView::WaveView()
{
	num=0;
	data=NULL;
	LData=NULL;
	RData=NULL;
	BytesPerSample=0;
	channel=0;

}

WaveView::~WaveView()
{
}

BOOL WaveView::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}


BOOL WaveView::OnOpenDocument(LPCTSTR PathName)
{
	if (!CDocument::OnOpenDocument(PathName))
		return FALSE;

	return TRUE;
}


void WaveView::Read_Wave(CString f)
{
	CFile file;
	file.Open(f, CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	unsigned long ChunkID, ChunkLength, dw;
	unsigned short b;
	unsigned short w;
	unsigned short fmtTag;
	unsigned short wBitsPerSample;
	unsigned long dwAvgBytesRate;
	unsigned long Len;
	ar >> ChunkID;
		ar >> dw >> ChunkID;
		ar >> ChunkID;
		ar >> ChunkLength;
		ar >> fmtTag;
		ar >> channel;
		ar >> dw;
		ar >> dwAvgBytesRate;
		ar >> w;
		ar >> wBitsPerSample;
	if (ChunkLength == 18)
	{
		ar >> w;
		for (int i = 0; i<w; i++)
		{
			ar >> b;
		}
	}
	ar >> ChunkID;
	if (ChunkID == ID_fact)
	{
		ar >> dw;
		ar >> dw;
		ar >> ChunkID;
	}
	if (ChunkID == ID_data)
	{
		ar >> Len;
		BytesPerSample = wBitsPerSample / 8;
		num = Len / BytesPerSample;
	}
	if (channel == 1)
	{
		data = new LONG[num];
		if (BytesPerSample == 1)
		{
			for (int i = 0; i<num; i++)
			{
				ar >> b;
				data[i] = b - 128;
			}
		}
		else if (BytesPerSample == 2)
		{
			for (int i = 0; i<num; i++)
			{
				ar >> w;
				data[i] = (SHORT)w;
			}
		}
		else if (BytesPerSample == 4)
		{
			for (int i = 0; i<num; i++)
			{
				ar >> dw;
				data[i] = (LONG)dw;	
			}
		}
		else if (BytesPerSample == 3)
		{
			for (int i = 0; i<num; i++)
			{
				ar >> b >> w;
				data[i] = w + b;
			}
		}
	}
	else if (channel == 2)
	{
		LData = new LONG[num / 2];
		RData = new LONG[num / 2];
		if (BytesPerSample == 1)
		{
			for (int i = 0; i<num / 2; i++)
			{
				ar >> b;
				LData[i] = b - 128;
				ar >> b;
				RData[i] = b - 128;
			}
		}
		else if (BytesPerSample == 2)
		{
			for (int i = 0; i<num / 2; i++)
			{
				ar >> w;
				LData[i] = (SHORT)w;
				ar >> w;
				RData[i] = (SHORT)w;
			}
		}
		else if (BytesPerSample == 4)
		{
			for (int i = 0; i<num / 2; i++)
			{
				ar >> dw;
				LData[i] = (LONG)dw;
				ar >> dw;
				RData[i] = (LONG)dw;
			}
		}
		else if (BytesPerSample == 3)
		{
			for (int i = 0; i<num / 2; i++)
			{
				ar >> b >> w;
				LData[i] = w + b;
				ar >> b >> w;
				RData[i] = w + b;
			}
		}
	}
	ar.Flush();	
	file.Close();
	if (channel == 1)
	{
		for (int j = 0; j<num; j++)
		{
			if (data[j]>maxValue)
			{
				maxValue = data[j];
			}
			if (data[j]<minValue)
			{
				minValue = data[j];
			}
		}
	}
	else {
		for (int j = 0; j<num / 2; j++)
		{
			if (LData[j]>maxValue)
			{
				maxValue = LData[j];
			}
			if (RData[j]>maxValue)
			{
				maxValue = RData[j];
			}
			if (LData[j]<minValue)
			{
				minValue = LData[j];
			}
			if (RData[j]<minValue)
			{
				minValue = RData[j];
			}
		}

	}

	CMainFrame *Mainfrm = (CMainFrame*)AfxGetMainWnd();
	Mainfrm->GetActiveView()->Invalidate();
	PlaySound(f, NULL, SND_ASYNC);
}
