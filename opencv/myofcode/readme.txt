光流跟踪迭代次数及精度设置：默认20,0.03， 改为15,0.1；迭代精度没必要那么高，浪费时间
角点窗口大小设置:WINSIZE = 31
角点数目设置在findCorner.c

防止各种奇怪的值
滤波