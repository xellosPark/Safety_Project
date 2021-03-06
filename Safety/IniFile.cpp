#include "StdAfx.h"
#include "IniFile.h"
#include "FileOperations.h"

#define LONG_STRING_BUF_SIZE	1024
#define SHORT_STRING_BUF_SIZE	64

CIniFile::CIniFile(CString fileName)
{
	SetPath(fileName);
}

CIniFile::~CIniFile(void)
{
}
void CIniFile::SetPath(CString strFilePath)
{
	CFileFind FileFinder;
	m_strFileName = strFilePath;
	if(!FileFinder.FindFile(strFilePath))
	{
		CreateFile(strFilePath);  //빈 INI File을 생성한다.
	}

}
bool CIniFile::CreateFile(CString sFileName)
{
	CString sFileFolder;
	int len= sFileName.GetLength();
	int N = -1;
	N= sFileName.ReverseFind('\\');
	if(N<=len&&N>=0)
	{
		sFileFolder = sFileName.Left(N);
	}

	FILE *p_file = NULL;
	if ((p_file = _wfopen(sFileName,L"wt+,ccs=UTF-16LE")) == NULL) // C4996
	{
		CFileFind fFinder;
		if (!fFinder.FindFile(sFileFolder,0))
		{
			CFileOperation file;
			file.MakeFullDir(sFileFolder);
		}
		if(!_wfopen(sFileName,L"wt+,ccs=UTF-16LE"))
		{
			return false;
		}
	}

	fclose(p_file);
	return true;
}

bool CIniFile::FindFile(CString sPath)
{
	CFileFind FileFinder;
	if(!FileFinder.FindFile(sPath,0))
	{
		//CString sMsg;
		//sMsg.Format("INI Recipe File %s를 찾을수 없습니다.",sPath);
		//AfxMessageBox(sMsg, MB_TOPMOST);
		return false;
	}
	return true;
}

bool CIniFile::GetFileNames(CStringArray &arrModelName, CString strAddress/*=FILE_GLASS_MODEL_RECIPE*/)
{
	CFileFind FileFinder;
	CString strRcpPath;
	strRcpPath.Format(_T("%s%s"), strAddress, _T("*.*"));

	BOOL bFind = FileFinder.FindFile(strRcpPath);

	if(!bFind)
	{
		return false;
	}

	while(bFind)
	{
		bFind = FileFinder.FindNextFile();
		if(!FileFinder.IsDirectory() && !FileFinder.IsDots())
		{
			CString strFileName = FileFinder.GetFileTitle();
			arrModelName.Add(strFileName);
		}
	}

	return true;
}

void CIniFile::selectSection(CString strSection)
{
	m_strSection = strSection;
}

void CIniFile::deleteSection(const CString strSection) 
{
	WritePrivateProfileString(strSection,NULL,NULL,(LPCTSTR)m_strFileName);	
}

int CIniFile::GetAllSections(CStringArray& strArray)
{
	strArray.RemoveAll();

	TCHAR szBuf[LONG_STRING_BUF_SIZE],szSect[SHORT_STRING_BUF_SIZE];

	int iCnt = GetPrivateProfileSectionNames(szBuf,LONG_STRING_BUF_SIZE,m_strFileName);

	for(int i = 0; i < iCnt;)
	{
		_tcscpy_s(szSect,SHORT_STRING_BUF_SIZE,szBuf + i);
		i += _tcslen(szSect) + 1;

		strArray.Add(szSect);
	}
	
	return strArray.GetSize();
}

void CIniFile::write(CString strKey, int nValue)
{
	CString strTemp;
	strTemp.Format(_T("%d"), nValue);
	WritePrivateProfileString((LPCTSTR)m_strSection, (LPCTSTR)strKey, (LPCTSTR)strTemp, (LPCTSTR)m_strFileName);
}
void CIniFile::write(CString strSection, CString strKey, int nValue)
{
	CString strTemp;
	strTemp.Format(_T("%d"), nValue);
	WritePrivateProfileString((LPCTSTR)strSection, (LPCTSTR)strKey, (LPCTSTR)strTemp, (LPCTSTR)m_strFileName);
}

