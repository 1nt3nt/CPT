#pragma once
#include <string>
#include <Windows.h>
#include <float.h>
#include <iostream>
#include "ThostFtdcTraderApi.h"

class TraderSpi : public CThostFtdcTraderSpi
{
	// defined member
	// constructor & destructor
public: 
	TraderSpi() {};
	~TraderSpi() {};
	// integrate notification function
	void notification(CThostFtdcRspInfoField* pRspInfo)
	{
		if (pRspInfo)
		{
			printf("Error ID: %d\n", pRspInfo->ErrorID);
			printf("Error message: %s \n", pRspInfo->ErrorMsg);
		}
		printf("----------------- END -----------------\n");
	}

	// prevent nan, inf value
	template<typename T> T validValue(T val)
	{
		T ref = 0.0;
		return (val >= DBL_MAX) ? ref : val;
	}

	// method
public:
	// invoke after building communication between client-side and trade service
	virtual void OnFrontConnected();

	// invoke after disconnection between client-side and trade service
	virtual void OnFrontDisconnected(int nReason);

	// invoke when there is long time without response(order)
	virtual void OnHeartBeatWarning(int nTimeLapse);

	// invoke when error occured during order inserting
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField* pInputOrder,
		CThostFtdcRspInfoField* pRspInfo);

	// invoke when error occured during order withdraw
	virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField* pOrderAction,
		CThostFtdcRspInfoField* pRspInfo);

	// respond to authenticate client
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to user login
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to user logout
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to update user password
	virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField* pUserPasswordUpdate, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to update trader account password
	virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField* pTradingAccountPasswordUpdate, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to support which authentications by user
	virtual void OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField* pRspUserAuthMethod, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// get graphic verification code
	virtual void OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField* pRspGenUserCaptcha, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// get text verification code
	virtual void OnRspGenUserText(CThostFtdcRspGenUserTextField* pRspGenUserText, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to insert order
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to pre-park inserting order
	virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField* pParkedOrder, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to pre-park withdrawing order
	virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField* pParkedOrderAction, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to Withdraw order
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField* pInputOrderAction, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to query max order volume
	virtual void OnRspQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField* pQryMaxOrderVolume, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to confirm settlement info
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to delete pre-pared order
	virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField* pRemoveParkedOrder, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to delete pre-pard withdrawing order
	virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField* pRemoveParkedOrderAction, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to execute inserting order
	virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField* pInputExecOrder, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to execute placing order
	virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField* pInputExecOrderAction, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	//respond for inquiry 
	virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField* pInputForQuote, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	//respond to quote
	virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField* pInputQuote, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to quote action
	virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField* pInputQuoteAction, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to batch order operation
	virtual void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField* pInputBatchOrderAction, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond for options self-hedging inserting action
	virtual void OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField* pInputOptionSelfClose, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond for options self-hedging action
	virtual void OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField* pInputOptionSelfCloseAction, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) ;

	// respond to combine inserting action
	virtual void OnRspCombActionInsert(CThostFtdcInputCombActionField* pInputCombAction,
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to inquiry order
	virtual void OnRspQryOrder(CThostFtdcOrderField* pOrder, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to inquiry transaction
	virtual void OnRspQryTrade(CThostFtdcTradeField* pTrade, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to request investor postion
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to inquiry trading account
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to inquiry investor
	virtual void OnRspQryInvestor(CThostFtdcInvestorField* pInvestor, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to inquiry transaction code
	virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField* pTradingCode, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to inquiry instrument
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument,
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to inquiry instrument margin rate
	virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField* pInstrumentMarginRate, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to inquiry instrument commmission rate
	virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField* pInstrumentCommissionRate, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	// respond to inquiry exchange
	virtual void OnRspQryExchange(CThostFtdcExchangeField* pExchange, 
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	
	// respond to order insert
	virtual void OnRtnOrder(CThostFtdcOrderField* pOrder);

	// respond to order insert ii
	virtual void OnRtnTrade(CThostFtdcTradeField* pTrade);
}; 


