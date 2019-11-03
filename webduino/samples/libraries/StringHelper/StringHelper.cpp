
#include <string.h>
#include <stdlib.h>

#include "StringHelper.h"

char **StringHelper::split(char *text, const char *delimiter) {
    int counter = 0;
    char **tokens = NULL;
    char *token = NULL;

    //Make sure the text is not empty
    if (text == NULL) {
        return tokens;
    }

    //Get the first token and try to get the rest if any
    token = StringHelper::trim(strtok(text, delimiter));
    while (token != NULL) {
        if (counter == 0) {
            tokens = (char **) malloc(++counter * sizeof (char *));
        } else {
            tokens = (char **) realloc(tokens, ++counter * sizeof (char *));
        }

        //Set the found token
        *(tokens + counter - 1) = token;

        //Get the next token
        token = StringHelper::trim(strtok(NULL, delimiter));
    }

    //Mark the end of this vector
    *(tokens + counter) = 0;

    return tokens;
}

char *StringHelper::trim(char* text) {
    char *end;

    //If no text, break it
    if (text == NULL) {
        return NULL;
    }

    // Trim leading space
    while (StringHelper::isspace(*text)) {
        text++;
    }

    // All spaces
    if (*text == 0) {
        return text;
    }

    // Trim trailing space
    end = text + strlen(text) - 1;
    while (end > text && StringHelper::isspace(*end)) {
        end--;
    }

    // Write new null terminator
    *(end + 1) = 0;

    return text;
}

bool StringHelper::isspace(int c) {
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r') {
        return true;
    }

    return false;
}
