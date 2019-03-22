
class WaveView : public CDocument
{
protected:
	WaveView();
	DECLARE_DYNCREATE(WaveView)


public:
	int num;
	int type=0;	
	LONG maxValue = 0, minValue = 0;
	
	LONG* data;	
	LONG *LData,*RData;	
	unsigned short BytesPerSample,channel;



public:
	void Read_Wave(CString f);
	
public:
	virtual BOOL OnNewDocument();

public:
	virtual ~WaveView();
protected:

public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};


