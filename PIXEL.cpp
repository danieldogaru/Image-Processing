# include "PIXEL.h"

PIXEL::PIXEL( unsigned char R, unsigned char G, unsigned char B )
{
	this->R = R;
	this->G = G;
	this->B = B;
}

PIXEL& PIXEL::operator=( const PIXEL& p )
{
	R = p.R; 
	G = p.G;
	B = p.B;

	return *this;
}

const PIXEL PIXEL::operator+( const PIXEL& p ) const
{
	return PIXEL( R+p.R, G+p.G, B+p.B );
}

const PIXEL PIXEL::operator/( int n ) const
{
	return PIXEL( R/n, G/n, B/n);
}

const PIXEL PIXEL::operator*( double n ) const
{
	return PIXEL( R*n, G*n, B*n);
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

void PIXEL::setR( unsigned char r )
{
	this->R = r;
};

void PIXEL::setG( unsigned char g )
{
	this->G = g;
};

void PIXEL::setB( unsigned char b )
{
	this->B = b;
};