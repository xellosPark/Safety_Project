// INIRecipe.h: interface for the CINIRecipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIRECIPE_H__8E60165C_6460_470A_A61F_0B152C39D87E__INCLUDED_)
#define AFX_INIRECIPE_H__8E60165C_6460_470A_A61F_0B152C39D87E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/**
@author	:LG.PRI.WOOCHUL
@brief	: INI File In/Out class

-
-
-
@param		:
@return		:
@see	:
@date	:2010.8.18
*/



class CINIRecipe  
{
public:
	CINIRecipe();
	CINIRecipe(CString sFilePath);
	virtual ~CINIRecipe();

	void	Set(CString sFilePath);
	bool	FindFile(CString sPath);

	UINT	GetValueUI(CString sCategory,CString sFieldName,UINT uiDefault);
	int		GetValueI(CString sCategory,CString sFieldName,int iDefault);
	long	GetValueL(CString sCategory,CString sFieldName,long iDefault);
	double	GetValueD(CString sCategory,CString sFieldName,double dDefault);
	bool	GetValueB(CString sCategory,CString sFieldName,bool bDefault);
	CString GetValueS(LPCTSTR sCategory,LPCTSTR sFieldName,LPCTSTR sDefault);

	void SetValue(LPCTSTR sCategory,LPCTSTR sFieldName,LPCTSTR sValue);
	void SetValue(LPCTSTR sCategory,LPCTSTR sFieldName,double dValue);
	void SetValue(LPCTSTR sCategory,LPCTSTR sFieldName,int iValue);
//	void SetValue(CString sCategory,CString sFieldName,bool bValue);

	void Close();
	bool CreateFile(CString sPath);
	bool IsFloat(LPCTSTR pszText );
	bool _isfloatOp(char ch);

protected:
	CString m_sFilePath;
	bool	m_bFileFind;

	CFile	m_File;
};

#endif // !defined(AFX_INIRECIPE_H__8E60165C_6460_470A_A61F_0B152C39D87E__INCLUDED_)
