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
    int page_range[2] = {0, 1};

    // default database file path
    std::string db_file = "/home/wan/Desktop/ShawnJin_Workspace/Wordly_OCR_Cpp/ChineseCharHarvesting/Database/charImgData.db";
    // Number of bigger than chars per page
    int max_char = 9;
    //================================ pbm format pictures ===========================
    // std::string char_img_pattern = "page%02d-char%05d.pbm";      // with pages info
    // std::string char_img_pattern_pbm = "char%05d.pbm";           // no pages info
    //================================ png format pictures ===========================
    // std::string char_img_pattern = "page%02d-char%05d.png";      // with pages info
    std::string char_img_pattern_png = "char%05d.png";              // no pages info
    //================================================================================

    std::string createTable = "CREATE TABLE if NOT EXISTS char_bitmaps "
                              "(page NUMERIC, "
                              "idx NUMERIC, "
                              "image VARCHAR); ";
    std::string createIndex = "CREATE INDEX IF NOT EXISTS page_idx "
                              "ON char_bitmaps (page, idx); ";
    std::string query_test =  "EXPLAIN QUERY PLAN "
                         "SELECT page,idx FROM char_bitmaps WHERE page = '6';";
    // query without page info
    std::string query =  "SELECT idx FROM char_bitmaps "
                              "WHERE idx = %d;";

    // std::string write_with_page = "INSERT INTO char_bitmaps"
    //                               "VALUES (%d, %d, %s);";

    std::string write = "INSERT INTO char_bitmaps(pages, idx, image)"
                        "VALUES (0, %d, %s);";
};

/**
 *  Check if a file is exist according to the input path parameter.
 **/
inline bool fexists(const std::string filename) {
    using namespace std;
    ifstream ifile(filename);
    return ifile.good();
}

/**
 * CONTRIBUTOR
 * filePath: the path of a database file
 */
BitmapToDatabase::BitmapToDatabase(char *filePath) {
    using namespace std;
    // check if the input path is valid of not
    if (!fexists(filePath)) {
        std::cout << "Input path invalid, going to use default path.";
    } else {
        db_file = filePath;
    }

    int exit = 0;
    char *errorMessage;
    exit = sqlite3_open(db_file.c_str(), &database);
    // create table
    exit = sqlite3_exec(database, createTable.c_str(), nullptr, nullptr, &errorMessage);
    if (exit != SQLITE_OK) {
        cerr << "Error Create Table" << endl;
        sqlite3_free(errorMessage);
    } else {
        std::cout << "Table created Successfully" << std::endl;
    }
    // create index
    exit = sqlite3_exec(database, createIndex.c_str(), nullptr, nullptr, &errorMessage);
    if (exit != SQLITE_OK) {
        cerr << "Error Create Index" << endl;
        sqlite3_free(errorMessage);
    } else {
        std::cout << "Index created Successfully" << std::endl;
    }

}



int BitmapToDatabase::update() {

    char buffer[150];
    std::string home_char_dir = "/home/wan/Desktop/ShawnJin_Workspace/Wordly_OCR_Cpp/ChineseCharHarvesting/Chars_data/Chars/";
    for (int page = page_range[0]; page <= page_range[1]; page++) {
        std::cout << "Page:" << page << std::endl;
        bool found_first_char = false;

        // loop each pages in char folder
        for (int index = 1; index < max_char; index++) {
            int n = sprintf(buffer, char_img_pattern_png.c_str(), index);
            std::string char_dir = home_char_dir + buffer;
            std::cout << "buffer : " << char_dir <<std::endl;

            // try to find the characters
            if (fexists(char_dir)) {
                found_first_char = true;
            } else {
                std::cout << "File doesn't exist!" << std::endl;
                break;
            }

//            if (!found_first_char) {
//                return -1;
//            }
            // read image
            cv::Mat image = cv::imread(char_dir);
            // cv::imshow("test", image);
            // cvWaitKey(0);

            // open database
            char* errorMessage;
            int exit;
            if ((sqlite3_open(db_file.c_str(), &database)) != SQLITE_OK) {
                std::cerr << "Error open the database file!" << std::endl;
                return -1;
            }
            // convert cv::Mat to std::string
            std::string image_string;
            std::vector<unsigned  char> buff;
            // ALERT: ext need to be changed if the images format changes
            cv::imencode(".png", image, buff);
            image_string.resize(buff.size());
            memcpy(&image_string[0], buff.data(), buff.size());
            // update the update query
            sprintf(buffer, write.c_str(), index, image_string.c_str());
//            std::cout << "TEST: query: " << buffer << std::endl;
            // update database
            exit = sqlite3_exec(database, buffer, nullptr, nullptr, &errorMessage);
            if (exit != SQLITE_OK) {
                std::cerr << "Error: Update Failed!" << std::endl;
                std::cerr << errorMessage << std::endl;
                sqlite3_free(errorMessage);
            } else {
                std::cout << "Update index: " << index << " Successfully" << std::endl;
            }

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