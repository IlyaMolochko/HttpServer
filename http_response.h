#pragma once

#include "stringbuilder.h"

#include <stdbool.h>

#define SERVER_HEADER "Server: Ilya Malochka"

enum EHttpCode {
    HTTP_OK = 200,
    HTTP_BAD_REQUEST = 400,
    HTTP_NOT_FOUND = 404,
    HTTP_METHOD_NOT_ALLOWED = 405,
    HTTP_INTERNAL_SERVER_ERROR = 500,
};

struct THttpResponse {
    enum EHttpCode Code;
    const char* ContentType; // static string
    struct TStringBuilder Body;
};

const char* GetReasonPhrase(enum EHttpCode code);

void THttpResponse_Init(struct THttpResponse* self);
bool THttpResponse_Send(struct THttpResponse* self, int sockfd);
void THttpResponse_Destroy(struct THttpResponse* self);
