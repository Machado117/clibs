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

ErrorCode CreateString(String *string, char *text) {
    size_t text_length = (text == NULL) ? 0 : strlen(text);
    size_t allocation_size;

    allocation_size = DEFAULT_CAPACITY;
    while (text_length > allocation_size) {
        allocation_size = (size_t)ceil(allocation_size * GROWTH_FACTOR);
        if (allocation_size >  INT_MAX) {
            allocation_size = INT_MAX;
            if (text_length > allocation_size) {
                string->capacity_ = 0;
                string->length_ = 0;
                string->string_ = NULL;
                return ERROR;
            }
        }
    }

    if (!(string->string_ = malloc(allocation_size))) {
        string->capacity_ = 0;
        string->length_ = 0;
        return ERROR;
    }

    string->capacity_ = allocation_size;
    string->length_ = text_length;

    memcpy(string->string_, text, text_length);
    return SUCCESS;
}

ErrorCode CreateEmptyString(String *string) {
    return CreateString(string, NULL);
}
void DestroyString(String *string) {
    string->length_ = 0;
    string->capacity_ = 0;
    free(string->string_);
    string->string_ = NULL;
}

ErrorCode GrowString(String *string, int size_to_add) {
    size_t new_allocation_size = (size_t)ceil(string->capacity_ * GROWTH_FACTOR);
    if (new_allocation_size >  INT_MAX) {
        new_allocation_size = INT_MAX;
        if (string->length_ + size_to_add > new_allocation_size) return ERROR;
    }
    while (string->length_ + size_to_add > new_allocation_size) {
        new_allocation_size = (size_t)ceil(new_allocation_size * GROWTH_FACTOR);
        if (new_allocation_size >  INT_MAX) {
            new_allocation_size = INT_MAX;
            if (string->length_ + size_to_add > new_allocation_size) return ERROR;
        }
    }

    char *new_string = realloc(string->string_, new_allocation_size);
    if (new_string) {
        string->string_ = new_string;
        string->capacity_ = new_allocation_size;
        return SUCCESS;
    } else {
        return ERROR;
    }
}

char *CString(String *string) {
    if (!string->length_) return NULL;
    if (string->length_ == string->capacity_) {
        if (GrowString(string, 1) == ERROR) {
            return NULL;
        }
    }
    string->string_[string->length_] = '\0';
    return string->string_;
}

ErrorCode AddCharString(String *string, char c) {
    if (string->length_ == string->capacity_) {
        if (GrowString(string, 1) == ERROR) {
            return ERROR;
        }
    }
    string->string_[string->length_++] = c;
    return SUCCESS;
}
ErrorCode AddTextString(String *string, char *text) {
    int text_length = strlen(text);
    if (string->length_ + text_length > string->capacity_) {
        if (GrowString(string, text_length) == ERROR) {
            return ERROR;
        }
    }
    memcpy(string->string_ + string->length_, text, text_length);
    string->length_ += text_length;
    return SUCCESS;
}

ErrorCode AddString(String *string_dest, String *string_src) {
    if (string_dest->length_ + string_src->length_ > string_dest->capacity_) {
        if (GrowString(string_dest, string_src->length_) == ERROR) {
            return ERROR;
        }
    }
    memcpy(string_dest->string_ + string_dest->length_, string_src->string_,
           string_src->length_);
    string_dest->length_ += string_src->length_;
    return SUCCESS;
}

int FindTextString(String *string, char *text, int index) {
    int i;
    int text_length = strlen(text);
    int string_length = string->length_;
    for (i = index; i <= string_length - text_length; i++) {
        if (!strncmp(CString(string) + i, text, text_length)) {
            return i;
        }
    }
    return -1;
}

void RemoveTextString(String *string, int index, int length) {
    int string_length = string->length_;
    if (index < string_length && length) {
        if (index + length < string_length) {
            memmove(&string->string_[index], &string->string_[index + length],
                    string_length - (index + length));
            string->length_ = string_length - length;
        } else {
            string->length_ = string_length - (string_length - index);
        }
    }
}

void ClearString(String *string) {
    string->length_ = 0;
}

int LengthString(String *string) {
    return string->length_;
}

Bool EqualString(String *string1, String *string2) {
    if (string1->length_ != string2->length_) return false;
    return !memcmp(string1->string_, string1->string_, string1->length_);
}

Bool EqualTextString(String *string, char *text) {
    if (string->length_ != strlen(text)) return false;
    return !memcmp(string->string_, text, string->length_);
}

char GetLastChar(String *string) {
    if (string->length_)
    {
        return string->string_[string->length_ - 1];
    } else {
        return -1;
    }

}

char GetCharString(String *string, int index) {
    if (index < string->length_) {
        return string->string_[index];
    }
    return -1;
}