#ifndef _TV_ERROR_H
#define _TV_ERROR_H

#ifdef __cplusplus
extern "C"
{
#endif
 
//! The enumeration of Error codes 
typedef enum {
     
    tvERROR_NONE = 0, //! Error Code None
    tvERROR_GENERAL, //! Error Code General  
    tvERROR_OPERATION_NOT_SUPPORTED,  //! Error code Operation not supported 
    tvERROR_INVALID_PARAM,  //! Error code - Invalid Parameter  
    tvERROR_INVALID_STATE  //! Error code - Invalid State
}tvError_t;

#ifdef __cplusplus
}
#endif

#endif //_TV_ERROR_H
