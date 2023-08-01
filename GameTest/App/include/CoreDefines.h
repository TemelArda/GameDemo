#pragma once

#define APP_VIRTUAL_TO_NATIVE_COORDS(_x_,_y_)			_x_ = ((_x_ / APP_VIRTUAL_WIDTH )*2.0f) - 1.0f; _y_ = ((_y_ / APP_VIRTUAL_HEIGHT)*2.0f) - 1.0f;
#define APP_NATIVE_TO_VIRTUAL_COORDS(_x_,_y_)			_x_ = ((_x_ + 1.0f) * APP_VIRTUAL_WIDTH) / 2.0f; _y_ = ((_y_ + 1.0f) * APP_VIRTUAL_HEIGHT) / 2.0f;

#define FRAND	(static_cast <float> (rand()) / static_cast <float> (RAND_MAX))
#define FRAND_RANGE(_MIN_, _MAX_ ) (FRAND * ((_MAX_)-(_MIN_)) + (_MIN_))
#define PI		(3.14159265359f)
