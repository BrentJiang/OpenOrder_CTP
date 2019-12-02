/////////////////////////////////////////////////////////////////////////
///@system 新一代交易所系统
///@company 上海期货信息技术有限公司
///@file ThostFtdcTraderApi.h
///@brief 定义了客户端接口
///@history 
///20060106	赵鸿昊		创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(OPENORDER_THOST_FTDCTRADERAPI_H)
#define OPENORDER_THOST_FTDCTRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ThostFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#define TRADER_API_EXPORT 
#endif

namespace OpenOrder {
enum level_enum
{
	trace = 0,
	debug = 1,
	info = 2,
	warn = 3,
	err = 4,
	critical = 5,
	off = 6,
};

// 交易帐号配置结构
struct InvestorConfig {
	InvestorConfig() {}
	InvestorConfig(const InvestorConfig& other) {
		this->name = other.name;
		this->investor_id = other.investor_id;
		this->broker_id = other.broker_id;
		this->user_id = other.user_id;
		this->account_code = other.account_code;
		this->password = other.password;
		this->client_id = other.client_id;
	}
	InvestorConfig& operator=(const InvestorConfig& other) {
		this->name = other.name;
		this->investor_id = other.investor_id;
		this->broker_id = other.broker_id;
		this->user_id = other.user_id;
		this->account_code = other.account_code;
		this->password = other.password;
		this->client_id = other.client_id;
		return *this;
	}
	// 交易账号名称。可为空。
	std::string name;
	// 交易账号编号，OpenOrder的内部编号，需保证不为重复。默认为0即可。
	int32_t investor_id;
	// 经纪公司代码
	std::string broker_id;
	// 用户帐号编号。对于CTP，user_id等同于account_code（两者应同时填入）。
	std::string user_id;
	// 资金帐号编号。对于CTP，user_id等同于account_code（两者应同时填入）。
	std::string account_code;
	/// 资金帐号密码（交易密码）
	std::string password;
	// 客户号（交易编码）。可为空。
	std::string client_id;

};

// 柜台配置结构
struct CounterConfig {
	CounterConfig() {}
	CounterConfig(const CounterConfig& other) {
		this->name = other.name;
		this->channel_type = other.channel_type;
		this->channel_id = other.channel_id;
		this->custom_config = other.custom_config;
		this->auto_query = other.auto_query;
		this->auto_query_interval = other.auto_query_interval;
		this->investor = other.investor;
		this->data_path = other.data_path;
		this->log_pathname = other.log_pathname;
		this->log_level = other.log_level;
		this->ipv4_address = other.ipv4_address;
		this->ipv4_port = other.ipv4_port;
	}
	CounterConfig& operator=(const CounterConfig& other) {
		this->name = other.name;
		this->channel_type = other.channel_type;
		this->channel_id = other.channel_id;
		this->custom_config = other.custom_config;
		this->auto_query = other.auto_query;
		this->auto_query_interval = other.auto_query_interval;
		this->investor = other.investor;
		this->data_path = other.data_path;
		this->log_pathname = other.log_pathname;
		this->log_level = other.log_level;
		this->ipv4_address = other.ipv4_address;
		this->ipv4_port = other.ipv4_port;
		return *this;
	}
	// The unique name of the Counter connected. Default to "CTP".
	std::string name;
	// '2' - CTP柜台,'M' - CTP2Mini,'L' - LTS柜台,'Q' - QMT柜台,'X' - TradeX接入
	std::string channel_type;
	// 柜台链路通道编号，默认为1即可。
	int32_t channel_id;
	// 自定义柜台配置参数。用于输入CTP柜台的BrokerID、AuthenticationCode等柜台配置信息。
	// 详细参考Readme.md文档。
	std::string custom_config;
	// 是否自动定时查询委托和成交回报。
	bool auto_query;
	// 自动查询委托和成交回报的时间间隔，单位为秒。
	int32_t auto_query_interval;
	// 交易账号。目前仅支持一个通道一个帐号，不支持通道复用。
	InvestorConfig investor;
	// 存放缓存文件的文件夹。
	std::string data_path;
	// 日志文件的路径和文件名。
	std::string log_pathname;
	// 日志级别.
	level_enum log_level;
	// 如果未在custom_config中指定服务器地址，可以用ipv4_address指定。
	std::string ipv4_address;
	// 如果未在custom_config中指定服务器端口，可以用ipv4_port指定。
	int32_t ipv4_port;
};

class CThostFtdcTraderSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse){};

	///报单录入请求响应
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询报单响应
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询成交响应
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约响应
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询行情响应
	virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单通知
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder) {};

	///成交通知
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) {};

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {};
};

class TRADER_API_EXPORT CThostFtdcTraderApi
{
public:
	///创建TraderApi
	///@return 创建出的UserApi
	static CThostFtdcTraderApi *CreateFtdcTraderApi();
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@param pszConfigPath 存贮配置信息
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init(const CounterConfig* pCounterConfig) = 0;
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CThostFtdcTraderSpi *pSpi) = 0;
	
	///报单录入请求
	virtual int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	///报单操作请求
	virtual int ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID) = 0;

	///请求查询报单
	virtual int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	///请求查询成交
	virtual int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID) = 0;

	///请求查询投资者持仓
	virtual int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) = 0;

	///请求查询资金账户
	virtual int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) = 0;

	///请求查询投资者
	virtual int ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID) = 0;

	///请求查询交易编码
	virtual int ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID) = 0;

	///请求查询合约
	virtual int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///请求查询行情
	virtual int ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID) = 0;
	
	///订阅行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeMarketData(char *ppInstrumentID[], int nCount) = 0;

	///退订行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeMarketData(char *ppInstrumentID[], int nCount) = 0;
protected:
	~CThostFtdcTraderApi(){};
};

} // namespace OpenOrder 
#endif
