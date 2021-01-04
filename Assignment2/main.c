/*
	Student name: Tinghui Zhang
	Panther ID: 6144880
	~Affirmation of Originality: I affirm that I wrote this program myself without any help 
	from any other people or sources from the internet.
	~Program Description: This program will manipulate image from a 24-bit uncompressed bmp 
	file. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bmplib.h"

/*
 * This method enlarges a 24-bit, uncompressed .bmp file
 * that has been read in using readFile()
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the original number of rows
 * cols     - the original number of columns
 *
 * scale    - the multiplier applied to EACH OF the rows and columns, e.g.
 *           if scale=2, then 2* rows and 2*cols
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows (scale*rows)
 * newcols  - the new number of cols (scale*cols)
 */
int enlarge(PIXEL* original, int rows, int cols, int scale,
	    PIXEL** new, int* newrows, int* newcols)
{
	/* THIS IS THE METHOD THAT YOU SHOULD WRITE */
	int row, col, scaledcol, scaledrow;
	if ((rows <= 0) || (cols <= 0)) return -1;
	
	*newrows = scale*rows;
	*newcols = scale*cols;
	*new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));
	for (row=0; row < rows; row++) {
		for(scaledcol=0; scaledcol<scale; scaledcol++){
			for (col=0; col < cols; col++) {
				for(scaledrow=0; scaledrow<scale; scaledrow++){
					PIXEL* o = original + row*cols + col;
					PIXEL* n = (*new) + row*cols*scale*scale + cols*scale*scaledcol + col*scale + scaledrow;
					*n = *o;
				}
			}
		}
	}
	return 0;
}

/*
 * This method rotates a 24-bit, uncompressed .bmp file that has been read
 * in using readFile(). The rotation is expressed in degrees and can be
 * positive, negative, or 0 -- but it must be a multiple of 90 degrees
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 * rotation - a positive or negative rotation,
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows
 * newcols  - the new number of cols
 */
int rotate(PIXEL* original, int rows, int cols, int rotation,
	   PIXEL** new, int* newrows, int* newcols)
{
  /* THIS IS THE METHOD THAT YOU SHOULD WRITE */
	int row, col;
	int clockwise = 0;
	while(rotation < 0)
		rotation += 360;
	clockwise = rotation / 90 % 4;
	if ((rows <= 0) || (cols <= 0)) return -1;
	
	if(clockwise == 0)
	{
		
		*newrows = rows;
		*newcols = cols;
		*new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));
		for (row=0; row < rows; row++)
			for (col=0; col < cols; col++)
			{
				PIXEL* o = original + row*cols + col;
				PIXEL* n = (*new) + row*cols + col;
				*n = *o;
			}
	}
	else if(clockwise == 1)
	{
		
		*newrows = cols;
		*newcols = rows;
		*new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));
		for (row=0; row < rows; row++)
			for (col=0; col < cols; col++)
			{
				PIXEL* o = original + row*cols + col;
				PIXEL* n = (*new) + cols*rows - col*rows - rows + row;
				*n = *o;
			}
	}
	else if(clockwise == 2)
	{
		
		*newrows = rows;
		*newcols = cols;
		*new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));
		for (row=0; row < rows; row++)
			for (col=0; col < cols; col++) {
				PIXEL* o = original + row*cols + col;
				PIXEL* n = (*new) + rows*cols - row*cols - col - 1;
				*n = *o;
			}
	}
	else if(clockwise == 3)
	{
		*newrows = cols;
		*newcols = rows;
		*new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));
		for (row=0; row < rows; row++)
		for (col=0; col < cols; col++) {
		  PIXEL* o = original + row*cols + col;
		  PIXEL* n = (*new) + (rows - 1 - row) + col*rows;
		  *n = *o;
		}
	}
	return 0;
}

/*
 * This method Vertically flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile().
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */

