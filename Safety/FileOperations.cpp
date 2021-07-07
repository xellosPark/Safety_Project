/** \file	FileOperations.cpp
			Project: FopDemo\n
			Project type: MFC App\n
			Author: Vinnichenko Alexey\n
			E-mail: subj@mail.ru\n
			Description: Implementation of CFileOperation class and CFileExeption class.
*/ 

#include "stdafx.h" 
#include "FileOperations.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//************************************************************************************************************
CFExeption::CFExeption(DWORD dwErrCode)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			      NULL, dwErrCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	m_sError = (LPTSTR)lpMsgBuf;
	LocalFree(lpMsgBuf);
	m_dwError = dwErrCode;
}


CFExeption::CFExeption(CString sErrText)
{
	m_sError = sErrText;
	m_dwError = 0;
}


//************************************************************************************************************

CFileOperation::CFileOperation()
{
	Initialize();
}


void CFileOperation::Initialize()
{
	m_sError = _T("No error");
	m_dwError = 0;
	m_bAskIfReadOnly = true;
	m_bOverwriteMode = false;
	m_bAborted = false;
	m_iRecursionLimit = -1;
}


void CFileOperation::DoDelete(CString sPathName)
{
	CFileFind ff;
	CString sPath = sPathName;

	if (CheckPath(sPath) == PATH_IS_FILE)
	{
		if (!CanDelete(sPath)) 
		{
			m_bAborted = true;
			return;
		}
		if (!DeleteFile(sPath)) throw new CFExeption(GetLastError());
		return;
	}

	PreparePath(sPath);
	sPath += "*.*";

	BOOL bRes = ff.FindFile(sPath);
	while(bRes)
	{
		bRes = ff.FindNextFile();
		if (ff.IsDots()) continue;
		if (ff.IsDirectory())
		{
			sPath = ff.GetFilePath();
			DoDelete(sPath);
		}
		else DoDelete(ff.GetFilePath());
	}
	ff.Close();
	if (!RemoveDirectory(sPathName) && !m_bAborted) throw new CFExeption(GetLastError());
}


void CFileOperation::DoFolderCopy(CString sSourceFolder, CString sDestFolder, bool bDelteAfterCopy)
{
	CFileFind ff;
	CString sPathSource = sSourceFolder;
	BOOL bRes = ff.FindFile(sPathSource);
	while (bRes)
	{
		bRes = ff.FindNextFile();
		if (ff.IsDots()) continue;
		if (ff.IsDirectory()) // source is a folder
		{
			if (m_iRecursionLimit == 0) continue;
			sPathSource = ff.GetFilePath() + CString("\\") + CString("*.*");
			CString sPathDest = sDestFolder + ff.GetFileName() + CString("\\");
			if (CheckPath(sPathDest) == PATH_NOT_FOUND) 
			{
				if (!CreateDirectory(sPathDest, NULL))
				{
					ff.Close();
					throw new CFExeption(GetLastError());
				}
			}
			if (m_iRecursionLimit > 0) m_iRecursionLimit --;
			DoFolderCopy(sPathSource, sPathDest, bDelteAfterCopy);
		}
		else // source is a file
		{
			CString sNewFileName = sDestFolder + ff.GetFileName();
			DoFileCopy(ff.GetFilePath(), sNewFileName, bDelteAfterCopy);
		}
	}
	ff.Close();
}

//folder내의 file list를 얻는다.
//sub folder 는 제외
//WOOCHUL
bool CFileOperation::GetFileList(CString sSourceFolder, CString sExtension, CStringArray& sArFileList)
{
	sArFileList.RemoveAll();
	
	PreparePath(sSourceFolder);
	
	CString sFindPath;
	sFindPath.Format("%s*.%s",sSourceFolder,sExtension);

	CFileFind ff;
	BOOL bRes = ff.FindFile(sFindPath);
	if(!bRes)
	{
		ff.Close();
		return false;
	}


	while(bRes)
	{
		bRes = ff.FindNextFile();
		CString sFileName = ff.GetFileName();

		if (ff.IsDots()) continue;
		else if (ff.IsDirectory()) continue;// source is a folder
		else
		{
			sArFileList.Add(sFileName);
		}
	}

	ff.Close();

	return (sArFileList.GetSize()==0)?false:true;
}




