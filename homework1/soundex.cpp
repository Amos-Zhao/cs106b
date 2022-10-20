/**
 * @file: soundex.cpp
 * @author: jianfei.zhao
 * @description: Surname code retrieval program(Soundex system proposed by Margaret O'Dell and Robert C. Russell)
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
#include "map.h"
using namespace std;

/* This function is intended to return a string which
 * contains only the letter characters (capitalized) from the original
 * (all non-letter characters are removed)
 *
 * if string s is empty, s[0] would access to nothing
 * if the first char is not Letter, result will not be initialize properly
 * --initialize result with empty and let i start from 0
 */
string remove_non_letters(string s) {
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += toupper(s[i]);
        }
    }
    return result;
}

/* This function is intended to convert a string (capitalized and all letter)
 * to soudex encode system in number
 */
string encode_processed_string(string s){
    Map<char,char> encode_map={{'A','0'},{'E','0'},{'I','0'},{'O','0'},{'U','0'},{'H','0'},{'W','0'},{'Y','0'}
                              ,{'B','1'},{'F','1'},{'V','1'},{'P','1'}
                              ,{'C','2'},{'G','2'},{'J','2'},{'K','2'},{'Q','2'},{'S','2'},{'X','2'},{'Z','2'}
                              ,{'D','3'},{'T','3'}
                              ,{'L','4'}
                              ,{'M','5'},{'N','5'}
                              ,{'R','6'}
                              };
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        result += encode_map.get(s[i]);
    }
    return result;
}

/* Merge adjacent duplicate numbers
 */
string merge_adjacent_duplicate_numbers(string s){
    string result="";
    for (int i = 0; i < s.length(); i++) {
        if(i>=1){
            if(s[i]!=result.at(result.size()-1)){
                result+=s[i];
            }
        }else{
            result+=s[i];
        }
    }
    return result;
}

/* fill with 0 or extract string to the size of 4
 */
string fill_extract_string_to_size_of_4(string s){
    string result=s.substr(0,4);
    int string_size=result.size();
    if(string_size<4){
        for(int i=0;i<4-string_size;i++){
            result+='0';
        }
    }
    return result;
}

/* This function is intended to return a encode(soudex system) with input `s`
 */
string soundex(string s) {
    //1. remove extra character that cannot be encoded and make all letter capitalized(mark as processed_input)
    string processed_input= remove_non_letters(s);
    //2. generate encode table with specific data structure(like dict in python)
    //3. repalace all character in the input string with encode table
    string encode=encode_processed_string(processed_input);
    //4. Merge adjacent duplicate numbers in the encode
    encode=merge_adjacent_duplicate_numbers(encode);
    //5. repalce first char in encode with the first char of processed_input  (make the first letter capitalized instead of step 1 seems make program faster )'
    if(encode.size()>0){
        encode[0]=processed_input[0];
    }
    //6. remove all 0 in encode
    encode=stringReplace(encode,"0","");
    //7. fill or extract the encode to make the length is 4
    encode= fill_extract_string_to_size_of_4(encode);
    return encode;
}


/* calculate the Soundex encoding of input, and then find all last names with the same encoding in the database
 * the input filepath is the file path of database file
 */
void soundexSearch(string filepath) {
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "<< databaseNames.size() << " names found." << endl;
    bool process_next=true;
    while(process_next){
        string surname = getLine("Enter a surname (RETURN to quit): ");
        if(surname.size()==0){
            process_next=false;
        }else{
            string encode=soundex(surname);
            cout << "Soundex code is "  << encode << endl;
            Vector<string> matches;
            for(string item:databaseNames){
                if(equalsIgnoreCase(encode,soundex(item))){
                    matches.add(item);
                }
            }
            matches.sort();
            cout << "Matches from database:"  << matches << endl;
        }
    }
    cout << "All done!"  ;
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = remove_non_letters(s);
    EXPECT_EQUAL(result, "OHARA");
    s = "Planet9";
    result = remove_non_letters(s);
    EXPECT_EQUAL(result, "PLANET");
    s = "tl dr";
    result = remove_non_letters(s);
    EXPECT_EQUAL(result, "TLDR");
    s = "";
    result = remove_non_letters(s);
    //failed at here
    EXPECT_EQUAL(result, "");
    s = "Am0s";
    result = remove_non_letters(s);
    EXPECT_EQUAL(result, "AMS");
    s = "0000";
    result = remove_non_letters(s);
    EXPECT_EQUAL(result, "");
}

PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

STUDENT_TEST("Test encode_processed_string") {
    string s="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result = encode_processed_string(s);
    EXPECT_EQUAL(result, "01230120022455012623010202");
}

STUDENT_TEST("Test merge_adjacent_duplicate_numbers") {
    EXPECT(equalsIgnoreCase(merge_adjacent_duplicate_numbers("1003"),  "103"));
    EXPECT(equalsIgnoreCase(merge_adjacent_duplicate_numbers("0000"),  "0"));
}

STUDENT_TEST("Test fill_extract_string_to_size_of_4") {
    string s="AMOS";
    string result = fill_extract_string_to_size_of_4(s);
    EXPECT_EQUAL(result, "AMOS");
    s="";
    result = fill_extract_string_to_size_of_4(s);
    EXPECT_EQUAL(result, "0000");
    s="AMMMMMOS";
    result = fill_extract_string_to_size_of_4(s);
    EXPECT_EQUAL(result, "AMMM");
    s="A";
    result = fill_extract_string_to_size_of_4(s);
    EXPECT_EQUAL(result, "A000");
}



