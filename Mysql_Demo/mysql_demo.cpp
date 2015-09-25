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
	// ��ʼ������  
	driver = sql::mysql::get_mysql_driver_instance();
	// ��������  
	con = driver->connect("tcp://localhost:3306", "zqgame", "zqgame");
	state = con->createStatement();
	state->execute("use world");
	// ��ѯ  
	result = state->executeQuery("select * from city where population > 1000000");
	// �����ѯ  
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