void CIniFile::write(CString strSection, CString strKey, double dValue)
{
	CString strTemp;
// 	strTemp.Format(_T("%.17f"), dValue);
	strTemp.Format(_T("%.10f"), dValue);
	WritePrivateProfileString((LPCTSTR)strSection, (LPCTSTR)strKey, (LPCTSTR)strTemp, (LPCTSTR)m_strFileName);
}

void CIniFile::write(CString strKey, CString strValue)
{
	WritePrivateProfileString((LPCTSTR)m_strSection, (LPCTSTR)strKey, (LPCTSTR)strValue, (LPCTSTR)m_strFileName);
}

void CIniFile::write(CString strKey, double fValue)
{
	CString strTemp;
// 	strTemp.Format(_T("%.17f"), fValue);
	strTemp.Format(_T("%.10f"), fValue);
	WritePrivateProfileString((LPCTSTR)m_strSection, (LPCTSTR)strKey, (LPCTSTR)strTemp, (LPCTSTR)m_strFileName);
}

void CIniFile::write(CString strSection, CString strKey, CString strValue)
{
// 	CString strTemp;
// 	strTemp.Format(_T("%d"), nValue);
// 	WCHAR wTemp[100]=L"追加点检者";
// 	WritePrivateProfileString((LPCTSTR)m_strSection, (LPCTSTR)strKey, wTemp, (LPCTSTR)m_strFileName);
	WritePrivateProfileString((LPCTSTR)strSection, (LPCTSTR)strKey, (LPCTSTR)strValue, (LPCTSTR)m_strFileName);
}

int CIniFile::read(CString strKey, int nDefault)
{
	return GetPrivateProfileInt((LPCTSTR)m_strSection, (LPCTSTR)strKey, nDefault, (LPCTSTR)m_strFileName);
}

int CIniFile::read(CString strSection, CString strKey, int nDefault)
{
	return GetPrivateProfileInt((LPCTSTR)strSection, (LPCTSTR)strKey, nDefault, (LPCTSTR)m_strFileName);
}

double CIniFile::read(CString strSection, CString strKey, double fDefault)
{
	TCHAR buffer[100];
	CString strDefault;
	strDefault.Format(_T("%.17f"), fDefault);
	GetPrivateProfileString((LPCTSTR)strSection, (LPCTSTR)strKey, (LPCTSTR)strDefault, buffer, sizeof(buffer), (LPCTSTR)m_strFileName);

	TCHAR* stopstring;
	return _tcstod(buffer,&stopstring);
}

CString CIniFile::read(CString strKey, CString strDefault)
{
	TCHAR buffer[100];
	GetPrivateProfileString((LPCTSTR)m_strSection, (LPCTSTR)strKey, (LPCTSTR)strDefault, buffer, sizeof(buffer), (LPCTSTR)m_strFileName);
	return CString(buffer);
}

CString CIniFile::read(CString strSection, CString strKey, CString strDefault)
{
	TCHAR buffer[100];
	GetPrivateProfileString((LPCTSTR)strSection, (LPCTSTR)strKey, (LPCTSTR)strDefault, buffer, sizeof(buffer), (LPCTSTR)m_strFileName);
	return CString(buffer);
}

double CIniFile::read(CString strKey, double fDefault)
{
	TCHAR buffer[100];
	CString strDefault;
	strDefault.Format(_T("%.17f"), fDefault);
	GetPrivateProfileString((LPCTSTR)m_strSection, (LPCTSTR)strKey, (LPCTSTR)strDefault, buffer, sizeof(buffer), (LPCTSTR)m_strFileName);

	TCHAR* stopstring;
	return _tcstod(buffer,&stopstring);
}


void CIniFile::clear(CString strSection, CString strKey)
{
	WritePrivateProfileString((LPCTSTR)strSection,  (LPCTSTR)strKey, NULL, (LPCTSTR)m_strFileName);
}


void CIniFile::clear(CString strSection)
{
	WritePrivateProfileString((LPCTSTR)strSection,  NULL, NULL, (LPCTSTR)m_strFileName);
}

void CIniFile::clear()
{
	WritePrivateProfileString((LPCTSTR)m_strSection,  NULL, NULL, (LPCTSTR)m_strFileName);
}