bool CFileOperation::GetFileInfoList(CString sSourceFolder, CString sExtension, std::vector<_FILEINFO>& vFileInfo)
{
	vFileInfo.clear();
	
	PreparePath(sSourceFolder);
	
	CString sFindPath;
	sFindPath.Format("%s*.%s",sSourceFolder,sExtension);

	CFileFind ff;
	BOOL bRes = ff.FindFile(sFindPath);
	if(!bRes)
	{
		ff.Close();
		return false;
	}

	while(bRes)
	{
		bRes = ff.FindNextFile();

		_FILEINFO fInfo;

		if (ff.IsDots()) continue;
		else if (ff.IsDirectory()) continue;// source is a folder
		else
		{
			CTime time;
			fInfo.m_szFileName = ff.GetFileName();
			fInfo.m_szFilePath = ff.GetFilePath();
			
			ff.GetLastWriteTime(fInfo.m_WriteTime);
			
			fInfo.m_lFileSize = (long)ff.GetLength();

			vFileInfo.push_back(fInfo);
		}
	}

	ff.Close();
	return (vFileInfo.size()==0)?false:true;
}


bool CFileOperation::GetFileInfo(CString sFilePath,_FILEINFO& tFileInfo)
{
	CFileFind ff;

	if(!ff.FindFile(sFilePath))
	{
		ff.Close();
		return false;
	}

	ff.FindNextFile();

	if (ff.IsDots() || ff.IsDirectory()) return false;
	else
	{
		CTime time;
		tFileInfo.m_szFileName = ff.GetFileName();
		tFileInfo.m_szFilePath = ff.GetFilePath();
		ff.GetLastWriteTime(tFileInfo.m_WriteTime);
		tFileInfo.m_lFileSize = (long)ff.GetLength();
	}

	ff.Close();
	return true;
}

bool CFileOperation::Delete(CString sPathName)
{
	try
	{
		DoDelete(sPathName);
	}
	catch(CFExeption* e)
	{
		m_sError = e->GetErrorText();
		m_dwError = e->GetErrorCode();
		delete e;
		if (m_dwError == 0) return true;
		return false;
	}
	return true;
}


bool CFileOperation::Rename(CString sSource, CString sDest)
{
	try
	{
		DoRename(sSource, sDest);
	}
	catch(CFExeption* e)
	{
		m_sError = e->GetErrorText();
		m_dwError = e->GetErrorCode();
		delete e;
		return false;
	}
	return true;
}


void CFileOperation::DoRename(CString sSource, CString sDest)
{
	if (!MoveFile(sSource, sDest)) throw new CFExeption(GetLastError());
}


void CFileOperation::DoCopy(CString sSource, CString sDest, CString sDestName,  bool bDelteAfterCopy)
{
	CheckSelfRecursion(sSource, sDest);
	// source not found
	if (CheckPath(sSource) == PATH_NOT_FOUND)
	{
		CString sError = sSource + CString(" not found");
		throw new CFExeption(sError);
	}
	// dest not found
	if (CheckPath(sDest) == PATH_NOT_FOUND)
	{
		CString sError = sDest + CString(" not found");
		throw new CFExeption(sError);
	}
	// folder to file
	if (CheckPath(sSource) == PATH_IS_FOLDER && CheckPath(sDest) == PATH_IS_FILE) 
	{
		throw new CFExeption(_T("Wrong operation"));
	}
	// folder to folder
	if (CheckPath(sSource) == PATH_IS_FOLDER && CheckPath(sDest) == PATH_IS_FOLDER) 
	{
		CFileFind ff;
		CString sError = sSource + CString(" not found");
		PreparePath(sSource);
		PreparePath(sDest);
		sSource += "*.*";
		if (!ff.FindFile(sSource)) 
		{
			ff.Close();
			throw new CFExeption(sError);
		}
		if (!ff.FindNextFile()) 
		{
			ff.Close();
			throw new CFExeption(sError);
		}
		CString sFolderName = ParseFolderName(sSource);
		if (!sFolderName.IsEmpty()) // the source is not drive
		{
			sDest += sFolderName;
			PreparePath(sDest);
			MakeFullDir(sDest);
			// chan : 기존에 경로가 이미 있는경우 Exeption 으로 되므로
			// 경로가 없으면 생성하는 것으로...

// 			if (!CreateDirectory(sDest, NULL))
// 			{
// 				DWORD dwErr = GetLastError();
// 				if (dwErr != 183)
// 				{
// 					ff.Close();
// 					throw new CFExeption(dwErr);
// 				}
// 			}
		}
		ff.Close();
		DoFolderCopy(sSource, sDest, bDelteAfterCopy);
	}
	// file to file
	if (CheckPath(sSource) == PATH_IS_FILE && CheckPath(sDest) == PATH_IS_FILE) 
	{
		DoFileCopy(sSource, sDest);
	}
	// file to folder
	if (CheckPath(sSource) == PATH_IS_FILE && CheckPath(sDest) == PATH_IS_FOLDER) 
	{
		//PreparePath(sDest);
		//TCHAR drive[MAX_PATH], dir[MAX_PATH], name[MAX_PATH], ext[MAX_PATH];
		//_tsplitpath_s(sSource, drive, sizeof(drive), dir, sizeof(dir), name, sizeof(name), ext, sizeof(ext));
		//sDest = sDest + CString(name) + CString(ext);

		sDest += sDestName;
		DoFileCopy(sSource, sDest);
	}
}


