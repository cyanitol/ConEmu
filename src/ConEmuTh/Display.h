
/*
Copyright (c) 2010 Maximus5
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

struct CeFullPanelInfo
{
	DWORD cbSize;
	HWND  hView;
	//HANDLE hPanel;
	PanelViewMode PVM;
	ThumbSizes Spaces;
	wchar_t sFontName[32]; // Tahoma
	int nFontHeight; // 14
	//
	int nWholeW, nWholeH; // ���������������� ��� ������ Paint
	int nXCountFull; // ��� �����, ����� ������ �� �����������
	int nXCount; // � ��� ����������� ����������� ����� ����� ������
	int nYCountFull; // ��� �����, ����� ������ �� �����������
	int nYCount; // � ��� ����������� ����������� ������� ����� ������
	//
	DWORD nFarInterfaceSettings;
	DWORD nFarPanelSettings;
	BOOL  bLeftPanel, bPlugin;
	BOOL IsFilePanel;
	int PanelMode; // 0..9 - ������� ����� ������.
	BOOL Visible;
	BOOL ShortNames;
	BOOL Focus;
	RECT  PanelRect;
	RECT  WorkRect; // "�������" �������������. ��� ���������� ����� �����
	int ItemsNumber;
	// 
	int CurrentItem;
	int TopPanelItem;
	// ��� �� ����� ��������� ��� ��������� Synchro
	bool bRequestItemSet;
	int ReqCurrentItem;
	int ReqTopPanelItem;
	//
	int OurTopPanelItem; // �� ����� �� ��������� � ���������, ����� CurrentItem ��� ���� �����
	DWORD Flags; // CEPANELINFOFLAGS
	// ************************
	int nMaxFarColors;
	BYTE *nFarColors; // ������ ������ ����
	COLORREF crLastBackBrush;
	HBRUSH hLastBackBrush;
	// ************************
	int nMaxPanelDir;
	wchar_t* pszPanelDir;
	// ************************
	int nMaxItemsNumber;
	CePluginPanelItem** ppItems;
	CePluginPanelItemColor* pItemColors;
	MSection* pSection;
	// ************************
	int nFarTmpBuf;    // ��������� ����� ��� ���������
	LPVOID pFarTmpBuf; // ���������� �� �������� ������


	int RegisterPanelView();
	int UnregisterPanelView();
	void Close();
	HWND CreateView();
	BOOL ReallocItems(int anCount);
	void FinalRelease();

	// ��� "����������" ������� ���������� �� �������� ����, ��� ����� ������� FAR Api
	void DisplayReloadPanel();

	// ��� ������� Safe-thread - �� ����� ������� �� ����� ����
	void RequestSetPos(int anCurrentItem, int anTopItem, BOOL abSetFocus = FALSE);

	static LRESULT CALLBACK DisplayWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static DWORD WINAPI DisplayThread(LPVOID lpvParam);
	int CalcTopPanelItem(int anCurrentItem, int anTopItem);
	void Invalidate();
	static void InvalidateAll();
	void Paint(HWND hwnd, PAINTSTRUCT& ps, RECT& rc);
	BOOL PaintItem(HDC hdc, int nIndex, int x, int y, CePluginPanelItem* pItem, CePluginPanelItemColor* pItemColor,
		BOOL abCurrentItem, BOOL abSelectedItem,
		/*COLORREF *nBackColor, COLORREF *nForeColor, HBRUSH *hBack,*/
		/*BOOL abAllowPreview,*/ HBRUSH hBackBrush, HBRUSH hPanelBrush, COLORREF crPanelColor);
	int DrawItemText(HDC hdc, LPRECT prcText, LPRECT prcMaxText, CePluginPanelItem* pItem, LPCWSTR pszComments, HBRUSH hBr, BOOL bIgnoreFileDescription);
	BOOL OnSettingsChanged(BOOL bInvalidate);
	BOOL GetIndexFromWndCoord(int x, int y, int &rnIndex);
	BOOL GetConCoordFromIndex(int nIndex, COORD& rCoord);
	HBRUSH GetItemColors(int nIndex, CePluginPanelItem* pItem, CePluginPanelItemColor* pItemColor, BOOL abCurrentItem, COLORREF &crFore, COLORREF &crBack);
	void LoadItemColors(int nIndex, CePluginPanelItem* pItem, CePluginPanelItemColor* pItemColor, BOOL abCurrentItem, BOOL abStrictConsole);
	// Conversions
	BOOL FarItem2CeItem(int anIndex,
		const wchar_t*   asName,
		const wchar_t*   asDesc,
		DWORD            dwFileAttributes,
		FILETIME         ftLastWriteTime,
		unsigned __int64 anFileSize,
		BOOL             abVirtualItem,
		DWORD_PTR        apUserData,
		DWORD            anFlags,
		DWORD            anNumberOfLinks);

	/*{
	if (ppItems) {
	for (int i=0; i<ItemsNumber; i++)
	if (ppItems[i]) free(ppItems[i]);
	free(ppItems);
	ppItems = NULL;
	}
	nMaxItemsNumber = 0;
	if (pszPanelDir) {
	free(pszPanelDir);
	pszPanelDir = NULL;
	}
	nMaxPanelDir = 0;
	if (nFarColors) {
	free(nFarColors);
	nFarColors = NULL;
	}
	nMaxFarColors = 0;
	if (pFarTmpBuf) {
	free(pFarTmpBuf);
	pFarTmpBuf = NULL;
	}
	nFarTmpBuf = 0;
	}*/
};
