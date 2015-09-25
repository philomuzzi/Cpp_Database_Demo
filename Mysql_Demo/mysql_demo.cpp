#include <mysql_connection.h>  
#include <mysql_driver.h>  
#include <cppconn/statement.h>  

using namespace sql;
using namespace std;

void RunConnectMySQL()
{
	mysql::MySQL_Driver *driver;
	Connection *con;
	Statement *state;
	ResultSet *result;
	// 初始化驱动  
	driver = sql::mysql::get_mysql_driver_instance();
	// 建立链接  
	con = driver->connect("tcp://localhost:3306", "zqgame", "zqgame");
	state = con->createStatement();
	state->execute("use world");
	// 查询  
	result = state->executeQuery("select * from city where population > 1000000");
	// 输出查询  
	while (result->next())
	{
		auto id = result->getInt("ID");
		auto name = result->getString("2");
		auto country = result->getString("3");
		cout << id << " : " << name << " : " << country << endl;
	}
	delete state;
	delete con;
}

int main(int argc, char* argv[])
{
	RunConnectMySQL();
	getchar();
	return 0;
}