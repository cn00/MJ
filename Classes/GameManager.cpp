#include "GameManager.h"

vector< string > GameManager::sqlRecords;
string GameManager::dbpath;
bool GameManager::showMsg( string id )
{
	return "";
}

std::string GameManager::getText( string id, string key )
{
	sqlRecords.clear();
	sqlCommand((char*)(" select " + key + " from text where id = "+ id +" ;").c_str(), GameManager::sqlLoadRecord);//½µÐò DESC, ÉýÐò ASC
	if(sqlRecords.size() > 0)return sqlRecords[0];
	else return "";
}

GameManager::GameManager():user(new User())
{
	dbpath = CCFileUtils::getInstance()->getWritablePath() + ("data.db3");
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	dbpath = CCFileUtils::sharedFileUtils()->fullPathForFilename("data.db3");
#endif
	sqlite3_result = sqlite3_open(dataName, &pDB); 
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

void GameManager::sqlCommand( char *condition, int (*callback)(void*,int,char**,char**) )
{
	sqlite3_result = sqlite3_exec( pDB, condition ,callback, 0, &errMsg );
	CCLOG("SqliteAction::sqlCommand = %s, errorMsg = %s", condition, errMsg);
}

int GameManager::sqlLoadRecord( void *para, int n_column, char ** column_value, char ** column_name )
{
	string param = "";
	for ( int i = 0; i < n_column; ++i )
	{
		param += column_value[i];
		param += "    ";
	}
	sqlRecords.push_back(param);
// 	CCLOG("SqliteAction::sqlLoadRecord  %s",param.c_str());
	return 0;  
}

void GameManager::sqlInsert( char *table, int n_column, const char **column_name, const char **column_value )
{
	string sqlstr = string(" create table if not exists ") + table + "(";
	for (int i = 0; i < n_column; ++i)
	{
		sqlstr += " "+string(column_name[i])+" char(30)";
		sqlstr += (i < n_column-1) ? ", " : ", rdatet DATETIME NOT NULL DEFAULT (datetime('now','localtime') ) )";
	}
	sqlite3_result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg ); 
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
