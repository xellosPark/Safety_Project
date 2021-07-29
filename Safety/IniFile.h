#pragma once

/**
 *	ini ���� ���� class
 *	\warning �ʱ�ȭ�� fileName�� ������ ���ڰ� �齽������ ��� ����� ó�� �ȵɼ� ����
 *	\warning ��� ���� ���丮 �̸��� ���� ������ ������ ��� ���α׷� �ٿ�ɼ� ����
 */
class CIniFile
{
private:
	CString m_strFileName;
	CString m_strSection;
public:
	/**
	 * ������ �޼ҵ�
	 * \param fileName ini ���� �̸�
	 * ������ ������ ���� ���� ���丮���� ã�´�.
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

