#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  // input file names can be specified here
  char file1[100] = "Hotels.txt";
  char file2[100] = "Seattle.txt";

  // variables pertaining to file1 - here: Hotels.txt (input)
  int lineNum1 = 0;    // counter to monitor number of lines in file1
  char arr1[100][100]; // string array to store the contents from file1
  int i = 0;           // iterator for the sting array
  char temp1str[100]; // temp string for concatenating page name and rank number
  int charPos1; // variables for extracting rank numbers from the concatenated
                // string
  char *chPtr1;

  // variables pertaining to file2 - here: Seattle.txt (input)
  int lineNum2 = 0;    // counter to monitor number of lines in file2
  char arr2[100][100]; // string array to store the contents from file2
  int j = 0;           // iterator for the sting array
  char temp2str[100]; // temp string for concatenating page name and rank number
  int charPos2; // variables for extracting rank numbers from the concatenated
                // string
  char *chPtr2;

  // variables pertaining to file3 - here: result.txt (output)
  int lineNum3 = 0;    // counter to monitor number of lines in file3
  char arr3[100][100]; // string array to store the content of results before
                       // writing to file3
  int k = 0;           // iterator for the sting array
  char temp3str[100]; // variable for swapping the contents of array for sorting

  // variables to implement logic - pick common entries and sort them out
  int p, q; // iterators used in for-loops in bubble sorting technique
  int rank, rank1, rank2,
      ranktmp;       // variables used to sort pages according to their ranks
  char rankStr[100]; // variable used to convert rank from int to str type

  // file handling for file1 - Hotels.txt (opened in read mode)
  FILE *fptr1 = fopen(file1, "r");
  if (fptr1 == NULL) {
    printf("Error in file inputs!!!");
    exit(0);
  }

  // writing contents of file1 into a string array and incrementing line counter
  while (fscanf(fptr1, "%s ", &arr1[i++]) == 1) {
    lineNum1++;
  }

  // closing file1
  fclose(fptr1);

  // file handling for file2 - Seattle.txt (opened in read mode)
  FILE *fptr2 = fopen(file2, "r");
  if (fptr2 == NULL) {
    printf("Error in file inputs!!!");
    exit(0);
  }

  // writing contents of file2 into a string array and incrementing line counter
  while (fscanf(fptr2, "%s ", &arr2[j++]) == 1) {
    lineNum2++;
  }

  // closing file2
  fclose(fptr2);

  // logic for picking out common table entries and computing their cumulative
  // ranks
  for (i = 0; i < lineNum1; i = i + 2) {
    for (j = 0; j < lineNum2; j = j + 2) {
      if (strcmp(arr1[i], arr2[j]) ==
          0) { // checking if the page names are the same
        rank = atoi(arr1[i + 1]) +
               atoi(arr2[j + 1]); // computing cumulative ranks for common pages
        sprintf(rankStr, "%d",
                rank); // converting rank value from int type to str type
        strcpy(arr3[k++],
               strcat(strcat(arr1[i], " "),
                      rankStr)); // adding the values into another string array
        lineNum3++;
      }
    }
  }

  // logic for sorting out table entries based on their cumulative rank values
  // using bubble sort technique
  for (p = 0; p < (lineNum3 - 1); p++) {
    memset(temp1str, ' ', strlen(temp1str)); // resetting temp str before
                                             // copying values in each iteration
    chPtr1 = NULL; // resetting char pointer before assigning values in each
                   // iteration
    chPtr1 = strchr(arr3[p], ' ');
    charPos1 = (int)(chPtr1 - arr3[p]);
    rank1 = atoi(strncpy(temp1str, &arr3[p][charPos1],
                         ((int)strlen(arr3[p]) - charPos1)));
    ranktmp = rank1;

    for (q = p + 1; q < lineNum3; q++) {
      memset(temp2str, ' ',
             strlen(temp2str)); // resetting temp str before copying values in
                                // each iteration
      chPtr2 = NULL; // resetting char pointer before assigning values in each
                     // iteration
      chPtr2 = strchr(arr3[q], ' ');
      charPos2 = (int)(chPtr2 - arr3[q]);
      rank2 = atoi(strncpy(temp2str, &arr3[q][charPos2],
                           ((int)strlen(arr3[q]) - charPos2)));

      // swapping the table entries to arrange them in descending order
      if (ranktmp < rank2) {
        strcpy(temp3str, arr3[p]);
        strcpy(arr3[p], arr3[q]);
        strcpy(arr3[q], temp3str);
        ranktmp = rank2;
      }
    }
  }

  // file handling for file3 - result.txt (opened in write mode)
  FILE *fptr3 = fopen("result.txt", "w");
  if (fptr3 == NULL) {
    printf("Error in opening and writing into result file!!!");
    exit(0);
  }

  // writing out result table entries into file 3 - result.txt
  for (i = 0; i < lineNum3; i++) {
    fprintf(fptr3, "%s\n", arr3[i]);
  }

  // closing file 3
  fclose(fptr3);

  // displaying success message on the console
  printf("Execution successful! Please check result.txt file. \n");

  return 0;
}