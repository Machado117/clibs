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

static String create_string(int minimum_capacity) {
    if (minimum_capacity < 0) return NULL;
    String string;
    if (!(string = malloc(sizeof(struct String)))) return NULL;
    int allocation_size = get_allocation_size(DEFAULT_CAPACITY, minimum_capacity);
    if (!(string->string_data_ = malloc((size_t) allocation_size))) {
        free(string);
        return NULL;
    }
    string->capacity_ = allocation_size;
    string->length_ = 0;
    return string;
}

String CreateString(char *text, int text_length) {
    if (text_length < 0) return NULL;
    String string;
    if (!(string = create_string(text_length))) return NULL;
    memcpy(string->string_data_, text, (size_t) text_length);
    string->length_ = text_length;
    return string;
}

String CreateStringCopy(String string) {
    return CreateString(string->string_data_, string->length_);
}

String CreateEmptyString() {
    return create_string(0);
}

void DestroyString(String string) {
    free(string->string_data_);
    free(string);
}

static ErrorCode GrowString(String string, int new_minimum_capacity) {
    if (new_minimum_capacity <= string->capacity_) return SUCCESS;
    int new_allocation_size = get_allocation_size(string->capacity_, new_minimum_capacity);
    char *new_string = realloc(string->string_data_, (size_t) new_allocation_size);
    if (new_string) {
        string->string_data_ = new_string;
        string->capacity_ = new_allocation_size;
        return SUCCESS;
    } else {
        return ERROR;
    }
}

char *CString(String string) {
    if (GrowString(string, string->length_ + 1) == ERROR) return NULL;
    string->string_data_[string->length_] = '\0';
    return string->string_data_;
}

ErrorCode AppendCharToString(String string, char c) {
    ErrorCode error_code = GrowString(string, string->length_ + 1);
    if (error_code != SUCCESS) return error_code;
    string->string_data_[string->length_++] = c;
    return SUCCESS;
}

ErrorCode AppendTextToString(String string, char *text, int text_length) {
    if (!text_length) return SUCCESS;
    if (text_length < 0) return ERROR;
    ErrorCode error_code = GrowString(string, string->length_ + text_length);
    if (error_code != SUCCESS) return error_code;
    memcpy(string->string_data_ + string->length_, text, (size_t) text_length);
    string->length_ += text_length;
    return SUCCESS;
}

ErrorCode AppendString(String string_dest, String string_src) {
    return AppendTextToString(string_dest, string_src->string_data_, string_src->length_);
}

int FindTextString(String string, int index, char *text, int text_length) {
    int i;
    int string_length = string->length_;
    if (index >= 0 && text_length <= string_length && text_length > 0) {
        for (i = index; i <= string_length - text_length; i++) {
            if (!memcmp(string->string_data_ + i, text, (size_t) text_length)) {
                return i;
            }
        }
    }
    return -1;
}

int FindSubstring(String string, int index, String substring) {
    return FindTextString(string, index, substring->string_data_, substring->length_);
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

String GetSubstring(String string, int index, int length) {
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
    if (!(substring = create_string(substring_length))) return NULL;
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

Bool EqualTextString(String string, char *text, int text_length) {
    if (string->length_ != text_length) return false;
    return !memcmp(string->string_data_, text, (size_t) string->length_);
}

Bool EqualString(String string1, String string2) {
    return EqualTextString(string1, string2->string_data_, string2->length_);
}

char GetCharFromString(String string, int index) {
    return string->string_data_[index];
}

static int get_allocation_size(int current_allocation_size, int minimum_capacity) {
    int new_allocation_size = current_allocation_size;
    if (minimum_capacity > INT_MAX / GROWTH_FACTOR) {
        new_allocation_size = INT_MAX;
    } else {
        while (minimum_capacity > new_allocation_size) {
            new_allocation_size = (int) floor(new_allocation_size * GROWTH_FACTOR);
        }
    }
    return new_allocation_size;
}