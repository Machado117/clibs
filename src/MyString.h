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

static String create_string(int minimum_capacity);

String CreateString(char *text, int text_length);

String CreateStringCopy(String string);

String CreateEmptyString();

void DestroyString(String string);

static ErrorCode GrowString(String string, int new_minimum_capacity);

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

Bool EqualTextString(String string, char *text, int text_length);

Bool EqualString(String string1, String string2);

char GetCharFromString(String string, int index);

static int get_allocation_size(int current_allocation_size, int minimum_capacity);

void testMyString();

#endif //CLIBS_MYSTRING_H
