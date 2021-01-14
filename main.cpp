#include <iostream>

using namespace std;

#include <time.h>

#define _CRT_SECURE_NO_WARNINGS 1
#include <vector>
#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//#define M_PI 3.141592653589793238562;

int main()
{
    time_t beginTime,endTime;
    time(&beginTime);
    cout << "beginTime = " << beginTime << endl;
    cout << "Hello World!" << endl;
    cin.get();
    time(&endTime);
    cout << "endTime = " << endTime << endl;
    cout << "Cela dure " << difftime(endTime,beginTime) << " secondes !" << endl;
    return 0;
}