void CFileOperation::DoFileCopy(CString sSourceFile, CString sDestFile, bool bDelteAfterCopy)
{
	BOOL bOvrwriteFails = FALSE;
	if (!m_bOverwriteMode)
	{
		while (IsFileExist(sDestFile)) 
		{
			sDestFile = ChangeFileName(sDestFile);
		}
		bOvrwriteFails = TRUE;
	}
	if (!CopyFile(sSourceFile, sDestFile, bOvrwriteFails)) 
		throw new CFExeption(GetLastError());
	if (bDelteAfterCopy)
	{
		DoDelete(sSourceFile);
	}
}


bool CFileOperation::Copy(CString sSource, CString sDest, CString sDestName)
{
	if (CheckSelfCopy(sSource, sDest)) return true;
	bool bRes;
	try
	{
		DoCopy(sSource, sDest, sDestName);
		bRes = true;
	}
	catch(CFExeption* e)
	{
		m_sError = e->GetErrorText();
		m_dwError = e->GetErrorCode();
		delete e;
		if (m_dwError == 0) bRes = true;
		bRes = false;
	}
	m_iRecursionLimit = -1;
	return bRes;
}


bool CFileOperation::Replace(CString sSource, CString sDest, CString sDestName)
{
	if (CheckSelfCopy(sSource, sDest)) return true;
	bool bRes;
	try
	{
		bool b = m_bAskIfReadOnly;
		m_bAskIfReadOnly = false;
		DoCopy(sSource, sDest, sDestName, true);
		DoDelete(sSource);
		m_bAskIfReadOnly = b;
		bRes = true;
	}
	catch(CFExeption* e)
	{
		m_sError = e->GetErrorText();
		m_dwError = e->GetErrorCode();
		delete e;
		if (m_dwError == 0) bRes = true;
		bRes = false;
	}
	m_iRecursionLimit = -1;
	return bRes;
}


CString CFileOperation::ChangeFileName(CString sFileName)
{
	CString sName, sNewName, sResult;
	TCHAR drive[MAX_PATH];
	TCHAR dir  [MAX_PATH];
	TCHAR name [MAX_PATH];
	TCHAR ext  [MAX_PATH];
	_tsplitpath_s((LPCTSTR)sFileName, drive, sizeof(drive), dir, sizeof(dir), name, sizeof(name), ext, sizeof(ext));
	sName = name;

	int pos = sName.Find(_T("Copy "));
	if (pos == -1)
	{
		sNewName = CString(_T("Copy of ")) + sName + CString(ext);
	}
	else
	{
		int pos1 = sName.Find('(');
		if (pos1 == -1)
		{
			sNewName = sName;
			sNewName.Delete(0, 8);
			sNewName = CString("Copy (1) of ") + sNewName + CString(ext);
		}
		else
		{
			CString sCount;
			int pos2 = sName.Find(')');
			if (pos2 == -1)
			{
				sNewName = CString("Copy of ") + sNewName + CString(ext);
			}
			else
			{
				sCount = sName.Mid(pos1 + 1, pos2 - pos1 - 1);
				sName.Delete(0, pos2 + 5);
				int iCount = _ttoi((LPCTSTR)sCount);
				iCount ++;
				sNewName.Format(_T("%s%d%s%s%s"), _T("Copy ("), iCount, _T(") of "), (LPCTSTR)sName, ext);
			}
		}
	}

	sResult = CString(drive) + CString(dir) + sNewName;

	return sResult;
}


