#pragma once
#include <string>
#include <Windows.h>
#include <float.h>
#include <iostream>
#include "ThostFtdcTraderApi.h"

class TraderHandler
{
private:
	CThostFtdcTraderApi* tdApi;
	// ----------------------------------------------
	TThostFtdcBrokerIDType brokerID = "9999";
	TThostFtdcUserIDType uId = "214060";
	TThostFtdcInvestorIDType investor_id = "214060";
	TThostFtdcSessionIDType session_id;
	//TThostFtdcExchangeIDType exchangeID;
	//TThostFtdcFrontIDType frontID;
	//TThostFtdcInvestorIDType investorID;
	//TThostFtdcInvestUnitIDType investor_UnitID;
	//TThostFtdcOrderActionRefType OrderActionRef;

	int nRequestID = 0;

	// counstructor & destructor
public:
	TraderHandler(CThostFtdcTraderApi* userTDApi);
	~TraderHandler();

	// methods member
public:
	void Connect(char* tradeFront, CThostFtdcTraderSpi* tdSpi);

	void ReqUserLogin();

	void ReqUserLogout();

	void ReqAuthenticate();

	void ReqUserPasswordUpdate(char* oldPassword, char* newPassword);

	void ReqTradingAccountPasswordUpdate(char* brokerID, char* currencyID, char* accountID,
		char* oldPassword, char* newPassword);

	void ReqBatchOrderAction(char* brokerID, char* exchangeID, int frontID,
		char* investorID, char* investor_UnitID, int OrderActionRef);
	//void ReqCombActionInsert(char* brokerID, char* investorID, char* instrument_id,
	//	char* exchangeID);
	//void ReqExecOrderAction();
	//void ReqExecOrderInsert();
	//void ReqForQuoteInsert();
	//void ReqFromBankToFutureByFuture();
	//void ReqFromFutureToBankByFuture();
	//void ReqOptionSelfCloseAction();
	//void ReqOptionSelfCloseInsert();
	void ReqOrderAction(int session_id);
	void ReqOrderInsert();
	//void ReqParkedOrderAction();
	//void ReqParkedOrderInsert();
	//void ReqQryAccountregister();
	//void ReqQryBrokerTradingAlgos();
	//void ReqQryBrokerTradingParams();
	//void ReqQueryCFMMCTradingAccountToken();
	//void ReqQryCombAction();
	//void ReqQryCombInstrumentGuard();
	//void ReqQryContractBank();
	//void ReqQryDepthMarketData();
	//void ReqQryEWarrantOffset();
	//void ReqQryExchange();
	//void ReqQryExchagneMarginRate();
	//void ReqQryExhcangeMarginRateAdjust();
	//void ReqQryExchangeRate();
	//void ReqQryExecOrder();
	//void ReqQryForQuote();
	void ReqQryInstrument();
	//void ReqQryInstrumentCommissionRate();
	//void ReqQryInstrumentMarginRate();
	//void ReqQryInstrumentOrderCommRate();
	//void ReqQryInvestor();
	//void ReqQryInvestorPosition();
	//void ReqQryInvestorPositionCombineDetail();
	//void ReqQryInvestorPositionDetail();
	//void ReqQryInvestorProductGroupMargin();
	//void ReqQryInvestUnit();
	//void ReqQryMMInstrumentCommisionRate();
	//void ReqQryMMOptionInstrCommRate();
	//void ReqQryNotice();
	//void ReqQryOptionInstrCommRate();
	//void ReqQryOptionInstrTradeCost();
	//void ReqQryOptionSelfClose();
	//void ReqQryOrder();
	//void ReqQryParkedOrder();
	//void ReqQryParkedOrderAction();
	//void ReqQryProduct();
	//void ReqQryProductExchRate();
	//void ReqQryProductGroup();
	//void ReqQryQuote();
	//void ReqQrySecAgentACIDMap();
	//void ReqQrySecAgentCheckMode();
	//void ReqQrySecAgentTradeInfo();
	//void ReqQrySecAgentTradingAccount();
	//void ReqQrySettlementInfo();
	//void ReqQrySettlementInfoConfirm();
	//void ReqQryTrade();
	//void ReqQryTradingAccount();
	//void ReqQryTradingCode();
	//void ReqQryTradingNotice();
	//void ReqQryTransferBank();
	//void ReqQryTransferSerial();
	//void ReqQueryBankAccountMoneyByFuture();
	//void ReqQueryCFMMCTradingAccountToken();
	//void ReqQryMaxOrderVolume();
	//void ReqQuoteAction();
	//void ReqQuoteInsert();
	//void ReqRemoveParkedOrder();
	//void ReqRemoveParkedOrderAction();
	void ReqSettlementInfoConfirm();
	//void ReqUserAuthMethod();
	//void SubmitUserSystemInfo();
	//void SubscribePrivateTopic();
	//void SubscribePublicTopic();
	//void ReqQryClassifiedInstrument();
	//void ReqQryCombPromotionParam();
	//void ReqQryRiskSettleInvstPosition();
	//void ReqQryRiskSettleProductStatus();
};