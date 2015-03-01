// Commented code was used before using STL
// Using STL - no more need for IMAGE::MEMALOC()

# pragma once
# include "IMAGE.h"
# include <cstdlib>
# include <cstring>
# include <string>
# include <fstream>
# include <math.h>
# include <vector>

typedef vector<PIXEL>				::iterator	p_iterator;
typedef vector<PRIMARY>				::iterator	pr_iterator;

typedef vector< vector<PIXEL> >		::iterator	P_iterator;
typedef vector< vector<PRIMARY> >	::iterator	PR_iterator;


using namespace std;

// CONSTRUCTORS

IMAGE::IMAGE( char *imageName)
{

	FILE *f;
	f = fopen(imageName, "rb");

	fseek(f, 0, SEEK_SET);

 	fread( &FILEHEADER, sizeof(FILEHEADER), 1,  f);
 	fread( &INFOHEADER, sizeof(INFOHEADER), 1,  f);


	// Mem alloc for pixelArray
	//pixelArray = new PIXEL* [ INFOHEADER.height ];
		//for( int i=0; i < INFOHEADER.height ; i++)
			//pixelArray[i] = new PIXEL[ INFOHEADER.width ];

	fseek(f,FILEHEADER.imageDataOffset,SEEK_SET);

 
 	cout << "READ SUCCESS1" << INFOHEADER.width << INFOHEADER.height;
 	
	vector<PIXEL> line;
	for(int i=INFOHEADER.height-1; i >= 0; i--) 
	{
		unsigned char R, G, B;
	
   		for(int j=0; j<INFOHEADER.width; j++) 
   		{ 
			
   			fread( & B, sizeof(unsigned char), 1,  f);
   			fread( & G, sizeof(unsigned char), 1,  f);
   			fread( & R, sizeof(unsigned char), 1,  f);

			PIXEL P( R, G, B );
			line.push_back(P);
   		}

		pixelArray.push_back(line);

		line.clear();
	}
	
	cout << "READ SUCCESS";
	fclose(f);

	// Using C++ fstream
	/*fstream f;

	f.open( imageName, ios::in | ios::binary );
	f.seekg(0, ios::beg);

	f.read( (char*)&FILEHEADER, sizeof(FILEHEADER) );
	f.read( (char*)&INFOHEADER, sizeof(INFOHEADER) );

	cout << INFOHEADER.width << " " << INFOHEADER.height;

	pixelArray = new PIXEL* [ INFOHEADER.height ];
		for( int i=0; i < INFOHEADER.height ; i++)
			pixelArray[i] = new PIXEL[ INFOHEADER.width ];

	f.seekg(FILEHEADER.imageDataOffset, ios::beg);

	for(int i=INFOHEADER.height-1; i >= 0; i--) 
   		for(int j=0; j<INFOHEADER.width; j++) 
   		{
   			f.read( (char*)&pixelArray[i][j].B, sizeof(unsigned char));
   			f.read( (char*)&pixelArray[i][j].G, sizeof(unsigned char));
   			f.read( (char*)&pixelArray[i][j].R, sizeof(unsigned char));
   		}
	*/
   	//f.close();
}

IMAGE::IMAGE()
{
	cout<<"Default constructor!";
}

//METHODS
unsigned char IMAGE::getFileMarker( int n ) const
{
	if( n == 1)
		return this->FILEHEADER.fileMarker1;

	else if( n == 2)
		return this->FILEHEADER.fileMarker2;

	else
	{
		cout<<" Invalid use of function getFileMarker() ";
		return 0;
	}

}
	
void IMAGE::EXPORT( char *fileName )
{
	FILE *f;
	f = fopen(fileName, "wb");
	fprintf(f,"P2\n%d %d\n255\n", INFOHEADER.width , INFOHEADER.height );


	for ( P_iterator it_l = pixelArray.begin(); it_l != pixelArray.end(); it_l++)
	{
		for ( p_iterator it_c = it_l->begin(); it_c != it_l->end(); it_c++)
			fprintf(f, "%d %d %d", (*it_c).getR(), (*it_c).getG(), (*it_c).getB());

		fprintf(f, "\n");
	}
		
	fclose(f);

	/*	for( int i=0; i<INFOHEADER.height; i++){
		 	for(int j=0; j<INFOHEADER.width; j++)
				fprintf(f,"%d %d %d ", pixelArray[i][j].getR() ,pixelArray[i][j].getG(), pixelArray[i][j].getB() );
			fprintf(f, "\n");		
		}*/	
}

