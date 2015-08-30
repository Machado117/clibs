//
// Created by diogo on 30-08-2015.
//

#ifndef CLIBS_MYSTRING_H
#define CLIBS_MYSTRING_H

#include "MyLib.h"

struct String {
    int length_;
    int capacity_;
    char *string_;
};

typedef struct String String;

ErrorCode CreateString(String *string, char *text);
ErrorCode CreateEmptyString(String *string);
void DestroyString(String *string);
ErrorCode GrowString(String *string, int size_to_add);
char *CString(String *string);
ErrorCode AddCharString(String *string, char c);
ErrorCode AddTextString(String *string, char *text);
ErrorCode AddString(String *string_dest, String *string_src);
int FindTextString(String *string, char *text, int index);
void RemoveTextString(String *string, int index, int length);
void ClearString(String *string);
int LengthString(String *string);
Bool EqualString(String *string1, String *string2);
Bool EqualTextString(String *string, char *text);
char GetLastChar(String *string);
char GetCharString(String *string, int index);

#endif //CLIBS_MYSTRING_H
