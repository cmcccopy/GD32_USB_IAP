//key头文件
#ifndef _key_h
#define _key_h

#include "gd32f4xx.h"
#include <stdbool.h>
//按键初始化
void key_init(void);

//检查左右两个按键是否被按下，返回bool,按下返回0
bool key_left(void);
//检查左右两个按键是否被按下，返回bool,按下返回0
bool key_right(void);
//检查左右两个按键是否被按下，返回bool,按下返回0
bool key_OK(void);

#endif