void IMAGE::EXPORT_GRAY(char* fileName)
{
	FILE *f;
	f = fopen(fileName, "wb");
	fprintf(f,"P2\n%d %d\n255\n", INFOHEADER.width , INFOHEADER.height );

	for (PR_iterator it_l = primaryArray.begin(); it_l != primaryArray.end(); it_l++)
	{
		for (pr_iterator it_c = it_l->begin(); it_c != it_l->end(); it_c++)
			fprintf(f, "%d", (*it_c).getR());
		fprintf(f, "\n");
	}

	fclose(f);
	/*
		for( int i=0; i<INFOHEADER.height; i++) 
		{
		 	for(int j=0; j<INFOHEADER.width; j++)
				fprintf(f,"%d ", primaryArray[i][j].getR());

			fprintf(f, "\n");
		}
	*/	
}

void IMAGE::SKETCH()
{
	for( int i=0; i<INFOHEADER.height; i++ )
		for( int j=0; j<INFOHEADER.width; j++ )

			{
			 	if( i==0 && j==0 ) // Upper left corner
			 		pixelArray[i][j] = ( pixelArray[i][j+1] + pixelArray[i+1][j] ) / 2;

			 	else if ( i==INFOHEADER.height-1 && j==0 ) // Lower left corner
			 		pixelArray[i][j] = ( pixelArray[i][j+1] + pixelArray[i-1][j] ) / 2;

			 	else if ( i==0 && j==INFOHEADER.width-1 ) // Upper right corner
			 		pixelArray[i][j] = ( pixelArray[i][j-1] + pixelArray[i+1][j] ) / 2; 

			 	else if ( i==INFOHEADER.height-1 && j==INFOHEADER.width-1 ) // Lower right corner
			 		pixelArray[i][j] = ( pixelArray[i-1][j] + pixelArray[i][j-1] ) / 2;

			 	else if ( ( i==0 || i==(INFOHEADER.height-1) ) && ( j>0 && j<(INFOHEADER.width-1) ) ) // First or last line
			 		pixelArray[i][j] = ( pixelArray[ (i==0) ? (i+1) : (i-1) ][j] + pixelArray[i][j-1] + pixelArray[i][j+1] ) / 3;

			 	else if(  ( j==0 || j==INFOHEADER.width-1 )  && ( i>0 && i<(INFOHEADER.height-1) ) ) // First or last collumn
			 		pixelArray[i][j] = ( pixelArray[i-1][j] + pixelArray[i+1][j] + pixelArray[i][ ( j==0 ) ? (j+1) : (j-1) ] ) / 3;

			 	else
				 	 pixelArray[i][j] = ( pixelArray[i-1][j] + pixelArray[i+1][j] + pixelArray[i][j-1] + pixelArray[i][j+1] )/4;  
			}
}

