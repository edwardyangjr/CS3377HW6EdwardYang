//Edward Yang
//eiy160030
//cs 3377.502
//4/24/18

#include <iostream>
#include "cdk.h"
#include <stdint.h>
#include <fstream>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;

class BinaryFileHeader
{
  public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

int main()
{
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  
  ifstream binInfile("cs3377.bin", ios::in | ios::binary);
  if(!binInfile.is_open()){
    cerr << "Binary File error." << endl;
    exit(-1);
  }

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
 
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  //setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  char* currentLine = new char[256];
  sprintf(currentLine, "Magic: 0x%X", myHeader->magicNumber);
  setCDKMatrixCell(myMatrix, 1, 1, currentLine);

  sprintf(currentLine, "Version: %u", myHeader->versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, currentLine);

  sprintf(currentLine, "NumRecords: %lu", myHeader->numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, currentLine);
  
  //sprintf(currentLine, "%s", myHeader);
  //setCDKMatrixCell(myMatrix, 2, 1, currentLine);
  
  drawCDKMatrix(myMatrix, true);    // needed

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
