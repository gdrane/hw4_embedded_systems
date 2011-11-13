/* readInput - read text file input from the local file system
 * Paul Martin & Gauresh Rane
 * EE202A Homework #3
 */
 
/* The &#64257;rst line is a positive integer in the range [1, 65535] indicating the number of repetitions X.
 * The second line is a positive integer in the range [1, 4096] indicting the number of input samples in one repetition, K.
 * The following lines are the sample values, as many as those speci&#64257;ed in the second line. These are signed integers.
 * The idea is that the input over which you are computing is obtained by repeating X times, the sequence of K samples.
 *
 * (1) X
 * (2) K
 * (3) 12523
 * (4) -12442
 * ...
 * (K)
*/

#include "mbed.h"
#include "pins.h"
#include <fstream>
#include <string>
#include <sstream>

extern Serial pc;

// -- Variables --
signed int inBuffer[4096] __attribute__ ((section("AHBSRAM0"))); 

// -- Function Headers --
void readInput(int* x, int* k);
bool isNumeric(const char* pszInput);

// -- Function Implementations --
void readInput(int* x, int* k){
    int _x, _k, k_count = 0;
    // does the file exist?
    FILE *file = fopen("/local/input.txt", "r");
    if (!(file)){
        error("ERROR: NO INPUT");
    }else{
        fclose(file);
    }
    // open input file as read-only
    ifstream fp("/local/input.txt");
    string temp;
        
    // set pin 22 for grading purposes
    set(22);
    // get X
    if(!getline(fp,temp))
        error("ERROR: BAD INPUT FORMAT");
    if(!isNumeric(temp.c_str()))
        error("ERROR: BAD INPUT FORMAT");
    _x = atoi(temp.c_str());
    // get K
    if(!getline(fp,temp))
        error("ERROR: BAD INPUT FORMAT");
    if(!isNumeric(temp.c_str()))
        error("ERROR: BAD INPUT FORMAT");
    _k = atoi(temp.c_str());
    // parse the rest
    while (!fp.eof() && getline(fp, temp)){ 
        if(!isNumeric(temp.c_str()))
            error("ERROR: BAD INPUT FORMAT");
        inBuffer[k_count++] = atoi(temp.c_str());
    }
    if(k_count != _k)
        error("ERROR: BAD INPUT FORMAT");
    
    // update X & K
    *x = _x;
    *k = _k;

    // set pin 23 for grading purposes
    set(23);
}
bool isNumeric(const char* input){
    string inputStr = input;
    string valids = "0123456789-";
    for(int i=0; i<inputStr.length(); i++){
        if(valids.find(inputStr[i]) == string::npos && inputStr[i] != '\r' && inputStr[i] != '\n'){
            return false;
        }
    }
    return true;
}
