#ifndef filesjsonH
#define filesjsonH

#define JSNT_NONE 0
#define JSNT_INT 1
#define JSNT_BOOL 2
#define JSNT_DOUBLE 3
#define JSNT_ARRAY 4

#include <fcntl.h>
#include <sys/stat.h>
#include <rapidjson/document.h>
#include <rapidjson/reader.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/error/en.h>
#include <vector>

class MFileJSON
{
private:
	bool Result;
	char* jsonBuffer;
	rapidjson::Document m_Document;
	bool CheckValue(const char* Key, const char* SubKey, unsigned char Type);
public:
	MFileJSON();
	bool Read(const char* FileName);
	bool Write(const char* FileName);
	bool GetValue(const char* Key, int& Value);
	bool GetValue(const char* Key, bool& Value);
	bool GetValue(const char* Key, double& Value);
	bool GetValue(const char* Key, const char* SubKey, int& Value);
	bool GetValue(const char* Key, const char* SubKey, bool& Value);
	bool GetValue(const char* Key, const char* SubKey, double& Value);
	bool GetArray(const char* Key, std::vector<int>* Array);
	bool GetArray(const char* Key, const char* SubKey, std::vector<int>* Array);
	void Close();
};

#endif
