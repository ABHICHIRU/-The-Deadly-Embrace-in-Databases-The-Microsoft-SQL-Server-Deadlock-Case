# SQL SETUP
CREATE TABLE TableA (id INT PRIMARY KEY, value VARCHAR(50));
CREATE TABLE TableB (id INT PRIMARY KEY, value VARCHAR(50));

INSERT INTO TableA VALUES (1, 'A1');
INSERT INTO TableB VALUES (1, 'B1');


C++ CODE

  #include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <thread>

void executeDeadlockScenario(const char* connStr, bool firstLocksA) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    if (SQLDriverConnectA(hDbc, NULL, (SQLCHAR*)connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE) == SQL_SUCCESS) {
        SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
        SQLExecDirectA(hStmt, (SQLCHAR*)"BEGIN TRAN", SQL_NTS);

        if (firstLocksA) {
            SQLExecDirectA(hStmt, (SQLCHAR*)"UPDATE TableA SET value = 'ThreadA' WHERE id = 1", SQL_NTS);
            Sleep(1000); // Wait to increase chance of deadlock
            SQLExecDirectA(hStmt, (SQLCHAR*)"UPDATE TableB SET value = 'ThreadA' WHERE id = 1", SQL_NTS);
        } else {
            SQLExecDirectA(hStmt, (SQLCHAR*)"UPDATE TableB SET value = 'ThreadB' WHERE id = 1", SQL_NTS);
            Sleep(1000); // Wait to increase chance of deadlock
            SQLExecDirectA(hStmt, (SQLCHAR*)"UPDATE TableA SET value = 'ThreadB' WHERE id = 1", SQL_NTS);
        }

        SQLExecDirectA(hStmt, (SQLCHAR*)"COMMIT TRAN", SQL_NTS);
    } else {
        std::cerr << "Connection failed." << std::endl;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}

int main() {
    const char* connStr = "DRIVER={SQL Server};SERVER=localhost;DATABASE=TestDB;Trusted_Connection=yes;";
    std::thread t1(executeDeadlockScenario, connStr, true);
    std::thread t2(executeDeadlockScenario, connStr, false);

    t1.join();
    t2.join();

    std::cout << "Execution complete. Check SQL Server logs for deadlock detection." << std::endl;
    return 0;
}

