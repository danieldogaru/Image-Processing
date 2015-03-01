// Using STL - no more need for IMAGE::MEMALOC()
#pragma pack(1) 

# include "PIXEL.h"
# include <vector>
class IMAGE
{
	private:

		struct 
		{
			unsigned char  fileMarker1;       /* 'B' */                       
    		unsigned char  fileMarker2;       /* 'M' */ 

			//UNUSED
			unsigned int   bfSize;             
   			unsigned short unused1;           
    		unsigned short unused2;           
    		unsigned int   imageDataOffset;  /* Offset to the start of image data */
			
		} FILEHEADER;

		struct 
		{
			unsigned int   biSize; // UNUSED

			signed int	   width;            /* Width of the image */ 
    		signed int     height;           /* Height of the image */ 

    		//UNUSED
    		unsigned short planes;             
    		unsigned short bitPix;             
    		unsigned int   biCompression;      
    		unsigned int   biSizeImage;        
    		int            biXPelsPerMeter;    
    		int            biYPelsPerMeter;    
    		unsigned int   biClrUsed;          
    		unsigned int   biClrImportant;    

		} INFOHEADER;

		vector< vector<PRIMARY> > primaryArray;
		vector< vector<PIXEL> > pixelArray;

	public:

		IMAGE( char* );  		/* Constructor */
		IMAGE();			    /* Default Constructor */
		~IMAGE(){}; 			/* Destructor */

		//Methods
			//FILEHEADER Methods

			unsigned char   getFileMarker( int ) 	const; 
			unsigned int    getImageDataOffset()     const;

			//INFOHEADER Methods

			unsigned int 	getWidth()  			const;
    		unsigned int 	getHeight() 			const;

    		//METHODS

    	void BLUR();
    	void SKETCH();
    	void EXPORT(char*);
    	void EXPORT_GRAY(char*);
    	void MEMALLOC( vector< vector<PIXEL> > );
    	void CROP( int, int, signed int, signed int);
    	void BLACK_WHITE();
    	void GRAYSCALE_AUTO_CONTRAST(); // Contrast stretching
    	void GRAYSCALE_LOGARITHM_OPERATOR();

    	friend IMAGE& IMAGE_BLENDING( const IMAGE& , const IMAGE& , double, char*); //mix 2 images of same size

};