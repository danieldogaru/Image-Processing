# include "PRIMARY.h"

class PIXEL: public PRIMARY
{	
	private:

		unsigned char G, B;

	public:
		// Constructors

		PIXEL(){};
		PIXEL(unsigned char r, unsigned char g, unsigned char b) :G(g), B(b)
		{
			R = r;
		};

		//Destructor
		~PIXEL(){};

		// Operators

		PIXEL& operator=( const PIXEL& );

		const PIXEL operator+( const PIXEL& ) const;
		const PIXEL operator/( int ) const ;
		const PIXEL operator*( double ) const ;


		// Methods;

		//PIXEL divide( int );

		void multiply(float, float, float);
		void setR( unsigned char);
		void setG( unsigned char);
		void setB( unsigned char);
		unsigned char getR();
		unsigned char getG();
		unsigned char getB();
};

PIXEL& PIXEL::operator=(const PIXEL& p)
{
	R = p.R;
	G = p.G;
	B = p.B;

	return *this;
}

const PIXEL PIXEL::operator+(const PIXEL& p) const
{
	return PIXEL(R + p.R, G + p.G, B + p.B);
}

const PIXEL PIXEL::operator/(int n) const
{
	return PIXEL(R / n, G / n, B / n);
}

const PIXEL PIXEL::operator*(double n) const
{
	return PIXEL(R*n, G*n, B*n);
}

unsigned char PIXEL::getR()
{
	return this->R;
}

unsigned char PIXEL::getG()
{
	return this->G;
}

unsigned char PIXEL::getB()
{
	return this->B;
}

void PIXEL::multiply(float r, float g, float b)
{
	this->R *= r;
	this->G *= g;
	this->B *= b;
}

void PIXEL::setR(unsigned char r)
{
	this->R = r;
};

void PIXEL::setG(unsigned char g)
{
	this->G = g;
};

void PIXEL::setB(unsigned char b)
{
	this->B = b;
};