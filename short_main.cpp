#include <stdio.h> 
#include <string.h>//Konstantinos Krestenitis - Arithmetic Coding
int main(int argc, char** argv) {
    char *plainText = new char[30]; strcpy(plainText,"BILL GATES\0");
    double freqOfuniqueChars[30]= {0}, sumOfFreq=0, cut, *lowerRanges = new double[strlen(plainText)], *upperRanges = new double[strlen(plainText)], low, up;
    bool isCheckedLetter[30] = {0};
    for(unsigned char i=0;i<strlen(plainText);i++)
        for(unsigned char x=0; x<strlen(plainText);x++)
            if((plainText[i] == plainText[x]) && isCheckedLetter[x]!=true) {
                freqOfuniqueChars[i]++;
                sumOfFreq++;
                isCheckedLetter[x] = true;
            } printf("Sum of freq:%f. Size of cuts:%f\n", sumOfFreq, cut= (double)1.0/sumOfFreq);
	lowerRanges[0] = low = 0.0; upperRanges[0] = up= (freqOfuniqueChars[0]* cut);
    for(unsigned char i=1;i<strlen(plainText);i++) { if(freqOfuniqueChars[i]!=0) up = (low = up) +(freqOfuniqueChars[i]*cut);
		lowerRanges[i] = low;
        upperRanges[i] = up;
	} low=0.0; up=1.0;
    for(unsigned char i=0;i<strlen(plainText);i++) { 
		double range = up - low;
        up = low + upperRanges[i] * range;
        low = low + lowerRanges[i] * range;
        printf("Encoding: %i: ch:%c up:%f low:%f. :lowR:%f upR:%f\n", i, plainText[i], up, low, lowerRanges[i], upperRanges[i]);
    }
    for (unsigned char i = 0; i < strlen(plainText); i++) 
		if ((low > lowerRanges[i] || (int)low==(int)lowerRanges[i]) && (low<upperRanges[i])) 
			printf("Decoded char:%c LOW:%f\n", plainText[i], low = (low - lowerRanges[i]) / (upperRanges[i] - lowerRanges[i]));
    return 0;
}