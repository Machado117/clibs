//
// Created by diogo on 30-08-2015.
//

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "MyString.h"

#define DEFAULT_CAPACITY 16
#define GROWTH_FACTOR 1.618

String CreateString(int minimum_capacity) {
    String string;
    if (!(string = malloc(sizeof(struct String)))) {
        return NULL;
    }
    size_t allocation_size = DEFAULT_CAPACITY;
    while (minimum_capacity > allocation_size) {
        allocation_size = (size_t) ceil(allocation_size * GROWTH_FACTOR);
        if (allocation_size > INT_MAX) {
            allocation_size = INT_MAX;
        }
    }
    if (!(string->string_data_ = malloc(allocation_size))) {
        free(string);
        return NULL;
    }
    string->capacity_ = (int) allocation_size;
    string->length_ = 0;
    return string;
}

String CreateStringFromText(char *text, int text_length) {
    String string;

    if (!(string = CreateString(text_length))) {
        return NULL;
    }
    memcpy(string->string_data_, text, (size_t) text_length);
    string->length_ = text_length;
    return string;
}

String CreateEmptyString() {
    return CreateString(0);
}

void DestroyString(String string) {
    free(string->string_data_);
    free(string);
}

ErrorCode GrowString(String string, int new_minimum_capacity) {
    if (new_minimum_capacity < 0) return ERROR;
    if (new_minimum_capacity < string->capacity_) return SUCCESS;
    size_t new_allocation_size = (size_t) ceil(string->capacity_ * GROWTH_FACTOR);
    while (new_minimum_capacity > new_allocation_size) {
        new_allocation_size = (size_t) ceil(new_allocation_size * GROWTH_FACTOR);
        if (new_allocation_size > INT_MAX) {
            new_allocation_size = INT_MAX;
        }
    }
    char *new_string = realloc(string->string_data_, new_allocation_size);
    if (new_string) {
        string->string_data_ = new_string;
        string->capacity_ = (int) new_allocation_size;
        return SUCCESS;
    } else {
        return ERROR;
    }
}

char *CString(String string) {
    if (GrowString(string, string->length_ + 1) == ERROR) {
        return NULL;
    }
    string->string_data_[string->length_] = '\0';
    return string->string_data_;
}

ErrorCode AddCharString(String string, char c) {
    ErrorCode error_code = GrowString(string, string->length_ + 1);
    if (error_code != SUCCESS) return error_code;
    string->string_data_[string->length_++] = c;
    return SUCCESS;
}

ErrorCode AddTextString(String string, char *text, int text_length) {
    if (text_length >= 0) {
        ErrorCode error_code = GrowString(string, string->length_ + text_length);
        if (error_code != SUCCESS) return error_code;
        memcpy(string->string_data_ + string->length_, text, (size_t) text_length);
        string->length_ += text_length;
        return SUCCESS;
    }
    return ERROR;
}

ErrorCode AddString(String string_dest, String string_src) {
    ErrorCode error_code = GrowString(string_dest, string_dest->length_ + string_src->length_);
    if (error_code != SUCCESS) return error_code;
    memcpy(string_dest->string_data_ + string_dest->length_, string_src->string_data_,
           (size_t) string_src->length_);
    string_dest->length_ += string_src->length_;
    return SUCCESS;
}

int FindTextString(String string, int index, char *text, int text_length) {
    int i;
    int string_length = string->length_;
    if (index >= 0 && text_length <= string_length) {
        for (i = index; i <= string_length - text_length; i++) {
            if (!strncmp(CString(string) + i, text, (size_t) text_length)) {
                return i;
            }
        }
    }
    return -1;
}

void RemoveTextString(String string, int index, int length) {
    int string_length = string->length_;
    if (index < string_length && index >= 0) {
        if (length == -1) length = string_length - index;
        if (length > 0) {
            if (index + length < string_length) {
                memmove(&string->string_data_[index], &string->string_data_[index + length],
                        (size_t) (string_length - (index + length)));
                string->length_ = string_length - length;
            } else {
                string->length_ = string_length - (string_length - index);
            }
        }

    }
}

String GetSubString(String string, int index, int length) {
    if (index >= string->length_ || index < 0 || length < -1) {
        return CreateEmptyString();
    }
    if (length == -1) length = string->length_ - index;
    int end_index = index + length;
    if (end_index > string->length_) {
        end_index = string->length_;
    }
    int substring_length = end_index - index;
    String substring;
    if (!(substring = CreateString(substring_length))) return NULL;
    memcpy(substring->string_data_, string->string_data_ + index,
           (size_t) substring_length);
    substring->length_ = substring_length;
    return substring;
}

void ClearString(String string) {
    string->length_ = 0;
}

int LengthString(String string) {
    return string->length_;
}

Bool EqualString(String string1, String string2) {
    if (string1->length_ != string2->length_) return false;
    return !memcmp(string1->string_data_, string1->string_data_, (size_t) string1->length_);
}

Bool EqualTextString(String string, char *text, int text_length) {
    if (string->length_ != text_length) return false;
    return !memcmp(string->string_data_, text, (size_t) string->length_);
}

char GetCharString(String string, int index) {
    if (index < string->length_ && index >= 0) {
        return string->string_data_[index];
    }
    return -1;
}