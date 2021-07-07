// INIRecipe.cpp: implementation of the CINIRecipe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INIRecipe.h"
#include "FileOperations.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINIRecipe::CINIRecipe(CString sFilePath)
{
	Set(sFilePath);
}

CINIRecipe::~CINIRecipe()
{	
	Close();
}


CINIRecipe::CINIRecipe()
{
	m_sFilePath.Empty();
	m_bFileFind = false;
}


void CINIRecipe::Set(CString sFilePath)
{
	m_sFilePath=sFilePath;
	if(!FindFile(sFilePath))
	{
		m_bFileFind = CreateFile(sFilePath);  //빈 INI File을 생성한다.
	}
	else
		m_bFileFind = true;

	if(!m_bFileFind)
		AfxMessageBox("FILE을 찾을수 없습니다.");
}


bool CINIRecipe::CreateFile(CString sFileName)
{
	Close();

	CString sFileFolder = _T("");
	int len= sFileName.GetLength();
	int N = -1;
	N= sFileName.ReverseFind('\\');
	if(N<=len && N>=0)
	{
		sFileFolder = sFileName.Left(N);
	}
	else
		return false;
	
	//CFile f;
	if(!m_File.Open(sFileName,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
	{
		CFileOperation fFinder;
		if (!fFinder.FindFile(sFileFolder,0))
		{
			fFinder.MakeFullDir(sFileFolder);
		}
		if(!m_File.Open(sFileName,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
		{
			return false;
		}
	}
	m_File.SeekToEnd();
	
	CString szData; szData.Empty();
	m_File.Write(szData,szData.GetLength());
	return true;
}


void CINIRecipe::Close()
{
	if (INVALID_HANDLE_VALUE != (HANDLE)m_File)  // File 안 열렸다.
	{
		m_File.Close();
	}
}

bool CINIRecipe::FindFile(CString sPath)
{
	CFileFind FileFinder;
	if(!FileFinder.FindFile(sPath,0))
	{
		//CString sMsg;
		//sMsg.Format("INI Recipe File %s를 찾을수 없습니다.",sPath);
		//AfxMessageBox(sMsg);
		return false;
	}
	return true;
}


double CINIRecipe::GetValueD(CString sCategory,CString sFieldName,double dDefault)
{
	CString sDefault = _T("");
	sDefault.Format(_T("%.5f"),dDefault);
	CString sValue = GetValueS(sCategory,sFieldName,sDefault);
	if(IsFloat(sValue))
		return _tstof(sValue);
	else
		return dDefault;
}


int CINIRecipe::GetValueI(CString sCategory,CString sFieldName,int iDefault)
{
	CString sDefault = _T("");
	sDefault.Format(_T("%d"),iDefault);
	CString sValue = GetValueS(sCategory,sFieldName,sDefault);
	if(IsFloat(sValue))
		return _ttoi(sValue);
	else
		return iDefault;
}

long CINIRecipe::GetValueL(CString sCategory,CString sFieldName,long lDefault)
{
	CString sDefault = _T("");
	sDefault.Format(_T("%ld"),lDefault);
	CString sValue = GetValueS(sCategory,sFieldName,sDefault);
	if(IsFloat(sValue))
		return atol(sValue);
	else
		return lDefault;
}

UINT CINIRecipe::GetValueUI(CString sCategory,CString sFieldName,UINT uiDefault)
{
	CString sDefault = _T("");
	sDefault.Format(_T("%d"),uiDefault);
	CString sValue = GetValueS(sCategory,sFieldName,sDefault);
	if(IsFloat(sValue))
		return _ttoi(sValue);
	else
		return uiDefault;
}


bool CINIRecipe::GetValueB(CString sCategory,CString sFieldName,bool bDefault)
{
	CString sDefault = bDefault? _T("1") : _T("0");
	CString sValue = GetValueS(sCategory,sFieldName,sDefault);
	if(IsFloat(sValue))
		return _tstof(sValue)? true : false;
	else
		return bDefault;
}

CString CINIRecipe::GetValueS(LPCTSTR sCategory,LPCTSTR sFieldName,LPCTSTR sDefault)
{
	if(!m_bFileFind)
	{
		CString sMsg = _T("");
		sMsg.Format(_T("INI Recipe File %s를 찾을수 없습니다."),m_sFilePath);
		AfxMessageBox((LPCTSTR)sMsg);
		return sDefault;
	}
	CString sData = _T("");
	TCHAR tchTemp[255] = {0,};
	GetPrivateProfileString(sCategory,sFieldName,sDefault,tchTemp,255,m_sFilePath);

	sData.Format(_T("%s"), tchTemp);
	return sData; //WOOCHUL.09012.P8E MODIFY
}


void CINIRecipe::SetValue(LPCTSTR sCategory,LPCTSTR sFieldName,LPCTSTR sValue)
{
	if(!m_bFileFind)
	{
		CString sMsg = _T("");
		sMsg.Format(_T("INI Recipe File %s를 찾을수 없습니다."),m_sFilePath);
		AfxMessageBox(sMsg);
		return;
	}
	WritePrivateProfileString(sCategory,sFieldName,sValue,m_sFilePath);
}

void CINIRecipe::SetValue(LPCTSTR sCategory,LPCTSTR sFieldName,double dValue)
{
	CString sValue = _T("");
	sValue.Format(_T("%.6f"),dValue);
	SetValue(sCategory,sFieldName,sValue);
}

void CINIRecipe::SetValue(LPCTSTR sCategory,LPCTSTR sFieldName,int iValue)
{
	CString sValue = _T("");
	sValue.Format(_T("%d"),iValue);
	SetValue(sCategory,sFieldName,sValue);
}




bool CINIRecipe::IsFloat(LPCTSTR pszText )
{
//	ASSERT_VALID_STRING( pszText );

	for( int i = 0; i < lstrlen( pszText ); i++ )
		if( !_istdigit( pszText[ i ] ) &&  !_isfloatOp( pszText[ i ]))
			return false;

	return true;
}

bool CINIRecipe::_isfloatOp(char ch)
{
	if (ch == '.' || ch == '-' || ch == '+') return true;
	return false;
}