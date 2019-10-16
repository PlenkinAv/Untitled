#include <stdio.h>
using namespace std;

void addWord (char** &words, int* &lengths, int &amountOfWords){
    amountOfWords++;
    char** temp = new char*[ amountOfWords ];
    int* newLengths = new int[ amountOfWords ];
    for (int i = 0; i < amountOfWords-1; i++) { temp[i] = words[i]; newLengths[i] = lengths[i]; };
    temp [ amountOfWords-1 ] = new char [1];
    temp [ amountOfWords-1 ] [0] = '\n';
    newLengths[ amountOfWords-1 ] = 1;
    delete words; delete lengths;
    words = temp; lengths = newLengths;
    return;}

void pushChar (char ch, char **&words, int &amountOfWords, int* &lengths, int numberOfWord){
    if ( numberOfWord > amountOfWords) {addWord (words, lengths, amountOfWords);}
        lengths[numberOfWord-1]++;
        char* temp = new char[ lengths[ numberOfWord-1 ] ];
        for (int i=0; i<lengths[ numberOfWord-1 ]-1; i++) {temp[i] = words[numberOfWord-1][i];};
        temp[lengths[ numberOfWord-1 ] -2] = ch;
        delete words[numberOfWord-1];
        words[numberOfWord-1] = temp;
    return;}

 void readStringFromFile (FILE* fin, char** &words, int &amountOfWords, int* &lengths){
    char ch = 0;
    bool onWord = true;
    if  ( ( (ch = fgetc(fin) ) == ' ') || (ch == EOF) ) {onWord = false;};
    if ( ch != EOF) {
        rewind(fin);
        int i=1;
        while  ( ( ch = fgetc(fin) ) != EOF )         
            if ( ( ((ch >= '0') && (ch <= '9')) || ((ch >= 'A') && (ch <= 'Z')) ) || ((ch >= 'a') && (ch <= 'z')) ) {
                pushChar(ch, words, amountOfWords, lengths, i);
                onWord = true;}
            else {
                if ( (ch == ' ') && (onWord) )
                    i++;
                    onWord = false;};}
    return;}

void sort (char** &words, int amountOfWords, int* lengths){
    for(int i=0; i< amountOfWords-1; i++)
        for(int j=i+1; j< amountOfWords; j++)
            if ( lengths[i] > lengths[j] ) {
                char* temp = words[i]; int tempLength = lengths[i];
                words[i] = words[j]; lengths[i] = lengths[j];
                words[j] = temp; lengths[j] = tempLength;
            }
    return;}

void outputWordsToFile(FILE *fout, char** words, int amountOfWords, int* lengths){
    for (int i=0; i<amountOfWords; i++){
        for (int j=0; j<lengths[i]-1; j++)
            fprintf(fout, "%c", words[i][j]);
        fprintf(fout, " ");};
    return;}

int main(){
    char** words; int* lengths; int amountOfWords = 0;
    FILE *fin, *fout = fopen("output_file.txt", "w");
    if ( !( fin = fopen ("input_file.txt", "r") ) ) {fprintf(fout, "Cannot open input file.");} else {
        readStringFromFile(fin, words, amountOfWords, lengths);
        sort(words, amountOfWords, lengths);
        outputWordsToFile(fout, words, amountOfWords, lengths);
    }
    fclose(fin);
    fclose(fout);
    return 0;}