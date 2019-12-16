/**
 * Author: Shawn Jin
 * Purpose: creating a table to store the information of bitmaps.
 * 
 * 
 */ 
#include <sqlite3.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>


class BitmapToDatabase {

public:
    BitmapToDatabase(char *filePath);
    int update();

private:
    sqlite3 *database;
    int page_range[2] = {6, 95};
    int max_char = 999;             // # bigger than chars per page
    char *char_img_pattern = "page%02d-char%05d.png";


    std::string createTable = "CREATE TABLE if NOT EXISTS char_bitmaps "
            "(page NUMERIC, "
            "idx NUMERIC, "
            "image VARCHAR); ";             
    std::string createIndex = "CREATE INDEX IF NOT EXISTS page_idx "
            "ON char_bitmaps (page, idx); ";
    std::string query =  "EXPLAIN QUERY PLAN "
            "SELECT page,idx FROM char_bitmaps WHERE page = '6';";

};

/**
 * CONTRIBUTER
 * filePath: the path of a database file 
 */
BitmapToDatabase::BitmapToDatabase(char *filePath) {
    char *db_file = "";            // default path 
    char *char_dir = "";

    using namespace std;
    int exit = 0;
    char *errorMessage;

    exit = sqlite3_open(filePath, &database);
    // check open status?
    // create table 
    exit = sqlite3_exec(database, createTable.c_str(), NULL, 0, &errorMessage);
    if (exit != SQLITE_OK) {
        cerr << "Error Create Table" << endl;
        sqlite3_free(errorMessage); 
        // return -1;
    } else {
        std::cout << "Table created Successfully" << std::endl;
    }
    // create index 
    exit = sqlite3_exec(database, createIndex.c_str(), NULL, 0, &errorMessage);
    if (exit != SQLITE_OK) {
        cerr << "Error Create Index" << endl;
        sqlite3_free(errorMessage); 
        // return -1;
    } else {
        std::cout << "Index created Successfully" << std::endl;
    }

}
/**
 *  Check if a file is exist.  
 **/
inline bool fexists(const char *filename) {
    using namespace std;
    ifstream ifile(filename);
    return ifile.good();
}

int BitmapToDatabase::update() {
    char buffer[50];
    for (int page = page_range[0]; page <= page_range[1]; page++) {
        std::cout << "Page:" + page;
        bool found_first_char = false;

        for (int index = 1; index < max_char; i++) {
            int n = sprintf(buffer, char_img_pattern, page, index);
            if (fexists(buffer) && !found_first_char) {
                found_first_char = true;
            } else {
                break;
            }

            if (!found_first_char) {
                continue;
            }


        }
    }
    return -1;
}

/**
 * ANCHOR Shawn Jin
 * 
 * 
 */
int main() {

}