void IMAGE::BLUR() // Still has some bugs
{
	/*PIXEL **P1;
	//this->MEMALLOC(P1);

	P1 = new PIXEL* [ INFOHEADER.height ];
		for( int i=0; i < INFOHEADER.height ; i++)
			P1[i] = new PIXEL[ INFOHEADER.width ];*/

	vector< vector<PIXEL> > P1;
	P1 = pixelArray;

	for( int i=0; i<INFOHEADER.height; i++ )
		for( int j=0; j<INFOHEADER.width; j++ )
			P1[i][j] = pixelArray[i][j];

	for( int i=0; i<INFOHEADER.height; i++ )
		for( int j=0; j<INFOHEADER.width; j++ )
			{	
			 	if( i==0 && j==0 ) // Upper left corner
			 		P1[i][j] = ( pixelArray[i][j+1] + pixelArray[i+1][j] ) / 2;

			 	else if ( i==INFOHEADER.height-1 && j==0 ) // Lower left corner
			 		P1[i][j] = ( pixelArray[i][j+1] + pixelArray[i-1][j] ) / 2;

			 	else if ( i==0 && j==INFOHEADER.width-1 ) // Upper right corner
			 		P1[i][j] = ( pixelArray[i][j-1] + pixelArray[i+1][j] ) / 2; 

			 	else if ( i==INFOHEADER.height-1 && j==INFOHEADER.width-1 ) // Lower right corner
			 		P1[i][j] = ( pixelArray[i-1][j] + pixelArray[i][j-1] ) / 2;

			 	else if ( ( i==0 || i==(INFOHEADER.height-1) ) && ( j>0 && j<(INFOHEADER.width-1) ) ) // First or last line
			 		P1[i][j] = ( pixelArray[ (i==0) ? (i+1) : (i-1) ][j] + pixelArray[i][j-1] + pixelArray[i][j+1] ) / 3;

			 	else if(  (j==0 || j==INFOHEADER.width-1)  && ( i>0 && i<(INFOHEADER.height-1) ) ) // First or last collumn
			 		P1[i][j] = ( pixelArray[i-1][j] + pixelArray[i+1][j] + pixelArray[i][ ( j==0 ) ? (j+1) : (j-1) ] ) / 3;

			 	else
				 	 P1[i][j] = ( pixelArray[i-1][j] + pixelArray[i+1][j] + pixelArray[i][j-1] + pixelArray[i][j+1] )/4;  
			}

		pixelArray = P1;
		/*
	for( int i=0; i<INFOHEADER.height; i++ )
		for( int j=0; j<INFOHEADER.width; j++ )
			pixelArray[i][j] = P1[i][j];*/
}

void IMAGE::CROP( int xpos, int ypos, int height, int width )
{
	if( ( INFOHEADER.height - height <= 0) || ( INFOHEADER.width - width <= 0) )
	{
		cout << "\n CROP: Invalid width/height! ";
		return;
	}

	else if( (xpos < 0 || xpos > this->INFOHEADER.width) || (ypos<0 || ypos > this->INFOHEADER.height ) )
	{
		cout <<" \n CROP: Invalid X or Y position!";
		return; 
	}

	// MEM Alloc for croppped pixel array
	vector< vector<PIXEL> > croppedArray;

	for (int i = 0; i<height; i++)
		for (int j = 0; j<width; j++)
			croppedArray[i][j] = pixelArray[i + ypos][j + xpos];
	
	this->INFOHEADER.height = INFOHEADER.height - ypos;
	this->INFOHEADER.width = INFOHEADER.width - xpos;

	pixelArray = croppedArray;

	/*PIXEL **croppedArray;
	croppedArray = new PIXEL* [ INFOHEADER.height - ypos];

	for( int i=0; i < ( INFOHEADER.height - ypos); i++)
		croppedArray[i] = new PIXEL[ INFOHEADER.width - xpos ];


	//Crop the image
	

	for( int i=0; i<height; i++)
		for( int j=0; j<width; j++)
			croppedArray[i][j] = pixelArray[i+ y_coord ][ j + x_coord];
			

	for(int i=0; i<INFOHEADER.height; i++)
		delete[] pixelArray[i];

	this->INFOHEADER.height = INFOHEADER.height - ypos;
	this->INFOHEADER.width  = INFOHEADER.width  - xpos;

	pixelArray = new PIXEL* [ INFOHEADER.height ];
		for( int i=0; i < INFOHEADER.height ; i++)
			pixelArray[i] = new PIXEL[ INFOHEADER.width ];


	for( int i=0; i< INFOHEADER.height; i++)
		for( int j=0; j<INFOHEADER.width; j++)
			pixelArray[i][j] = croppedArray[i][j];*/

}

