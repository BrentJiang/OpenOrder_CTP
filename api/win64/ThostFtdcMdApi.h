/////////////////////////////////////////////////////////////////////////
///@system ��һ��������ϵͳ
///@company �Ϻ��ڻ���Ϣ�������޹�˾
///@file ThostFtdcMdApi.h
///@brief �����˿ͻ��˽ӿ�
///@history 
///20060106	�Ժ��		�������ļ�
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
