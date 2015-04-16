#ifndef MRANDOM_H
#define MRANDOM_H


class MRandom
{
private:
	size_t seed;
public:
	MRandom()
	{

	}

	void setSeed(int _seed = 0)
	{
		if (seed == 0) {
			seed = (unsigned)time(0);
		}
		srand(seed);
	}
	
	int getSeed()
	{
		return seed;
	}

	int getInt(int st = 0, int dr = 32000)
	{
		return rand() % (dr - st) + st;
	}
};


#endif