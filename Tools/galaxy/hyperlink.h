/*
 * Module ID: hyperlink.h
 * Title    : CHyperLink Declaration.
 *
 * Author   : Olivier Langlois <olivier@olivierlanglois.net>
 * Date     : November 15, 2005
 *
 * To read the article describing this class, visit
 * http://www.olivierlanglois.net/hyperlinkdemo.htm
 *
 * Note: Strongly inspired by Neal Stublen code
 *       Minor ideas come from Chris Maunder and Paul DiLascia code
 *
 * Revision :
 *
 * 001        26-Nov-2005 - Olivier Langlois
 *            - Added changes to make CHyperLink compatible with UNICODE
 *            - Use dynamic memory allocation for the URL string
 */

#ifndef   _HYPERLINK_H_
#define   _HYPERLINK_H_

#include "windows.h"

class CHyperLink
{
public:
    CHyperLink(void);
    virtual ~CHyperLink(void);

    BOOL ConvertStaticToHyperlink(HWND hwndCtl, LPCTSTR strURL);
    BOOL ConvertStaticToHyperlink(HWND hwndParent, UINT uiCtlId, LPCTSTR strURL);

	BOOL setURL( LPCTSTR strURL);
	LPCTSTR getURL(void) const { return m_strURL; }

protected:
	/*
	 * Override if you want to perform some action when the link has the focus
	 * or when the cursor is over the link such as displaying the URL somewhere.
	 */
	virtual void OnSelect(void)   {}
	virtual void OnDeselect(void) {}

	LPTSTR   m_strURL;                              // hyperlink URL

private:
	static COLORREF g_crLinkColor, g_crVisitedColor;// Hyperlink colors
	static HCURSOR  g_hLinkCursor;                  // Cursor for hyperlink
	static HFONT    g_UnderlineFont;                // Font for underline display
	static int      g_counter;						// Global resources user counter
    BOOL     m_bOverControl;                        // cursor over control?
    BOOL     m_bVisited;                            // Has it been visited?
    HFONT    m_StdFont;                             // Standard font
	WNDPROC  m_pfnOrigCtlProc;

	void createUnderlineFont(void);
	static void createLinkCursor(void);
    void createGlobalResources(void)
	{
		createUnderlineFont();
		createLinkCursor();
	}
	static void destroyGlobalResources(void)
	{
		/*
		 * No need to call DestroyCursor() for cursors acquired through
		 * LoadCursor().
		 */
		g_hLinkCursor   = NULL;
		DeleteObject(g_UnderlineFont);
		g_UnderlineFont = NULL;
	}

	void Navigate(void);

	static void DrawFocusRect(HWND hwnd);
    static LRESULT CALLBACK _HyperlinkParentProc(HWND hwnd, UINT message,
		                                         WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK _HyperlinkProc(HWND hwnd, UINT message,
		                                   WPARAM wParam, LPARAM lParam);
};

class CDemoLink : public CHyperLink
{
protected:
	virtual void OnSelect(void)
	{ ((CFrameWnd *)AfxGetMainWnd())->SetMessageText(m_strURL); }
	virtual void OnDeselect(void)
	{ ((CFrameWnd *)AfxGetMainWnd())->SetMessageText(AFX_IDS_IDLEMESSAGE); }
};
/*
 * class CHyperLinkDlg
 */
class CHyperLinkDlg : public CDialog
{
public:
	CHyperLinkDlg(UINT nIDTemplate) : CDialog(nIDTemplate) {}
protected:
/******************************************************************************
 *
 * Name      : setURL
 *
 * Purpose   : Convert the static control id and load URL string from
 *             resource associated with id.
 *
 * Parameters:
 *     ctr     (CHyperLink &) Reference to the hyperlink object to setup.
 *     id      (int)          Static control ID and URL String ID.
 *
 * Return value : None.
 *
 ****************************************************************************/
	void setURL(CHyperLink &ctr, int id);
};

#endif /* _HYPERLINK_H_ */
