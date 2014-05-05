#pragma once
#include "sqlite/sqlite3.h"
#include "TemplateCreate.h"

#define GMGI GameManager::getInstance()
#define dataName (dbpath).c_str()

class User
{
public:
	User(){}
	string id;
	string name;
	string code;
};

class GameManager : public Singleton<GameManager>
{
public:
	User *const user;

	sqlite3 *pDB;//数据库指针 
	char * errMsg;//错误信息 
	static string dbpath;
	static vector< string > sqlRecords;
	int sqlite3_result;//sqlite3_exec返回值
	void sqlCommand( char *condition, int (*callback)(void*,int,char**,char**) );
	static int sqlLoadRecord( void *para, int n_column, char ** column_value, char ** column_name );
	void sqlInsert(char *table, int n_column, const char **column_name, const char **column_value);

	GameManager();
	~GameManager();

	string getText(string id);
	string getText(string id, string key);
	bool showMsg(string id);
};

