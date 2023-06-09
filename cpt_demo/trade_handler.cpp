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
	CThostFtdcUserPasswordUpdateField update_user_password = { 0 };
	strcpy_s(update_user_password.BrokerID, brokerID);
	strcpy_s(update_user_password.UserID, uId);
	strcpy_s(update_user_password.OldPassword, oldPassword);
	strcpy_s(update_user_password.NewPassword, newPassword);
	tdApi->ReqUserPasswordUpdate(&update_user_password, nRequestID++);
}

void TraderHandler::ReqTradingAccountPasswordUpdate(char* brokerID, char* currencyID, char* accountID,
	char* oldPassword, char* newPassword)
{
	CThostFtdcTradingAccountPasswordUpdateField update_trading_password = { 0 };
	strcpy_s(update_trading_password.BrokerID, brokerID);
	strcpy_s(update_trading_password.AccountID, accountID);
	strcpy_s(update_trading_password.OldPassword, oldPassword);
	strcpy_s(update_trading_password.NewPassword, newPassword);
	strcpy_s(update_trading_password.CurrencyID, currencyID);
	tdApi->ReqTradingAccountPasswordUpdate(&update_trading_password, nRequestID++);
}

void TraderHandler::ReqBatchOrderAction(char* brokerID, char* exchangeID, int frontID,
	char* investorID, char* investor_UnitID, int OrderActionRef)
{
	CThostFtdcInputBatchOrderActionField batch_order_action = { 0 };
	strcpy_s(batch_order_action.BrokerID, brokerID);
	strcpy_s(batch_order_action.UserID, uId);
	strcpy_s(batch_order_action.ExchangeID, exchangeID);
	batch_order_action.FrontID = frontID;
	strcpy_s(batch_order_action.InvestorID, investorID);
	strcpy_s(batch_order_action.InvestUnitID, investor_UnitID);
	batch_order_action.OrderActionRef = OrderActionRef;
	tdApi->ReqBatchOrderAction(&batch_order_action, nRequestID++);
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
void TraderHandler::ReqOrderAction(int session_id)
{
	//-822330096
	CThostFtdcInputOrderActionField input_order_action = { 0 };
	strcpy_s(input_order_action.BrokerID, brokerID);
	strcpy_s(input_order_action.InvestorID, uId);
	strcpy_s(input_order_action.ExchangeID, "SHFE");
	strcpy_s(input_order_action.UserID, uId);
	//strcpy_s(input_order_action.OrderSysID, "");
	input_order_action.FrontID = 1;
	input_order_action.SessionID = session_id;
	strcpy_s(input_order_action.OrderRef, "00001");
	strcpy_s(input_order_action.InstrumentID, "au2306");
	input_order_action.ActionFlag = THOST_FTDC_AF_Delete;
	tdApi->ReqOrderAction(&input_order_action, nRequestID++);
}
/*
* place order
*/
void TraderHandler::ReqOrderInsert()
{
	CThostFtdcInputOrderField in_order = { 0 };
	strcpy_s(in_order.BrokerID, brokerID);
	strcpy_s(in_order.InvestorID, investor_id);
	strcpy_s(in_order.ExchangeID, "SHFE");
	strcpy_s(in_order.InstrumentID, "au2306");
	strcpy_s(in_order.UserID, uId);
	strcpy_s(in_order.OrderRef, "00001");
	in_order.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	in_order.Direction = THOST_FTDC_D_Buy;
	in_order.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	in_order.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	in_order.LimitPrice = 449.0;
	in_order.VolumeTotalOriginal = 1;
	in_order.TimeCondition = THOST_FTDC_TC_GFD;
	in_order.VolumeCondition = THOST_FTDC_VC_AV;
	in_order.ContingentCondition = THOST_FTDC_CC_Immediately;
	in_order.StopPrice = 200;
	in_order.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	in_order.IsAutoSuspend = 0;
	in_order.IsSwapOrder = 0;
	tdApi->ReqOrderInsert(&in_order, nRequestID++);
}

void TraderHandler::ReqSettlementInfoConfirm()
{
	CThostFtdcSettlementInfoConfirmField settle_info_confirm = { 0 };
	strcpy_s(settle_info_confirm.BrokerID, brokerID);
	strcpy_s(settle_info_confirm.InvestorID, investor_id);
	tdApi->ReqSettlementInfoConfirm(&settle_info_confirm, nRequestID++);
}

void TraderHandler::ReqQryInstrument()
{
	CThostFtdcQryInstrumentField instrument = { 0 };
	strcpy_s(instrument.ExchangeID, "SHFE");
	strcpy_s(instrument.InstrumentID, "au2306");
	tdApi->ReqQryInstrument(&instrument, nRequestID++);
}