void IMAGE::BLACK_WHITE()
{
	
	vector<PRIMARY> line;

	for ( P_iterator it_l = pixelArray.begin(); it_l != pixelArray.end(); it_l++)
	{
		for ( p_iterator it_c = it_l->begin(); it_c != it_l->end(); it_c++)
		{
			PRIMARY P(((*it_c).getR() + (*it_c).getG() + (*it_c).getB()) / 3);
			line.push_back(P);
		}

		primaryArray.push_back(line);
		line.clear();
	}

 /*	primaryArray = new PRIMARY* [INFOHEADER.height];

	for( int i=0; i<INFOHEADER.height; i++)
	{
		primaryArray[i] = new PRIMARY [ INFOHEADER.width ];

		for( int j=0; j<INFOHEADER.width; j++)
			primaryArray[i][j].setR( (pixelArray[i][j].getR() + pixelArray[i][j].getG() + pixelArray[i][j].getB())/3 );
	}
 */
}

/*void IMAGE::MEMALLOC( PIXEL** pixelArray)
{
	pixelArray = new PIXEL* [ INFOHEADER.height ];
		for( int i=0; i < INFOHEADER.height ; i++)
			pixelArray[i] = new PIXEL[ INFOHEADER.width ];
}*/

unsigned int IMAGE::getHeight() const
{
	return this->INFOHEADER.height;
}

unsigned int IMAGE::getWidth() const
{
	return this->INFOHEADER.width;
}

void IMAGE::GRAYSCALE_AUTO_CONTRAST()
{
	int min=255, max=0;

	for (PR_iterator it_l = primaryArray.begin(); it_l != primaryArray.end(); it_l++)
		for (pr_iterator it_c=it_l->begin(); it_c != it_l->end(); it_c++)
		{
			min = (*it_c).getR() < min ? (*it_c).getR() : min;
			max = (*it_c).getR() > max ? (*it_c).getR() : max;
		}

	for (PR_iterator it_l = primaryArray.begin(); it_l != primaryArray.end(); it_l++)
		for (pr_iterator it_c = it_l->begin(); it_c != it_l->end(); it_c++)
			(*it_c).setR( ((*it_c).getR() - min)*(255 / (max - min)));
		

	/* 
	for( int i=0; i<INFOHEADER.height; i++ )
		for( int j=0; j<INFOHEADER.width; j++)
		{
			if( primaryArray[i][j].getR() < min )
				min = primaryArray[i][j].getR();

			if( primaryArray[i][j].getR() > max )
				max = primaryArray[i][j].getR();
		}

	for( int i=0; i<INFOHEADER.height; i++ )
		for( int j=0; j<INFOHEADER.width; j++)
		{	
			unsigned char r = primaryArray[i][j].getR();

			primaryArray[i][j].setR(( r  - min )*( 255/(max-min)) );
		}
	*/
}

void IMAGE::GRAYSCALE_LOGARITHM_OPERATOR() //http://homepages.inf.ed.ac.uk/rbf/HIPR2/pixlog.htm
{	//Try this on black and white space pictures

	for (PR_iterator it_l = primaryArray.begin(); it_l != primaryArray.end(); it_l++)
		for (pr_iterator it_c = it_l->begin(); it_c != it_l->end(); it_c++)
			(*it_c).setR( log( (*it_c).getR() ) );
	/*
	for( int i=0; i<INFOHEADER.height; i++ )
		for( int j=0; j<INFOHEADER.width; j++)
		{	
			unsigned char r = primaryArray[i][j].getR();
			primaryArray[i][j].setR( log(r) );
		}
	*/
}

/*
IMAGE& IMAGE_BLENDING( IMAGE &img1, IMAGE &img2, double ratio, char *fileName )
{
	IMAGE *temp = new IMAGE(fileName); // just temp

	int width = temp->getWidth(), height = temp->getHeight();

	for( int i=0; i<height; i++)
		for( int j=0; j<width; j++)
		{
			temp->pixelArray[i][j].setR((img1.pixelArray[i][j].getR()*ratio) + img2.pixelArray[i][j].getR()*(1-ratio));

			temp->pixelArray[i][j].setG((img1.pixelArray[i][j].getG()*ratio) + img2.pixelArray[i][j].getG()*(1-ratio));
				
			temp->pixelArray[i][j].setB((img1.pixelArray[i][j].getB()*ratio) + img2.pixelArray[i][j].getB()*(1-ratio));
		}

	return *temp;
}*/