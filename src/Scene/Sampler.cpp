#include "Sampler.h"

Sampler::Sampler(int w, int h)
	: w_(w), h_(h), num_samples_(w * h), curr_sample_(0) {}

// Tries to set next pixel sample, or tells client we are out
// Note: we start at top left of viewport and create one sample per pixel
bool Sampler::getSample(Sample& s)
{
	if (curr_sample_ >= num_samples_) return false;

	float x = (curr_sample_ % w_) + .5;
	float y = (curr_sample_ / w_) + .5;
	s = Sample(x / (w_ - 1), y / (h_ - 1));

	curr_sample_++;

	return true;
}
