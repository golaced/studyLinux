#include "accessTime.h"
#include <stdio.h>

int main()
{
    Mat im;
    string str = "test.jpg";

    im = imread(str);

    if(im.empty())
    {
        printf("can not open image\n");
        return 1;
    }
    if(!im.isContinuous())
    {
        printf("image is not continous, canot scan\n");
        return 1;
    }

    resize(im, im, Size(200,200));
    imshow("srcImg", im);
    structInit();
    scanTime(im);
    imshow("dstImg", im);

	waitKey(0);
}
