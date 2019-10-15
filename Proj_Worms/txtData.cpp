#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{

}

HRESULT txtData::init()
{

	return S_OK;
}

void txtData::release()
{

}


//세이브
void txtData::txtSave(const char* saveFileName, vector<string> vStr)
{
	HANDLE file;
	DWORD write;

	char str[128];

	strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	file = CreateFile(saveFileName, GENERIC_WRITE, FALSE, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);
}

char* txtData::vectorArrayCombine(vector<string> vArray)			
{
	char str[128];

	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		//100,100,100,100
		strncat_s(str, 128, vArray[i].c_str(), 126);
		if (i + 1 < vArray.size()) strcat(str, ",");
	}

	return str;
}


//로드
vector<string> txtData::txtLoad(const char* loadFileName)	 
{
	HANDLE file;

	char str[128];
	DWORD read;

	file = CreateFile(loadFileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 128, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	char* separator = ",";
	char* token;

	token = strtok(charArray, separator);

	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}
