#include "GameManager.h"

/*
 column_name1,	column_name2,	column_name3	
 value11,		value12,		value13
 value21,		value22,		value23
 value31,		value32,		value33
 */
map<int/*column_name*/, vector<string>/*column_value*/ > GameManager::sqlRecords;
string GameManager::dbpath;
sqlite3 * GameManager::pDB = nullptr;

bool GameManager::showMsg( string id )
{
	return "";
}

const string language[]={
    "en",	//ENGLISH = 0,
    "cn",	//CHINESE,
    "fr",	//FRENCH,
    "it",	//ITALIAN,
    "ge",	//GERMAN,
    "sp",	//SPANISH,
    "du",	//DUTCH,
    "ru",	//RUSSIAN,
    "ko",	//KOREAN,
    "ja",	//JAPANESE,
    "hu",	//HUNGARIAN,
    "por",	//PORTUGUESE,
    "ar",	//ARABIC,
    "no",	//NORWEGIAN,
    "pol",	//POLISH
};
int languaget = int(LanguageType::CHINESE);

std::string GameManager::getText( string id, string key )
{
	sqlRecords.clear();
	sqlCommand((char*)(" select " + key + " from text where id = "+ id +" ;").c_str(), GameManager::sqlLoadRecord);
	if(sqlRecords.size() > 0)return sqlRecords[languaget][0];
	else return "";
}

GameManager::GameManager():user(new User())
{
	dbpath = CCFileUtils::getInstance()->getWritablePath() + ("data.db");
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	dbpath = CCFileUtils::sharedFileUtils()->fullPathForFilename("data.db");
#endif
	char* errMsg;
	int sqlite3_result = sqlite3_open(dbpath.c_str(), &pDB);
	if( sqlite3_result != SQLITE_OK )
		CCLOG( "Open database failed, errorcode :%d, error msg:%s" , sqlite3_result, errMsg );
	else CCLOG( "Open database successful" );
	// 	path = CCFileUtils::sharedFileUtils()->fullPathForFilename("data.db3");
	CCLOG("dbpath = %s", dbpath.c_str());
}

GameManager::~GameManager()
{
	delete user;
	sqlite3_close(pDB);
	CCLOG("~sqlite3_close(pDB);");
}

void GameManager::sqlCommand( const char *condition, int (*callback)(void*,int,char**,char**) )
{
	char* sqlitemsg;
	sqlite3_exec( pDB, condition ,callback, 0, &sqlitemsg );
	CCLOG("SqliteAction::sqlCommand = %s, sqlitemsg信息 = %s", condition, sqlitemsg);
}

int GameManager::sqlLoadRecord( void *para, int n_column, char ** column_value, char ** column_name )
{
	vector<string> param;
	for ( int i = 1; i < n_column; ++i )
	{
		CCLOG("SqliteAction::sqlLoadRecord  %s, %s, %zu",column_name[i], column_value[i], strlen(column_value[i]));
		param.push_back(column_value[i]);
	}
	sqlRecords.insert(make_pair(atoi(column_value[0]), param));
	
//	sqlRecords.pushBack(param);
// 	CCLOG("SqliteAction::sqlLoadRecord  %s",param.c_str());
	return 0;  
}

void GameManager::sqlInsert( const char *table, int n_column, const char **column_name, const char **column_value )
{
	string sqlstr = string(" create table if not exists ") + table + "(";
	for (int i = 0; i < n_column; ++i)
	{
		sqlstr += " "+string(column_name[i])+" char(30)";
		sqlstr += (i < n_column-1) ? ", " : ", rdatet DATETIME NOT NULL DEFAULT (datetime('now','localtime') ) )";
	}
	char* errMsg;
	int sqlite3_result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );
	CCLOG("SqliteAction::sqlInsertRecord sqlstr = %s, &errMsg = %s", sqlstr.c_str(), errMsg);

	sqlstr = string(" insert into ") + table + ("( ");
	for (int i = 0; i < n_column; ++i)
	{
		sqlstr += "'"+string(column_name[i])+"'";
		if(i != n_column-1)sqlstr += ", ";
	}
	sqlstr += string(") values( ");
	for (int i = 0; i < n_column; ++i)
	{
		sqlstr += string("'") + (column_value[i]) + "'";
		if(i != n_column-1)sqlstr += ", ";
	}
	sqlstr += string(")");
	CCLOG("SqliteAction::sqlInsertRecord sqlstr = %s", sqlstr.c_str());
	sqlite3_result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );
	if(sqlite3_result != SQLITE_OK )CCLOG( "insrt failed:%d, errMsg:%s" , sqlite3_result, errMsg ); 
}
