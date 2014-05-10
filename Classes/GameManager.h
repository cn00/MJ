#pragma once
#include "sqlite/sqlite3.h"
#include "TemplateCreate.h"

#define GMGI GameManager::getInstance()

class GameManager;

struct User
{
	User(){}
	string id;
	string name;
	string code;
};

class GameManager:public Singleton<GameManager>
{
public:
	User *const user;

	static sqlite3 *pDB;//数据库指针
	static string dbpath;
	static map< int/*idx*/, vector< string >/*value*/ > sqlRecords;
	
	
	static void sqlCommand(const char *condition ){GameManager::sqlCommand(condition, sqlLoadRecord);}
	static void sqlCommand(const char *condition, int (*callback)(void*,int,char**,char**) );
	static int sqlLoadRecord( void *para, int n_column, char ** column_value, char ** column_name );
	static void sqlInsert(const char *table, int n_column, const char **column_name, const char **column_value);

	GameManager();
	~GameManager();

	static string getText(string id);
	static string getText(string id, string key);
	bool showMsg(string id);
};

