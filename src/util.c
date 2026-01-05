#include <stdlib.h>
#include <math.h>



// float lerpf(float start, float target, float time) {
// 	return 1.0f;
// }

float lerp_angle(float start, float end, float time) {
	if (start == end) return end;
	//float result = start + (end - start) * t
	// P * ((1/P) * Q)^t
	float base = start * ((1.f/(start + 0.001)) * end);
	//pow
	float result = powf(base, time);

	return result;
}