int verticalflip (PIXEL *original, PIXEL **new, int rows, int cols)
{
  /* THIS IS THE METHOD THAT YOU SHOULD WRITE */
	
	int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  for (row=0; row < rows; row++)
    for (col=0; col < cols; col++) {
      PIXEL* o = original + row*cols + col;
      PIXEL* n = (*new) + (rows-1-row)*cols + col;
      *n = *o;
    }

  return 0;
}


/*
 * This method horizontally flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile().
 *
 * THIS IS GIVEN TO YOU SOLELY TO LOOK AT AS AN EXAMPLE
 * TRY TO UNDERSTAND HOW IT WORKS
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */
int flip (PIXEL *original, PIXEL **new, int rows, int cols)
{
  int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  for (row=0; row < rows; row++)
    for (col=0; col < cols; col++) {
      PIXEL* o = original + row*cols + col;
      PIXEL* n = (*new) + row*cols + (cols-1-col);
      *n = *o;
    }

  return 0;
}

int main(int argc, char **argv)
{
	extern char *optarg;
	int opt, err = 0; 
	int sFlag = 0, rFlag = 0, fFlag = 0, vFlag = 0, oFlag = 0;
	int scale, degree;
	char* outfile;
	char* infile = NULL;
	int r, c, newRow, newColomn;
	PIXEL *b, *nb;
	static char usage[] = "Usage: %./bmptool [-s scale | -r degree | -f | -v ] [-o output_file] [input_file]\n";
	/*
		use getopt() to check options in the command line input.
		assign 1 to err, if getopt() returns to '?'.
	*/
	while ((opt = getopt(argc, argv, "s:r:fvo:")) != -1)
	{
		switch (opt) {
		case 's':
			sFlag = 1;
			scale = atoi(optarg);
			break;
		case 'r':
			rFlag = 1;
			degree = atoi(optarg);
			break;
		case 'f':
			fFlag = 1;
			break;
		case 'v':
			vFlag = 1;
			break;
		case 'o':
			oFlag = 1;
			outfile = optarg;
			break;
		case '?':
			err = 1;
			break;
		}
	}
	/*
		Print message and stop the program when there has no options
		in the command line, that is, when getopt() returns '?'.
	*/
	if(err == 1)
	{
		printf("Error: wrong option or wrong usage.\n");
		printf("%s", usage);
		exit(-1);
	}
	if(strcmp(argv[argc - 1], "bmptool") == 0)
	{
		printf("command line need at least one option.\n");
		printf("%s", usage);
		exit(-1);
	}
	/*
		find input file from command line arguments and read, read null
		if chained commands happened. 
	*/
	if(strcmp(argv[argc - 1], "-f") == 0 || strcmp(argv[argc - 1], "-v") == 0 || strcmp(argv[argc - 2], "-s") == 0
	|| strcmp(argv[argc - 2], "-r") == 0 || strcmp(argv[argc - 2], "-o") == 0)
	{
		readFile(NULL, &r, &c, &b);
	}
	else
	{
		infile = argv[argc - 1];
		readFile(infile, &r, &c, &b);
	}
	
	//enlarge the image with specified scale if get 1 for sFlag.
	if(sFlag == 1)
	{
		enlarge(b, r, c, scale, &nb, &newRow, &newColomn);
		r = newRow;
		c = newColomn;
		b = nb;
	}
	//rotate the image with specified degree if get 1 for rFlag.
	if(rFlag == 1)
	{
		rotate(b, r, c, degree, &nb, &newRow, &newColomn);
		r = newRow;
		c = newColomn;
		b = nb;
	}
	// flip the image vertically if get 1 for vFlag
	if(vFlag == 1)
	{
		verticalflip(b, &nb, r, c);
		b = nb;
	}
	//flip the image horizontally if get 1 for fFlag.
	if(fFlag == 1)
	{
		flip(b, &nb, r, c);
		b = nb;
	}
	/*
		output to file if oFlag = 1
		if no output file specified, write null to pipe commands.
	*/
	if(oFlag != 1)
	{
		writeFile(NULL, r, c, nb);
	}
	else
	{
		writeFile(outfile, r, c, nb);
	}
	//free memory.
	free(nb);
	return 0;
}