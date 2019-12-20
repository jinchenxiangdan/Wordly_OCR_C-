/**
 * Author: Shawn Jin
 * Purpose: creating a table to store the information of bitmaps.
 *
 *
 */
#include <sqlite3.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>


class BitmapToDatabase {

public:
    explicit BitmapToDatabase(char *filePath);
    int update();

private:
    sqlite3 *database{};
    int page_range[2] = {6, 95};
    int max_char = 999;             // # bigger than chars per page
//    std::string char_img_pattern = "page%02d-char%05d.png";
    std::string char_img_pattern = "char%05d.pbm";


    std::string createTable = "CREATE TABLE if NOT EXISTS char_bitmaps "
                              "(page NUMERIC, "
                              "idx NUMERIC, "
                              "image VARCHAR); ";
    std::string createIndex = "CREATE INDEX IF NOT EXISTS page_idx "
                              "ON char_bitmaps (page, idx); ";
    std::string query =  "EXPLAIN QUERY PLAN "
                         "SELECT page,idx FROM char_bitmaps WHERE page = '6';";

    std::string write = "SELECT page, idx FROM char_bitmaps "
                        "WHERE page = %d AND idx = %d;";
};

/**
 * CONTRIBUTOR
 * filePath: the path of a database file
 */
BitmapToDatabase::BitmapToDatabase(char *filePath) {
    char db_file[] = "/home/wan/Desktop/ShawnJin_Workspace/charImgData.db";            // default path


    using namespace std;
    int exit = 0;
    char *errorMessage;

    exit = sqlite3_open(db_file, &database);
    // check open status?
    // create table
    exit = sqlite3_exec(database, createTable.c_str(), nullptr, nullptr, &errorMessage);
    if (exit != SQLITE_OK) {
        cerr << "Error Create Table" << endl;
        sqlite3_free(errorMessage);
        // return -1;
    } else {
        std::cout << "Table created Successfully" << std::endl;
    }
    // create index
    exit = sqlite3_exec(database, createIndex.c_str(), nullptr, nullptr, &errorMessage);
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
inline bool fexists(const std::string filename) {
    using namespace std;
    ifstream ifile(filename);
    return ifile.good();
}

int BitmapToDatabase::update() {

    char buffer[150];
    for (int page = page_range[0]; page <= page_range[1]; page++) {
        std::cout << "Page:" << page << std::endl;
        bool found_first_char = false;
        std::string char_dir = "/home/wan/IdeaProjects/worldly-ocr/ChineseCharHarvesting/BWChars/";

        // loop each pages in char folder
        for (int index = 1; index < max_char; index++) {
            int n = sprintf(buffer, char_img_pattern.c_str(), index);
            char_dir += buffer;
            std::cout << "buffer : " << char_dir <<std::endl;

            // try to find the characters
            if (fexists(char_dir) && !found_first_char) {
                found_first_char = true;
            } else {
                std::cout << "File doesn't exist!" << std::endl;
                break;
            }

            if (!found_first_char) {
                return -1;
            }
            cv::Mat image = cv::imread(char_dir);
//            cv::imshow("test", image);
//            cvWaitKey(0);


            char_dir = "Chars/";
        }
    }
    return 0;
}

/**
 * ANCHOR Shawn Jin
 *
 *
 */
int main() {
    char path[] = "test img";
    BitmapToDatabase bitmapToDatabase = *new BitmapToDatabase(path);
    bitmapToDatabase.update();
}