bool CFileOperation::IsFileExist(CString sPathName)
{
	HANDLE hFile;
	hFile = CreateFile(sPathName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return false;
	CloseHandle(hFile);
	return true;
}


int CFileOperation::CheckPath(CString sPath)
{
	DWORD dwAttr = GetFileAttributes(sPath);
	if (dwAttr == 0xffffffff) 
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND || GetLastError() == ERROR_PATH_NOT_FOUND) 
			return PATH_NOT_FOUND;
		return PATH_ERROR;
	}
	if (dwAttr & FILE_ATTRIBUTE_DIRECTORY) return PATH_IS_FOLDER;
	return PATH_IS_FILE;
}


void CFileOperation::PreparePath(CString &sPath)
{
	if(sPath.Right(1) != "\\") sPath += "\\";
}


bool CFileOperation::CanDelete(CString sPathName)
{
	DWORD dwAttr = GetFileAttributes(sPathName);
	if (dwAttr == -1) return false;
	if (dwAttr & FILE_ATTRIBUTE_READONLY)
	{
		if (m_bAskIfReadOnly)
		{
			CString sTmp = sPathName;
			int pos = sTmp.ReverseFind('\\');
			if (pos != -1) sTmp.Delete(0, pos + 1);
			CString sText = sTmp + CString(" is read olny. Do you want delete it?");
			int iRes = MessageBox(NULL, sText, _T("Warning"), MB_YESNOCANCEL | MB_ICONQUESTION);
			switch (iRes)
			{
				case IDYES:
				{
					if (!SetFileAttributes(sPathName, FILE_ATTRIBUTE_NORMAL)) return false;
					return true;
				}
				case IDNO:
				{
					return false;
				}
				case IDCANCEL:
				{
					m_bAborted = true;
					throw new CFExeption(0);
					return false;
				}
			}
		}
		else
		{
			if (!SetFileAttributes(sPathName, FILE_ATTRIBUTE_NORMAL)) return false;
			return true;
		}
	}
	return true;
}


CString CFileOperation::ParseFolderName(CString sPathName)
{
	CString sFolderName = sPathName;
	int pos = sFolderName.ReverseFind('\\');
	if (pos != -1) sFolderName.Delete(pos, sFolderName.GetLength() - pos);
	pos = sFolderName.ReverseFind('\\');
	if (pos != -1) sFolderName = sFolderName.Right(sFolderName.GetLength() - pos - 1);
	else sFolderName.Empty();
	return sFolderName;
}


void CFileOperation::CheckSelfRecursion(CString sSource, CString sDest)
{
	if (sDest.Find(sSource) != -1)
	{
		int i = 0, count1 = 0, count2 = 0;
		for(i = 0; i < sSource.GetLength(); i ++)	if (sSource[i] == '\\') count1 ++;
		for(i = 0; i < sDest.GetLength(); i ++)	if (sDest[i] == '\\') count2 ++;
		if (count2 >= count1) m_iRecursionLimit = count2 - count1;
	}
}


bool CFileOperation::CheckSelfCopy(CString sSource, CString sDest)
{
	bool bRes = false;
	if (CheckPath(sSource) == PATH_IS_FOLDER)
	{
		CString sTmp = sSource;
		int pos = sTmp.ReverseFind('\\');
		if (pos != -1)
		{
			sTmp.Delete(pos, sTmp.GetLength() - pos);
			if (sTmp.CompareNoCase(sDest) == 0) bRes = true;
		}
	}
	return bRes;
}

