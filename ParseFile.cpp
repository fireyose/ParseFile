/*******************************************************************/
/*                                                                 */
/*    - Author:       Youssef Almkari                              */
/*    - Course:       CSC136                                       */
/*    - Project:      #1                                           */
/*    - Due Date:     September 12, 2013                           */
/*    - File name:    p1.cpp                                       */
/*    - Purpose:      To determine the number of characters,       */
/*                      tokens(words), and paragraphs in a file    */
/*                                                                 */
/*******************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

/** Prototypes **/

bool openFile (ifstream &, string &);           // Opens file, returns true or false
void charCount (ifstream &, int &, int &);      // Counts characters and paragraphs
void wordCount (ifstream &, int*);              // Holds word counts and length in array
int arraySum (int*, int &);                     // Adds the elements in array
void output (string &, int &, int &, int*);     // Outputs final results

int main()
{
  ifstream infile;                               // Declare infile as type input file stream class
  string fileName;                               // Will contain user input file name
  int numChar = 0;                               // Will contain number of characters
  int numNewLines = 0;                           // Will contain number of new lines (paragraphs)
  // Array that will keep count of:
  // the size and amount of words in input file
  int count[10];

  if (openFile (infile, fileName)) {                 // Checks if file was successfully is open
    charCount (infile, numChar, numNewLines);        // Count char and newlines
    // Rewinds the data file
    infile.close();
    infile.clear();
    infile.open (fileName.c_str());
    // End of rewind

    wordCount (infile, count);                       // Store size of words in array
    output (fileName, numChar, numNewLines, count);  // Output final results
  }

  return 0;
}

/** Functions **/

/*************************************************************************/
/*                                                                       */
/*   -Function Name:   openFile                                          */
/*                                                                       */
/*   -Description:     Prompts user for file name                        */
/*                     Checks if file exists                             */
/*                     If so, continue. If not, terminate.               */
/*                                                                       */
/*   -Parameters:      ifstream &inf    - opens and holds file stream    */
/*                     string &fileName  - INPUT - Stores file name      */
/*                                                                       */
/*   -Return Value:    true or false                                     */
/*                                                                       */
/*************************************************************************/

bool openFile (ifstream &inf, string &fileName)
{
  cout << "Enter file name: > ";         // Ask user for file name
  cin >> fileName;                       // Inserts name in string "fileName"
  inf.open(fileName.c_str());            // Opens file

  // Checks if the file exists
  if (inf.fail()) {
    cout << "FILE NOT FOUND" << endl << endl;     // File was not successfully found
    return false;                                 // Bool returns false, program exists
  } else {
    cout << "FILE FOUND" << endl << endl;          // File successfully streaming under "infile"
    return true;                                   // Bool returns true, program continues
  }
}

/*************************************************************************/
/*                                                                       */
/*   -Function Name:   charCount                                         */
/*                                                                       */
/*   -Description:     Read file char by char until end of file          */
/*                     If char is '\n' new line add to newLine           */
/*                     Else continue reading and incrementing numChar    */
/*                                                                       */
/*   -Parameters:      ifstream &inf    - Holds file stream              */
/*                     int &numChar     - Holds number of characters     */
/*                     int &newLine     - Holds number of new lines      */
/*                                                                       */
/*   -Return Value:    NONE                                              */
/*                                                                       */
/*************************************************************************/

void charCount (ifstream &inf, int &numChar, int &newLine)
{
  char ch;
  inf.get(ch);                  // Read first character from "inf" stream
  // Loop until the end of file
  while (!inf.eof())
    if (ch == '\n') {           // Check if character is a new line (\n)
    newLine++;                  // If new line character: increment number of "newLine"
    inf.get(ch);                // Continue reading from file
    } else {
      numChar++;              // Character is NOT new line, increment "numChar"
      inf.get(ch);            // Continue reading from file stream
    }
}

/*************************************************************************/
/*                                                                       */
/*   -Function Name:   wordCount                                         */
/*                                                                       */
/*   -Description:     Sets all elements in count[] array to zero        */
/*                     Reads from file and stores word count in array    */
/*                     If so, continue. If not, terminate.               */
/*                                                                       */
/*   -Parameters:      ifstream &inf    - Holds file stream              */
/*                     int count[]      - Array that holds word counts   */
/*                                                                       */
/*   -Return Value:    NONE                                              */
/*                                                                       */
/*************************************************************************/

// Counts the number and amount of words and stores them in array respectively
void wordCount (ifstream &inf, int count[])
{
  // Sets array elements to zero
  for (int i = 0; i < 10; i++)
    count[i] = 0;

  // Read and store words until end of file
  string word;
  inf >> word;
  while (!inf.eof()) {
    if (word.size() >= 10) {           // Checks if word size is equal to or bigger than zero
      count[0]++;                // count[0] increments if true
      inf >> word;               // Continue reading from file stream
    } else {
      count[word.size()]++;      // Word size is less than ten
      inf >> word;               // Continue reading from file stream
    }
  }
}

/*************************************************************************/
/*                                                                       */
/*   -Function Name:   arraySum                                          */
/*                                                                       */
/*   -Description:     Adds elements in array                            */
/*                                                                       */
/*   -Parameters:      int count[]      - Holds word counts              */
/*                     int &totalWords  - Holds total number or words    */
/*                                                                       */
/*   -Return Value:    int totalWords                                    */
/*                                                                       */
/*************************************************************************/

int arraySum (int count[], int &totalWords)
{
  // Adds array elements to "totalWords"
  for (int i = 0; i < 10; i++)
    totalWords += count[i];

  return totalWords;
}

/*********************************************************************************/
/*                                                                               */
/*   -Function Name:   output                                                    */
/*                                                                               */
/*   -Description:     ouputs final results                                      */
/*                                                                               */
/*   -Parameters:      string &fileName  - OUTPUT - Stores file name             */
/*                     int &numChar      - OUTPUT - Holds number of characters   */
/*                     int &newLines     - OUTPUT - Holds number of newLines     */
/*                     ont &count[]      - OUTPUT - Holds word counts            */
/*                                                                               */
/*   -Used Functions:  arraySum (count[], words) - Outputs total number of words */
/*                                                                               */
/*   -Return Value:    NONE                                                      */
/*                                                                               */
/*********************************************************************************/

void output (string &fileName, int &numChar, int &newLines, int count[])
{
  int words = 0;
  cout << "File: " << fileName << "    ";
  cout << "Characters: " << numChar << "    ";
  cout << "Words: " << arraySum (count, words) << "    ";
  cout << "Paragraphs: " << newLines << "    " << endl << endl;
  cout << "Size:     10+ 1   2   3   4   5   6   7   8   9" << endl;
  cout << "#Words:   ";
  for (int i = 0; i < 10; i++)
    cout << count[i] << "   ";
  cout << endl;
}
