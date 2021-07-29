#pragma once

/**
 *	ini 설정 파일 class
 *	\warning 초기화시 fileName에 마지막 문자가 백슬러쉬일 경우 제대로 처리 안될수 있음
 *	\warning 경로 내에 디렉토리 이름과 같은 파일이 존재할 경우 프로그램 다운될수 있음
 */
class CIniFile
{
private:
	CString m_strFileName;
	CString m_strSection;
public:
	/**
	 * 생성자 메소드
	 * \param fileName ini 파일 이름
	 * 지정된 파일은 현재 실행 디렉토리에서 찾는다.
	 */
	CIniFile(CString fileName);
	virtual ~CIniFile(void);

	void selectSection(CString strSection);
	void deleteSection(const CString strSection);
	int GetAllSections(CStringArray& strArray);

	void write(CString strKey, int nValue);
	void write(CString strKey, CString strValue);
	void write(CString strSection, CString strKey, int nValue);
	void write(CString strSection, double fValue);
	void write(CString strSection, CString strKey, double dValue);
	void write(CString strSection, CString strkey, CString strValue);

	int read(CString strKey, int nDefault);
	CString read(CString strKey, CString nDefault);
	CString read(CString strSection, CString strKey, CString strDefault);
	int read(CString strSection, CString strKey, int nDefault);
	double read(CString strSection, double fDefault);
	double read(CString strSection, CString strKey, double fDefault);
	
	void clear(CString strSection);
	void clear(CString strSection, CString strKey);
	void clear();

	bool FindFile(CString sPath);
	bool CreateFile(CString sFileName);
	void SetPath(CString strFilePath);
	bool GetFileNames(CStringArray &arrModelName, CString strAddress/*=FILE_GLASS_MODEL_RECIPE*/);
};

