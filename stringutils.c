#include "stringutils.h"

#include <stdio.h>
#include <string.h>

/**
 * Parse query string
 */

#define MAX_INT_LEN 9

static int ParseInt(const char *s, size_t len) {
    if (len > MAX_INT_LEN) {
        return 0;
    }

    // We need a null-terminated string for scanf()
    char tmp[MAX_INT_LEN + 1];
    memcpy(tmp, s, len);
    tmp[len] = '\0';

    int result;
    if (sscanf(tmp, "%d", &result) == 1) {
        return result;
    }
    return 0;
}

int GetIntParam(const char *queryString, const char *name) {
    const size_t len = strlen(queryString);
    const size_t nameLen = strlen(name);

    size_t i = 0;
    while (i < len) {
        size_t j = i;
        while (j < len && queryString[j] != '&') {
            ++j;
        }
        // [i, j) = "key=value"
        if (j - i > nameLen && strncmp(queryString + i, name, nameLen) == 0) {
            size_t eqPos = i + nameLen;
            if (queryString[eqPos] == '=') {
                return ParseInt(queryString + eqPos + 1, j - eqPos - 1);
            }
        }
        i = j + 1;
    }
    return 0;
}

bool StartsWith(const char *s, const char *prefix) {
    return strncmp(s, prefix, strlen(prefix)) == 0;
}

bool EndsWithCI(const char *s, const char *suffix) {
    const size_t sLen = strlen(s);
    const size_t suffLen = strlen(suffix);
    return suffLen <= sLen && strcasecmp(s + sLen - suffLen, suffix) == 0;
}

char Decode(char c){
    if ((c >= '0') && (c <= '9')) {
        return c - '0';
    } else if ((c >= 'a') && (c <= 'f')) {
        return c - 'a' + 10;
    } else if ((c >= 'A') && (c <= 'F')) {
        return c - 'A' + 10;
    }
}

void UnquoteUrl(char *url, char *unquotedUrl) {
    int c;
    while (*url) {
        if (*url == '%') {
            c = 0;
            c |= (Decode(url[1]) << 4);
            c |= (Decode(url[2]));
            *unquotedUrl = c;
            ++unquotedUrl;
            url += 3;
        } else {
            *unquotedUrl = *url;
            ++unquotedUrl;
            ++url;
        }
    }
    *unquotedUrl = 0;
}