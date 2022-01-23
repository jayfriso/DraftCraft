#pragma once


// Create function for passing in 1 param
#define CREATE_FUNC_ONE_PARAM_CONSTRUCTOR(__TYPE__, __CONSTRUCTOR_PARAM_TYPE__) \
static __TYPE__* create(__CONSTRUCTOR_PARAM_TYPE__ param) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(param); \
    if (pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

// Create function for passing in 2 params
#define CREATE_FUNC_TWO_PARAM_CONSTRUCTOR(__TYPE__, __PARAM_1_TYPE__, __PARAM_2_TYPE__) \
static __TYPE__* create(__PARAM_1_TYPE__ param1, __PARAM_2_TYPE__ param2) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(param1, param2); \
    if (pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}