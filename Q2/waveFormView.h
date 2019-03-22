
class CWaveFormView : public CView
{
public:
	int drawBitmapMode = 0;
protected: 
	CWaveFormView();
	DECLARE_DYNCREATE(CWaveFormView)

public:
	WaveView* GetDocument() const;

public:
	void drawWav(CDC* pointer1, WaveView* pointer2);
public:
	virtual void OnDraw(CDC* pointer1);
	virtual BOOL PreCreateWindow(CREATESTRUCT& op);
protected:
public:
	virtual ~CWaveFormView();
protected:
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
