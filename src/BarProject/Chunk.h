/*
 * Chunk.h
 *
 *  Created on: May 16, 2015
 *      Author: tal
 */

#ifndef CHUNK_H_
#define CHUNK_H_

typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

class Strip;
class Chunk {
public:
	Strip* Owner;
	long int color;
	int r,g,b;
	RgbColor rgb;
	HsvColor hsv;
	int standStillLeft;
	int startPin,endPin;
	int goesForward;
	void makeStep();
	void standStill();
	void makeNextColor();
	void growFront(){startPin--;}
	void growBack(){endPin++;}
	void shrinkFront(){startPin++;}
	void ShrinkBack(){endPin--;}
	int Size(){return endPin -startPin;}
	void moveForward(){startPin++;endPin++;}
	void moveBack(){startPin--;endPin--;}
	void nextStep();
	void reverse() {goesForward = !goesForward;};
	void ChangeColorRandom();
	void init (int start,int size);

	Chunk(Strip* s);
	virtual ~Chunk();
};

#endif /* CHUNK_H_ */
