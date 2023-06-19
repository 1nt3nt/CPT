#include "trader_handler.h"

TraderHandler::TraderHandler(CThostFtdcTraderApi* userTDApi) : tdApi(userTDApi) {};
TraderHandler::~TraderHandler() {};


void TraderHandler::Connect(char* tradeFront, CThostFtdcTraderSpi* tdSpi)
{
	tdApi = CThostFtdcTraderApi::CreateFtdcTraderApi(".\\flow\\");
	tdApi->RegisterSpi(tdSpi);
	tdApi->SubscribePublicTopic(THOST_TERT_QUICK);
	tdApi->SubscribePrivateTopic(THOST_TERT_QUICK);
	tdApi->RegisterFront(tradeFront);
	tdApi->Init();
	printf("%s\n", tdApi->GetApiVersion());
}

void TraderHandler::ReqUserLogin()
{
	CThostFtdcReqUserLoginField logReq = { 0 };
	strcpy_s(logReq.BrokerID, brokerID);
	strcpy_s(logReq.UserID, uId);
	strcpy_s(logReq.Password, "Splinter@1997");
	tdApi->ReqUserLogin(&logReq, ++nRequestID);
}

void TraderHandler::ReqUserLogout()
{
	CThostFtdcUserLogoutField logout = { 0 };
	strcpy_s(logout.BrokerID, brokerID);
	strcpy_s(logout.UserID, uId);
	tdApi->ReqUserLogout(&logout, nRequestID++);
}

void TraderHandler::ReqAuthenticate()
{
	CThostFtdcReqAuthenticateField authen = { 0 };
	strcpy_s(authen.BrokerID, brokerID);
	strcpy_s(authen.UserID, uId);
	strcpy_s(authen.UserProductInfo, "test");
	strcpy_s(authen.AppID, "simnow_client_test");
	strcpy_s(authen.AuthCode, "0000000000000000");
	tdApi->ReqAuthenticate(&authen, nRequestID++);
}

void TraderHandler::ReqUserPasswordUpdate(char* oldPassword, char* newPassword)
{
	CThostFtdcUserPasswordUpdateField updateUserAccount = { 0 };
	strcpy_s(updateUserAccount.BrokerID, brokerID);
	strcpy_s(updateUserAccount.UserID, uId);
	strcpy_s(updateUserAccount.OldPassword, oldPassword);
	strcpy_s(updateUserAccount.NewPassword, newPassword);
	tdApi->ReqUserPasswordUpdate(&updateUserAccount, nRequestID++);
}

void TraderHandler::ReqTradingAccountPasswordUpdate(char* brokerID, char* currencyID, char* accountID,
	char* oldPassword, char* newPassword)
{
	CThostFtdcTradingAccountPasswordUpdateField updateTradeAccount = { 0 };
	strcpy_s(updateTradeAccount.BrokerID, brokerID);
	strcpy_s(updateTradeAccount.AccountID, accountID);
	strcpy_s(updateTradeAccount.OldPassword, oldPassword);
	strcpy_s(updateTradeAccount.NewPassword, newPassword);
	strcpy_s(updateTradeAccount.CurrencyID, currencyID);
	tdApi->ReqTradingAccountPasswordUpdate(&updateTradeAccount, nRequestID++);
}

void TraderHandler::ReqBatchOrderAction(char* brokerID, char* exchangeID, int frontID,
	char* investorID, char* investor_UnitID, int OrderActionRef)
{
	CThostFtdcInputBatchOrderActionField batchOrderAction = { 0 };
	strcpy_s(batchOrderAction.BrokerID, brokerID);
	strcpy_s(batchOrderAction.UserID, uId);
	strcpy_s(batchOrderAction.ExchangeID, exchangeID);
	batchOrderAction.FrontID = frontID;
	strcpy_s(batchOrderAction.InvestorID, investorID);
	strcpy_s(batchOrderAction.InvestUnitID, investor_UnitID);
	batchOrderAction.OrderActionRef = OrderActionRef;
	tdApi->ReqBatchOrderAction(&batchOrderAction, nRequestID++);
}

//void TraderHandler::ReqCombActionInsert(char* brokerID, char* investorID, char* instrument_id,
//	char* exchangeID)
//{
//	CThostFtdcInputCombActionField input_comb_action = { 0 };
//	strcpy_s(input_comb_action.BrokerID, brokerID);
//	strcpy_s(input_comb_action.InvestorID, investorID);
//	strcpy_s(input_comb_action.ExchangeID, exchangeID);
//	strcpy_s(input_comb_action.InstrumentID, instrument_id);
//}

/*
* withdraw order
*/
void TraderHandler::ReqOrderAction(std::vector<std::string> orderSysIDVec)
{
	//-822330096
	CThostFtdcInputOrderActionField orderAction = { 0 };
	strcpy_s(orderAction.BrokerID, brokerID);
	strcpy_s(orderAction.InvestorID, uId);
	strcpy_s(orderAction.ExchangeID, "SHFE");
	strcpy_s(orderAction.UserID, uId);
	orderAction.OrderActionRef = 1;
	if (!orderSysIDVec.empty())
	{
		strcpy_s(orderAction.OrderSysID, orderSysIDVec[0].c_str());
	}
	orderAction.FrontID = 1;
	strcpy_s(orderAction.InstrumentID, "au2307");
	orderAction.ActionFlag = THOST_FTDC_AF_Delete;
	tdApi->ReqOrderAction(&orderAction, nRequestID++);
}
/*
* place order
*/
void TraderHandler::ReqOrderInsert()
{
	CThostFtdcInputOrderField insertOrder = { 0 };
	strcpy_s(insertOrder.BrokerID, brokerID);
	strcpy_s(insertOrder.InvestorID, investorID);
	strcpy_s(insertOrder.ExchangeID, "SHFE");
	strcpy_s(insertOrder.InstrumentID, "au2307");
	strcpy_s(insertOrder.UserID, uId);
	strcpy_s(insertOrder.OrderRef, "00001");
	insertOrder.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	insertOrder.Direction = THOST_FTDC_D_Buy;
	insertOrder.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	insertOrder.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	insertOrder.LimitPrice = 449.3;
	insertOrder.VolumeTotalOriginal = 1;
	insertOrder.TimeCondition = THOST_FTDC_TC_GFD;
	insertOrder.VolumeCondition = THOST_FTDC_VC_AV;
	insertOrder.ContingentCondition = THOST_FTDC_CC_Immediately;
	insertOrder.StopPrice = 200;
	insertOrder.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	insertOrder.IsAutoSuspend = 0;
	insertOrder.IsSwapOrder = 0;
	tdApi->ReqOrderInsert(&insertOrder, nRequestID++);
}

void TraderHandler::ReqSettlementInfoConfirm()
{
	CThostFtdcSettlementInfoConfirmField settleInfoConfirm = { 0 };
	strcpy_s(settleInfoConfirm.BrokerID, brokerID);
	strcpy_s(settleInfoConfirm.InvestorID, investorID);
	tdApi->ReqSettlementInfoConfirm(&settleInfoConfirm, nRequestID++);
}

void TraderHandler::ReqQryInstrument()
{
	CThostFtdcQryInstrumentField instrument = { 0 };
	strcpy_s(instrument.ExchangeID, "SHFE");
	strcpy_s(instrument.InstrumentID, "au2307");
	tdApi->ReqQryInstrument(&instrument, nRequestID++);
}