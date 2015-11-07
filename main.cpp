/* 
 * File:   main.cpp
 * Author: Konstantinos Krestenitis
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    char *plainText = new char[30];
    strcpy(plainText,"BILL GATES\0");
    
    double freqOfplainText[30]= {0}, sumOfFreq=0;
    bool checkedLetter[30] = {0};
    //calculate freq
    for(int i=0;i<strlen(plainText);i++){
        for(int x=0; x<strlen(plainText);x++){
            if((plainText[i] == plainText[x]) && checkedLetter[x]!=true){
                freqOfplainText[i]++;
                sumOfFreq++;
                checkedLetter[x] = true;
            }
        }
    }
    double cut= (double)1/(double)sumOfFreq;
    printf("Sum of freq:%f. Size of cuts:%f\n", sumOfFreq, cut);
    
    char *letters = new char[30];
    double freq[30],*lowerRangesl = new double[30], *upperRangesl = new double[30];
    lowerRangesl[0]= 0.0;
    upperRangesl[0]= (freqOfplainText[0]* cut);
    int counter=0;
    for(int i=0;i<strlen(plainText);i++) {
        if(freqOfplainText[i]!=0) {
            letters[counter] = plainText[i];
            freq[counter]= freqOfplainText[i];
            ///////////assign lower-upper ranges to individual letters
            lowerRangesl[counter] = upperRangesl[counter - 1];
            upperRangesl[counter] = lowerRangesl[counter]+(freq[counter++] * cut);
            printf("Char:%c Freq:%f.\n", plainText[i], freqOfplainText[i]);
        }
    }
    letters[counter]='\0';

    printf("\n");
    double *lowerRanges = new double[30];
    double *upperRanges = new double[30];
    for (int x = 0; x < strlen(plainText); x++) {
        for (int i = 0; i < strlen(letters); i++) {
            if (plainText[x] == letters[i]) {
                lowerRanges[x] = lowerRangesl[i];
                upperRanges[x] = upperRangesl[i];
            }
        }
        printf("%i - Char:%c :lowerRange:%f upperRange:%f\n",x, plainText[x], lowerRanges[x],upperRanges[x]);
    }
    
    //encoding
    double low=0.0, high=1.0;
    for(int i=0;i<strlen(plainText);i++) {
        double range = high - low;
        high = low + upperRanges[i] * range;
        low = low + lowerRanges[i] * range;
        printf("Encoding: %i: ch:%c low:%f high:%f.\n", i, plainText[i], low, high);
    }
    printf("ENCODED VALUE:%f\n",low);
    
    char *decodedText = new char[30];
    counter=0;
    //decoding
    for (int i = 0; i < strlen(plainText); i++) {
        if ((low > lowerRanges[i] || (int)low==(int)lowerRanges[i]) && (low<upperRanges[i])) {
            decodedText[counter++] = plainText[i];
            low = (low - lowerRanges[i]) / (upperRanges[i] - lowerRanges[i]);
            printf("Decoded char:%c LOW:%f\n", plainText[i], low);
        }
    }
    return 0;
}