//
// Created by diogo on 30-08-2015.
//
#include <stdio.h>
#include "MyString.h"

int main() {
    String str;

    CreateString(&str, "Hello World!");
    printf("%s\n", CString(&str));
    return 0;
}