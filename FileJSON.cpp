#include "FileJSON.h"

bool MFileJSON::CheckValue(const char* Key, const char* SubKey, unsigned char Type)
{
	Result = false;
	
	if(Type == JSNT_NONE || Type > JSNT_ARRAY)
	{
		printf("Wrong value type\n");
		return false;
	}
	if(m_Document.IsNull())
	{
		printf("Null Document\n");
		return false;
	}
	
	rapidjson::Value* DocValue;
	if(!m_Document.HasMember(Key))
	{
		printf("Can not find primary member\n");
		return false;
	}
	if(strlen(SubKey))
	{
		if(!m_Document[Key].HasMember(SubKey))
		{
			printf("Can not find secondary member\n");
			return false;
		}
		DocValue = &m_Document[Key][SubKey];
	}
	else DocValue = &m_Document[Key];
    
    switch(Type)
	{
		case JSNT_INT:
			if(!DocValue->IsNumber() || !DocValue->IsInt())
			{
				printf("Check failed (int)");
				return false;
			}
			break;
		case JSNT_BOOL:
			if(!DocValue->IsBool())
			{
				printf("Check failed (bool)");
				return false;
			}
			break;
		case JSNT_DOUBLE:
			if(!DocValue->IsNumber() || !DocValue->IsDouble())
			{
				printf("Check failed (double)");
				return false;
			}
			break;
		case JSNT_ARRAY:
			if(!DocValue->IsArray())
			{
				printf("Check failed (array)");
				return false;
			}
			break;
	}
	
	return true;
}

MFileJSON::MFileJSON()
{
	jsonBuffer = NULL;
}

bool MFileJSON::Read(const char* FileName)
{
	int ReadSize = 0;
    struct stat FileStat;
    int Handle = -1;
    if(stat(FileName, &FileStat) == -1)
	{
		printf("Can not get file stats.\n");
		return false;
	}
	if(!FileStat.st_size)
	{
		printf("Empty file.\n");
		return false;
	}
    jsonBuffer = new char [FileStat.st_size + 1];
    memset(jsonBuffer, 0, FileStat.st_size + 1);
    Handle = open(FileName, O_RDONLY | O_BINARY);
    if(Handle != -1)
    {
    	ReadSize = read(Handle, jsonBuffer, FileStat.st_size);
    	close(Handle);
    	
    	if(ReadSize == FileStat.st_size)
    	{
    		if(!m_Document.ParseInsitu(jsonBuffer).HasParseError())
    		{
    			if(!m_Document.IsObject())
    			{
    				printf("Wrong config structure\n");
    				return false;
				}
			}
			else
			{
				printf("Error: %s\n", GetParseError_En(m_Document.GetParseError()));
				return false;
			}
		}
		else
		{
			printf("Error while read file\n");
			return false;
		}
	}
	else
	{
		printf("Can not open file\n");
		return false; 
	}
	
	return true;
}

bool MFileJSON::Write(const char* FileName)
{
	if(!FileName)
	{
		printf("Empty file name\n");
		return false;
	}
	if(m_Document.IsNull() || jsonBuffer == NULL)
	{
		printf("NULL document");
		return false;
	}
		
	rapidjson::StringBuffer SB;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> Writer(SB);
	if(!m_Document.Accept(Writer))
	{
		printf("Can not accept writer\n");
		return false;
	}
	
	int Handle = -1;
	int WriteSize = 0;
	Handle = open(FileName, O_RDWR | O_BINARY | O_TRUNC);
	if(Handle != -1)
	{
		WriteSize = write(Handle, SB.GetString(), strlen(SB.GetString()));
		if(WriteSize != strlen(SB.GetString())) printf("Write failed");
		close(Handle);
	}
	else
	{
		printf("Can not open file\n");
		return false;
	}
	
	return true;
}

bool MFileJSON::GetValue(const char* Key, int& Value)
{
	Result = CheckValue(Key, "", JSNT_INT);
	if(Result) Value = m_Document[Key].GetInt();
	return Result;
}

bool MFileJSON::GetValue(const char* Key, bool& Value)
{
	Result = CheckValue(Key, "", JSNT_BOOL);
	if(Result) Value = m_Document[Key].GetBool();
	return Result;
}

bool MFileJSON::GetValue(const char* Key, double& Value)
{
	Result = CheckValue(Key, "", JSNT_DOUBLE);
	if(Result) Value = m_Document[Key].GetDouble();
	return Result;
}

bool MFileJSON::GetValue(const char* Key, const char* SubKey, int& Value)
{
	Result = CheckValue(Key, SubKey, JSNT_INT);
	if(Result) Value = m_Document[Key][SubKey].GetInt();
	return Result;
}

bool MFileJSON::GetValue(const char* Key, const char* SubKey, bool& Value)
{
	Result = CheckValue(Key, SubKey, JSNT_BOOL);
	if(Result) Value = m_Document[Key][SubKey].GetBool();
	return Result;
}

bool MFileJSON::GetValue(const char* Key, const char* SubKey, double& Value)
{
	Result = CheckValue(Key, SubKey, JSNT_DOUBLE);
	if(Result) Value = m_Document[Key][SubKey].GetDouble();
	return Result;
}

bool MFileJSON::GetArray(const char* Key, std::vector<int>* Array)
{
	if(!Array) return false;
	Result = CheckValue(Key, "", JSNT_ARRAY);
	if(Result)
	{
		Array->clear();
		const rapidjson::Value& ArrayValue = m_Document[Key];
		for(unsigned int i = 0; i < ArrayValue.Size(); i++)
            Array->push_back(ArrayValue[i].GetInt());
	}
	return Result;
}

bool MFileJSON::GetArray(const char* Key, const char* SubKey, std::vector<int>* Array)
{
	if(!Array) return false;
	Result = CheckValue(Key, SubKey, JSNT_ARRAY);
	if(Result)
	{
		Array->clear();
		const rapidjson::Value& ArrayValue = m_Document[Key][SubKey];
		for(unsigned int i = 0; i < ArrayValue.Size(); i++)
            Array->push_back(ArrayValue[i].GetInt());
	}
	return Result;
}

void MFileJSON::Close()
{
	m_Document.SetObject();
	if(jsonBuffer) delete [] jsonBuffer;
}
