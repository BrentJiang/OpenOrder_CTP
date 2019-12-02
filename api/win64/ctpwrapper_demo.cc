#include <string>
#include <iostream>
#include <stdint.h>
#pragma comment(lib, "shlwapi.lib")  // For SHGetValue().

#include "ThostFtdcTraderApi.h"

using namespace OpenOrder;

class TradeSpi : public CThostFtdcTraderSpi
{
public:
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected() {};

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason) {};

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse) {};

	///报单录入请求响应
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询报单响应
	virtual void OnRspQryOrder(CThostFtdcOrderField* pOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询成交响应
	virtual void OnRspQryTrade(CThostFtdcTradeField* pTrade, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约响应
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询行情响应
	virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {};

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {};

	///报单通知
	virtual void OnRtnOrder(CThostFtdcOrderField* pOrder) {
	};

	///成交通知
	virtual void OnRtnTrade(CThostFtdcTradeField* pTrade) {};

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData) {
		std::cout << "pDepthMarketData " << std::endl;
	};
};

int main(int argc, char** argv)
{
    CThostFtdcTraderApi* trader = CThostFtdcTraderApi::CreateFtdcTraderApi();
    CounterConfig counterConfig;
	counterConfig.auto_query = false;
	counterConfig.channel_id = 1;
	counterConfig.channel_type = '2';
	counterConfig.name = "test_demo";
	// simnow for non-trading time
	counterConfig.custom_config = 
		"{"\
		"\"CtpRunningMode\":\"debug_ntr_simnow\", "\
		"\"CtpTradeAddr\":\"tcp://180.168.146.187:10130\", "\
		"\"CtpMdAddr\":\"tcp://180.168.146.187:10131\", "\
		"\"BrokerID\":\"9999\", "\
		"\"CtpAuthCode\":\"0000000000000000\", "\
		"\"CtpProductInfo\":\"client_fhsoft\", "\
		"\"CtpAppId\":\"client_fhsoft_1.0.0\""\
		"}";
	//simnow for trading time
	//counterConfig.custom_config =
	//	"{"\
	//	"\"CtpRunningMode\":\"debug_tr_simnow\", "\
	//	"\"CtpTradeAddr\":\"tcp://180.168.146.187:10100\", "\
	//	"\"CtpMdAddr\":\"tcp://180.169.227.244:43213\", "\
	//	"\"BrokerID\":\"9999\", "\
	//	"\"CtpAuthCode\":\"0000000000000000\", "\
	//	"\"CtpProductInfo\":\"client_fhsoft\", "\
	//	"\"CtpAppId\":\"client_fhsoft_1.0.0\""\
	//	"}";
	counterConfig.investor.investor_id = 10001;
	counterConfig.investor.name = "trader01";
	counterConfig.investor.user_id = "126399";
	counterConfig.investor.account_code = "126399";
	counterConfig.investor.password = "vpn17560149";
	counterConfig.data_path = "./data";
	counterConfig.log_pathname = "./logs/ctpwrapper_demo.log";
	counterConfig.log_level = level_enum::debug;
	
	trader->Init(&counterConfig);
	TradeSpi tradespi;
	trader->RegisterSpi(&tradespi);
	trader->Join();
	return 0;
}