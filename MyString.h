//
// Created by diogo on 30-08-2015.
//

#ifndef CLIBS_MYSTRING_H
#define CLIBS_MYSTRING_H

#include "MyLib.h"

struct String {
    int length_;
    int capacity_;
    char *string_data_;
};

typedef struct String *String;

String CreateString(int minimum_capacity);

String CreateStringFromText(char *text, int text_length);

String CreateEmptyString();

void DestroyString(String string);

ErrorCode GrowString(String string, int new_minimum_capacity);

char *CString(String string);

ErrorCode AppendCharToString(String string, char c);

ErrorCode AppendTextToString(String string, char *text, int text_length);

ErrorCode AppendString(String string_dest, String string_src);

int FindTextString(String string, int index, char *text, int text_length);

int FindSubstring(String string, int index, String substring);

void RemoveTextString(String string, int index, int length);

String GetSubstring(String string, int index, int length);

void ClearString(String string);

int LengthString(String string);

Bool EqualString(String string1, String string2);

Bool EqualTextString(String string, char *text, int text_length);

char GetCharFromString(String string, int index);

#endif //CLIBS_MYSTRING_H