void CFileOperation::MakeFullDir(CString& szDir)
{
	CString szTmp;
	CString szMakeDir;
	CFileFind fFind;
	int iIndex = 1;


	if (!fFind.FindFile(szDir))
	{
		for(;;)
		{
			if (iIndex == 1)  /*It includes driver chanracter like C:\\*/
			{
				if (ReturnParameter(szDir,'\\',iIndex++,szTmp))
				{
					szMakeDir = szTmp + _T("\\");
					continue;
				}
			}
			if (ReturnParameter(szDir,'\\',iIndex++,szTmp))
			{
				szMakeDir += szTmp + _T("\\");
				if (!fFind.FindFile(szMakeDir))
				{
					if (!::CreateDirectory(szMakeDir,NULL))
					{
					}
				}
			}
			else break;
		}
	}
}

BOOL CFileOperation::ReturnParameter(CString& szOrigin, char cDelimeter, int nOrder,CString &szReturn)
{
	int iStartPos,iEndPos;
	int nFind;
	CString szTarget;
	int i = 0;
	char szErr[100];

	iStartPos = 0;
	while(1)
	{
		iEndPos =  szOrigin.Find(cDelimeter,iStartPos);
		if (i == nOrder-1)
		{
			break;
		}
		else
		{
			if (iEndPos == -1)
			{
				return FALSE;
			}
			iStartPos = iEndPos+1;
			i++;
		}
	}
	if (iEndPos == -1)
	{
		iEndPos = szOrigin.GetLength();
	}
	szReturn =  szOrigin.Mid(iStartPos,iEndPos - iStartPos);
	szReturn.TrimLeft();
	return TRUE;
}

bool CFileOperation::isExistFile(CString& str)
{
	return isExistFile(str.GetBuffer());
}

bool CFileOperation::isExistFile(TCHAR *str)
{
	HANDLE hFind;

	WIN32_FIND_DATA FindFileData;
	hFind = FindFirstFile(str, &FindFileData);

	if(hFind == INVALID_HANDLE_VALUE)
		return false;
	else
	{
		FindClose(hFind);
		int n = GetFileAttributes(str);
		if(n & FILE_ATTRIBUTE_DIRECTORY)
			return false;
		else
			return true;
	}
}


bool CFileOperation::DeleteFile(CString &strFolder)
{
	int nResult;
	SHFILEOPSTRUCT FileOp = {0};
	char szTemp[MAX_PATH];
	_tcscpy_s(szTemp, strFolder);
	szTemp[strlen(strFolder) + 1] = NULL;

	FileOp.hwnd = NULL;
	FileOp.wFunc = FO_DELETE;
	FileOp.pFrom = szTemp;
	FileOp.pTo = NULL;
	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI;
	FileOp.fAnyOperationsAborted = FALSE;
	FileOp.lpszProgressTitle = NULL;
	nResult = SHFileOperation(&FileOp);
	if (FileOp.fAnyOperationsAborted || nResult)
		nResult = 0;
	else
		nResult = 1;

	return nResult? true : false;
}


void CFileOperation::FindAndMoveFile(CString strSrcPath,CString strName,CString strDestPath)
{
	CString strTemp = strSrcPath + strName;

	CFileFind fFinder;
	BOOL bWorking = fFinder.FindFile((LPCTSTR)strTemp);

	while(bWorking)
	{
		bWorking = fFinder.FindNextFile();

		CString strFileName = fFinder.GetFileName();

		CString strSrc = strSrcPath + strFileName;
		CString strDest = strDestPath + strFileName;

		::MoveFile(strSrc,strDest);
	}

	fFinder.Close();
}

void CFileOperation::FindAndCopyFile(CString strSrcPath,CString strName,CString strDestPath)
{
	CString strTemp = strSrcPath + strName;

	CFileFind fFinder;
	BOOL bWorking = fFinder.FindFile((LPCTSTR)strTemp);

	while(bWorking)
	{
		bWorking = fFinder.FindNextFile();

		CString strFileName = fFinder.GetFileName();

		CString strSrc = strSrcPath + strFileName;
		CString strDest = strDestPath + strFileName;

		::CopyFile(strSrc,strDest,FALSE);	// FALSE이면 기존파일이 존재할 경우 덮어쓴다
	}

	fFinder.Close();
}

bool CFileOperation::FindFile(CString sSource,DWORD dwUnused /*= 0*/)
{
	CFileFind fFinder;
	return fFinder.FindFile((LPCTSTR)sSource,dwUnused)? true : false;
}