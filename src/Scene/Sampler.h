#pragma once

struct Sample
{
	float x, y;

	Sample(float x, float y)
		: x(x), y(y) {}
};


class Sampler
{
public:
	//Constructors
	Sampler(int w, int h);

	// Methods
	bool getSample(Sample& s);

private:
	//Members
	int w_, h_;
	int num_samples_;
	int curr_sample_;
};

