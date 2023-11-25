#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

using namespace std;

int main() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    std::string hostName = "mysql.students.it-college.ru";
    std::string userName = "i22s0997";
    std::string password = "vWkkYUdP";
    std::string databaseName = "i22s0997";
    std::string tableName = "Hello";
    std::string columnName = "";


    std::cout << "Enter name: ";
    std::cin >> columnName;

    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(hostName, userName, password);
        con->setSchema(databaseName);

        // Delete rows with a specific value in the column
        std::string deleteValue;
        std::cout << "Enter value to delete: ";
        std::cin >> deleteValue;

        sql::PreparedStatement* deleteStmt = con->prepareStatement("DELETE FROM " + tableName + " WHERE " + columnName + " = ?");
        deleteStmt->setString(1, deleteValue);
        deleteStmt->executeUpdate();
        delete deleteStmt;

        // Add a new value to the column
        std::string newValue;
        std::cout << "Enter new value: ";
        std::cin >> newValue;

        sql::PreparedStatement* insertStmt = con->prepareStatement("INSERT INTO " + tableName + "(" + columnName + ") VALUES (?)");
        insertStmt->setString(1, newValue);
        insertStmt->executeUpdate();
        delete insertStmt;

        // Retrieve and display the updated values from the column
        sql::Statement* selectStmt = con->createStatement();
        sql::ResultSet* res = selectStmt->executeQuery("SELECT " + columnName + " FROM " + tableName);

        while (res->next()) {
            std::cout << res->getString(columnName) << std::endl;
        }

        delete res;
        delete selectStmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        std::cout << "MySQL Error: " << e.what() << std::endl;
    }

    return 0;
}
