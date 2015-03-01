
# include <iostream>
using namespace std;

class PRIMARY
{
	protected:
		unsigned char R;


	public:
		PRIMARY(){};
		PRIMARY(unsigned char r) :R(r){};

		virtual unsigned char getR(){ return this->R; };

		virtual void setR( unsigned char r){ R = r;}
		virtual ~PRIMARY(){};
};