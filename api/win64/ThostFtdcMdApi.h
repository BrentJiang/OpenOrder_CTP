/////////////////////////////////////////////////////////////////////////
///@system 新一代交易所系统
///@company 上海期货信息技术有限公司
///@file ThostFtdcMdApi.h
///@brief 定义了客户端接口
///@history 
///20060106	赵鸿昊		创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(OPENORDER_THOST_FTDCMDAPI_H)
#define OPENORDER_THOST_FTDCMDAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ThostFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MD_API_EXPORT
#define MD_API_EXPORT __declspec(dllexport)
#else
#define MD_API_EXPORT __declspec(dllimport)
#endif
#else
#define MD_API_EXPORT 
#endif

namespace OpenOrder {

class CThostFtdcMdSpi
{
public:
	// do nothing! please CThostFtdcTraderSpi and CThostFtdcMdSpi

};

class MD_API_EXPORT CThostFtdcMdApi
{
public:

protected:
	~CThostFtdcMdApi(){};
};

} // namespace OpenOrder

#endif
