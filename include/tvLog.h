#ifndef _TV_LOG_H
#define _TV_LOG_H


#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif


#define ERROR(text, ...) do {\
        printf("%s[%d] - %s: " text, __FUNCTION__, __LINE__, "ERROR", ##__VA_ARGS__);}while(0);

#define INFO(text, ...) do {\
        printf("%s[%d] - %s: " text, __FUNCTION__, __LINE__, "INFO", ##__VA_ARGS__);}while(0);

//#define DEBUG_ENABLED
#ifdef DEBUG_ENABLED

#define DEBUG(text, ...) do {\
        printf("%s[%d] - %s: " text, __FUNCTION__, __LINE__, "DEBUG", ##__VA_ARGS__);}while(0);
#else
#define DEBUG(text, ...) 
#endif


#ifdef __cplusplus
}
#endif

#endif //_TV_LOG_H
