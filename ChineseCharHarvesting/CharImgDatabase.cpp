/**
 * Author: Shawn Jin
 * Purpose: creating a table to store the information of bitmaps.
 * 
 * 
 */ 
#include <sqlite3.h>
#include <iostream>


class BitmapToDatabase() {

public:
    int BitmapToDatabase(char *filePath);

private:
    sqlite3 *database;
    std::string createTable = "CREATE TABLE if NOT EXISTS char_bitmaps "
            "(page NUMERIC, "
            "idx NUMERIC, "
            "image VARCHAR); ";             
    std::string createIndex = "CREATE INDEX IF NOT EXISTS page_idx "
            "ON char_bitmaps (page, idx); ";
    std::string query =  "EXPLAIN QUERY PLAN "
            "SELECT page,idx FROM char_bitmaps WHERE page = '6';"

}

/**
 * CONTRIBUTER
 * filePath: the path of a database file 
 */
int BitmapToDatabase::BitmapToDatabase(char *filePath) {
    using namespace std;
    int exit = 0;
    char *errorMessage;

    exit = sqlite3_open(filePath, &database);
    // check open status?
    // create table 
    exit = sqlite3_exec(database, sql.c_str(), NULL, 0, &errorMessage);
    if (exit != SQLITE_OK) {
        cerr << "Error Create Table" << endl;
        sqlite3_free(messaggeError); 
        return -1;
    } else {
        std::cout << "Table created Successfully" << std::endl;
    }
    // create index 
    exit = sqlite3_exec(database, sql.c_str(), NULL, 0, &errorMessage);
    if (exit != SQLITE_OK) {
        cerr << "Error Create Index" << endl;
        sqlite3_free(messaggeError); 
        return -1;
    } else {
        std::cout << "Index created Successfully" << std::endl;
    }
    // 


    sqlite3_close(database);
}

