/*
 *  字符串数据结构
 * */
#ifndef MYSTRING_H
#define MYSTRING_H

#include "project_config.h"


typedef struct
{
    char *elem;
    size_t length;
} string;


/*  字符串初始化    */
bool String_init(string *str);


/*  生成一个值等于 ch的字符串 */
bool String_assign(string *str, const char *ch);


/*  返回 str 串的长度 */
size_t String_length(const string *str);


/* 字符串比较, 若 str_a > str_b 返回值> 0; 若 str_a == str_b, 返回值=0, 否则 < 0  */
int String_compare(const string *str_a, const string *str_b);


/*  清空字符串  */
bool String_clear(string *str);


/*  字符串连接操作  */
bool String_concat(const string *str_a, const string *str_b, string *out_str);


/*  字符串截取子串  */
bool String_substr(const string *str, int pos, int len, string *out_str);


/*  字符串的模式匹配算法    */
int  String_index(const string *str, const string *child_str, int pos);


// KMP 算法

#endif

