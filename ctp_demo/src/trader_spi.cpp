#include "trader_spi.h"
#include <stdio.h>

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

std::vector<std::string> TraderSpi::getOrderRef()
{
	return orderRefSet;
}

std::vector<std::string> TraderSpi::getOrderSysID()
{
	return orderSysIDSet;
}

void TraderSpi::OnFrontConnected()
{
	printf("----------------- On Front Connected -----------------\n");
}

void TraderSpi::OnFrontDisconnected(int nReason)
{
	printf("%d \n", nReason);
}

void TraderSpi::OnHeartBeatWarning(int nTimeLapse)
{
	printf("%d \n", nTimeLapse);
}

void TraderSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField* pOrderAction,
	CThostFtdcRspInfoField* pRspInfo)
{
	printf("\n ----------------- respond to an error occured during order withdraw ----------------- \n");
	if (pOrderAction)
	{
		printf("Action Date: %s\n", pOrderAction->ActionDate);
		printf("Action Flag: %c\n", pOrderAction->ActionFlag);
		printf("Action Time: %s\n", pOrderAction->ActionTime);
		printf("Broker ID: %s\n", pOrderAction->BrokerID);
		printf("Exchange ID: %s\n", pOrderAction->ExchangeID);
		printf("Front ID: %d\n", pOrderAction->FrontID);
		printf("Instrument ID: %s\n", pOrderAction->InstrumentID);
		printf("Investor ID: %s\n", pOrderAction->InvestorID);
		printf("Invest Unit ID: %s\n", pOrderAction->InvestUnitID);
		printf("LimitPrice: %lf\n", validValue(pOrderAction->LimitPrice));
		printf("OrderActionRef: %d\n", pOrderAction->OrderActionRef);
		printf("OrderAction Status: %c\n", pOrderAction->OrderActionStatus);
		printf("OrderRef: %s\n", pOrderAction->OrderRef);
		printf("OrderSysID: %s\n", pOrderAction->OrderSysID);
		printf("SessionID: %d\n", pOrderAction->SessionID);
		printf("StatusMsg: %s\n", pOrderAction->StatusMsg);
		printf("UserID: %s\n", pOrderAction->UserID);
		printf("VolumeChange: %d\n", pOrderAction->VolumeChange);
	}

	notification(pRspInfo);
}

void TraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField* pInputOrder,
	CThostFtdcRspInfoField* pRspInfo)
{
	printf("\n ----------------- respond to an error occured during order inserting -----------------\n");
	if (pInputOrder)
	{
		printf("Broker ID: %s\n", pInputOrder->BrokerID);
		printf("Exchange ID: %s\n", pInputOrder->ExchangeID);
		printf("CombHedgeFlag: %s\n", pInputOrder->CombHedgeFlag);
		printf("CombOffsetFlag: %s\n", pInputOrder->CombOffsetFlag);
		printf("ContingentCondition: %c\n", pInputOrder->ContingentCondition);
		printf("CurrencyID: %s\n", pInputOrder->CurrencyID);
		printf("Direction: %c\n", pInputOrder->Direction);
		printf("ForceCloseReason: %c\n", pInputOrder->ForceCloseReason);
		printf("ContingentCondition: %d\n", pInputOrder->IsAutoSuspend);
		printf("Instrument ID: %s\n", pInputOrder->InstrumentID);
		printf("Investor ID: %s\n", pInputOrder->InvestorID);
		printf("Invest Unit ID: %s\n", pInputOrder->InvestUnitID);
		printf("IsSwapOrder: %d\n", pInputOrder->IsSwapOrder);
		printf("LimitPrice: %lf\n", validValue(pInputOrder->LimitPrice));
		printf("MinVolume: %d\n", pInputOrder->MinVolume);
		printf("Order Price Type: %c\n", pInputOrder->OrderPriceType);
		printf("Order Ref: %s\n", pInputOrder->OrderRef);
		printf("Stop Price: %lf\n", validValue(pInputOrder->StopPrice));
		printf("TimeCondition: %c\n", pInputOrder->TimeCondition);
		printf("UserForceClose: %d\n", pInputOrder->UserForceClose);
		printf("UserID: %s\n", pInputOrder->UserID);
		printf("VolumeCondition: %c\n", pInputOrder->VolumeCondition);
		printf("VolumeTotalOriginal: %d\n", pInputOrder->VolumeTotalOriginal);
	}

	notification(pRspInfo);
}


void TraderSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, 
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- Respond for Authentication Process -----------------\n");
	if (pRspAuthenticateField)
	{
		printf("Broker ID: %s \n", pRspAuthenticateField->BrokerID);
		printf("User ID: %s \n", pRspAuthenticateField->UserID);
		printf("User Product Info: %s \n", pRspAuthenticateField->UserProductInfo);
	}
	printf("RequestID: %d \n", nRequestID);
	notification(pRspInfo);
}

void TraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, 
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- Respond to User Login -----------------\n");
	if (pRspUserLogin)
	{
		printf("Login Time: %s\n", pRspUserLogin->LoginTime);
		printf("Trading Day: %s\n", pRspUserLogin->TradingDay);
		printf("Broker ID: %s\n", pRspUserLogin->BrokerID);
		printf("User ID: %s\n", pRspUserLogin->UserID);
		printf("Front ID: %d\n", pRspUserLogin->FrontID);
		printf("Session ID: %d\n", pRspUserLogin->SessionID);
		printf("MaxOrderRef: %s\n", pRspUserLogin->MaxOrderRef);

		printf("Login successfully!\n");
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- Respond to User Logout -----------------\n");
	if (pUserLogout)
	{
		printf("Broker ID: %s\n",pUserLogout->BrokerID);
		printf("User ID: %s\n", pUserLogout->UserID);
		printf("logout successfully!\n");
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField* pUserPasswordUpdate,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to update user password -----------------\n");
	if (pUserPasswordUpdate)
	{
		printf("Broker ID: %s\n", pUserPasswordUpdate->BrokerID);
		printf("User ID: %s\n", pUserPasswordUpdate->UserID);
		printf("Old Password: %s\n", pUserPasswordUpdate->OldPassword);
		printf("New Password: %s\n", pUserPasswordUpdate->NewPassword);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField* pTradingAccountPasswordUpdate,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to update trader account password -----------------\n");
	if (pTradingAccountPasswordUpdate)
	{
		printf("Broker ID: %s\n", pTradingAccountPasswordUpdate->BrokerID);
		printf("Account ID: %s\n", pTradingAccountPasswordUpdate->AccountID);
		printf("Currency ID: %s\n", pTradingAccountPasswordUpdate->CurrencyID);
		printf("Old Password: %s\n", pTradingAccountPasswordUpdate->OldPassword);
		printf("New Password: %s\n", pTradingAccountPasswordUpdate->NewPassword);

	}
	notification(pRspInfo);
}

void TraderSpi::OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField* pRspUserAuthMethod,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to support which authentications by user -----------------\n");
	if (pRspUserAuthMethod)
		printf("Usable Authentication method: %d\n", pRspUserAuthMethod->UsableAuthMethod);

	notification(pRspInfo);
}

void TraderSpi::OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField* pRspGenUserCaptcha,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to get graphic verification code -----------------\n");
	if (pRspGenUserCaptcha)
	{
		printf("Broker ID: %s\n", pRspGenUserCaptcha->BrokerID);
		printf("User ID: %s\n", pRspGenUserCaptcha->UserID);
		printf("Graphic Info: %s\n", pRspGenUserCaptcha->CaptchaInfo);
		printf("Graphic Info Length: %d\n", pRspGenUserCaptcha->CaptchaInfoLen);

	}
	notification(pRspInfo);
}

void TraderSpi::OnRspGenUserText(CThostFtdcRspGenUserTextField* pRspGenUserText,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to get text verification code -----------------\n");

	if (pRspGenUserText)
		printf("Verification Sequence: %d\n", pRspGenUserText->UserTextSeq);

	notification(pRspInfo);
}

void TraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to insert order -----------------\n");
	if (pInputOrder)
	{
		printf("Account ID: %s\n", pInputOrder->AccountID);
		printf("Broker ID: %s\n", pInputOrder->BrokerID);
		printf("CombOffsetFlag: %s\n", pInputOrder->CombOffsetFlag);
		printf("CombHedgeFlag: %s\n", pInputOrder->CombHedgeFlag);
		printf("ContingentCondition: %c\n", pInputOrder->ContingentCondition);
		printf("ClientID: %s\n", pInputOrder->ClientID);
		printf("CurrencyID: %s\n", pInputOrder->CurrencyID);
		printf("Direction: %c\n", pInputOrder->Direction);
		printf("ExchangeID: %s\n", pInputOrder->ExchangeID);
		printf("Direction: %c\n", pInputOrder->ForceCloseReason);
		printf("GTD Date: %s\n", pInputOrder->GTDDate);
		printf("Investor ID: %s\n", pInputOrder->InvestorID);
		printf("Instrument ID: %s\n", pInputOrder->InstrumentID);
		printf("Invest Unit ID: %s\n", pInputOrder->InvestUnitID);
		printf("IsSwapOrder: %d\n", pInputOrder->IsSwapOrder);
		printf("IsAutoSuspend: %d\n", pInputOrder->IsAutoSuspend);
		printf("Limit Price: %lf\n", validValue(pInputOrder->LimitPrice));
		printf("MinVolume: %d\n", pInputOrder->MinVolume);		
		printf("Order Price Type: %c\n", pInputOrder->OrderPriceType);
		printf("OrderRef: %s\n", pInputOrder->OrderRef);
		printf("Stop Price: %lf\n", validValue(pInputOrder->StopPrice));
		printf("Time Condition: %c\n", pInputOrder->TimeCondition);
		printf("User ID: %s\n", pInputOrder->UserID);
		printf("UserForceClose: %d\n", pInputOrder->UserForceClose);
		printf("VolumeTotalOriginal: %d\n", pInputOrder->VolumeTotalOriginal);
		printf("Volume Condition: %c\n", pInputOrder->VolumeCondition);		
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspParkedOrderInsert(CThostFtdcParkedOrderField* pParkedOrder,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to pre-park inserting order -----------------\n");
	if (pParkedOrder)
	{
		printf("Broker ID: %s\n", pParkedOrder->BrokerID);
		printf("User ID: %s\n", pParkedOrder->UserID);
		printf("Account ID: %s\n", pParkedOrder->AccountID);
		printf("Investor ID: %s\n", pParkedOrder->InvestorID);
		printf("Order Price Type: %c\n", pParkedOrder->OrderPriceType);
		printf("OrderRef: %s\n", pParkedOrder->OrderRef);
		printf("Limit Price: %lf\n", pParkedOrder->LimitPrice);
		printf("VolumeTotalOriginal: %d\n", pParkedOrder->VolumeTotalOriginal);
		printf("Time Condition: %c\n", pParkedOrder->TimeCondition);
		printf("GTD Date: %s\n", pParkedOrder->GTDDate);
		printf("Volume Condition: %c\n", pParkedOrder->VolumeCondition);
		printf("CombOffsetFlag: %s\n", pParkedOrder->CombOffsetFlag);
		printf("MinVolume: %d\n", pParkedOrder->MinVolume);
		printf("Direction: %c\n", pParkedOrder->Direction);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField* pParkedOrderAction,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to pre-park withdrawing order -----------------\n");
	if (pParkedOrderAction)
	{
		printf("Broker ID: %s\n", pParkedOrderAction->BrokerID);
		printf("User ID: %s\n", pParkedOrderAction->UserID);
		printf("Parked Order Action ID: %s\n", pParkedOrderAction->ParkedOrderActionID);
		printf("Investor ID: %s\n", pParkedOrderAction->InvestorID);
		printf("OrderRef: %s\n", pParkedOrderAction->OrderRef);
		printf("Limit Price: %lf\n", pParkedOrderAction->LimitPrice);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField* pInputOrderAction,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to Withdraw order -----------------\n");
	if (pInputOrderAction)
	{		
		printf("Action Flag: %c\n", pInputOrderAction->ActionFlag);
		printf("Broker ID: %s\n", pInputOrderAction->BrokerID);
		printf("Exchange ID: %s\n", pInputOrderAction->ExchangeID);
		printf("Front ID: %d\n", pInputOrderAction->FrontID);
		printf("Investor ID: %s\n", pInputOrderAction->InvestorID);
		printf("Instrument ID: %s\n", pInputOrderAction->InstrumentID);
		printf("Invest Unit ID: %s\n", pInputOrderAction->InvestUnitID);
		printf("Limit Price: %lf\n", validValue(pInputOrderAction->LimitPrice));
		printf("OrderRef: %s\n", pInputOrderAction->OrderRef);
		printf("OrderActionRef: %d\n", pInputOrderAction->OrderActionRef);
		printf("OrderSysID: %s\n", pInputOrderAction->OrderSysID);
		printf("RequestID: %d\n", pInputOrderAction->RequestID);
		printf("SessionID: %d\n", pInputOrderAction->SessionID);
		printf("User ID: %s\n", pInputOrderAction->UserID);
		printf("VolumeChange: %d\n", pInputOrderAction->VolumeChange);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField* pQryMaxOrderVolume,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to query max order volume -----------------\n");

	if(pQryMaxOrderVolume)
	{
		printf("Broker ID: %s\n", pQryMaxOrderVolume->BrokerID);
		printf("Investor ID: %s\n", pQryMaxOrderVolume->InvestorID);
		printf("Exchange ID: %s\n", pQryMaxOrderVolume->ExchangeID);
		printf("Invest Unit ID: %s\n", pQryMaxOrderVolume->InvestUnitID);
		printf("Max Volume: %d\n", pQryMaxOrderVolume->MaxVolume);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to confirm settlement info -----------------\n");

	if (pSettlementInfoConfirm)
	{
		printf("Broker ID: %s\n", pSettlementInfoConfirm->BrokerID);
		printf("Account ID: %s\n", pSettlementInfoConfirm->AccountID);
		printf("Investor ID: %s\n", pSettlementInfoConfirm->InvestorID);
		printf("Confirm Date: %s\n", pSettlementInfoConfirm->ConfirmDate);
		printf("Confirm Time: %s\n", pSettlementInfoConfirm->ConfirmTime);
		printf("Settlement ID: %d\n", pSettlementInfoConfirm->SettlementID);
		printf("Currency ID: %s\n", pSettlementInfoConfirm->CurrencyID);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField* pRemoveParkedOrder,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to delete pre-pared order -----------------\n");
	if (pRemoveParkedOrder)
	{
		printf("Broker ID: %s\n", pRemoveParkedOrder->BrokerID);
		printf("Investor ID: %s\n", pRemoveParkedOrder->InvestorID);
		printf("Invest Unit ID: %s\n", pRemoveParkedOrder->InvestUnitID);
		printf("Parked Order ID: %s\n", pRemoveParkedOrder->ParkedOrderID);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField* pRemoveParkedOrderAction,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to delete pre-pard withdrawing order -----------------\n");
	if (pRemoveParkedOrderAction)
	{
		printf("Broker ID: %s\n", pRemoveParkedOrderAction->BrokerID);
		printf("Investor ID: %s\n", pRemoveParkedOrderAction->InvestorID);
		printf("Invest Unit ID: %s\n", pRemoveParkedOrderAction->InvestUnitID);
		printf("Parked Order Action ID: %s\n", pRemoveParkedOrderAction->ParkedOrderActionID);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspExecOrderInsert(CThostFtdcInputExecOrderField* pInputExecOrder,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to execute inserting order -----------------\n");
	if (pInputExecOrder)
	{
		printf("Broker ID: %s\n", pInputExecOrder->BrokerID);
		printf("Investor ID: %s\n", pInputExecOrder->InvestorID);
		printf("Invest Unit ID: %s\n", pInputExecOrder->InvestUnitID);
		printf("Action Type: %c\n", pInputExecOrder->ActionType);
		printf("Business Unit: %s\n", pInputExecOrder->BusinessUnit);
		printf("Volume: %d\n", pInputExecOrder->Volume);
		printf("Client ID: %s\n", pInputExecOrder->ClientID);
		printf("Currency ID: %s\n", pInputExecOrder->CurrencyID);
		printf("Exchange ID: %s\n", pInputExecOrder->ExchangeID);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField* pInputExecOrderAction,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to execute placing order -----------------\n");

	if (pInputExecOrderAction)
	{
		printf("Broker ID: %s\n", pInputExecOrderAction->BrokerID);
		printf("Investor ID: %s\n", pInputExecOrderAction->InvestorID);
		printf("Invest Unit ID: %s\n", pInputExecOrderAction->InvestUnitID);
		printf("Instrument ID: %s\n", pInputExecOrderAction->InstrumentID);
		printf("Request ID: %d\n", pInputExecOrderAction->RequestID);
		printf("Action Flag: %d\n", pInputExecOrderAction->ActionFlag);
		printf("ExecOrderSys ID: %s\n", pInputExecOrderAction->ExecOrderSysID);
		printf("Front ID: %d\n", pInputExecOrderAction->FrontID);
		printf("Exchange ID: %s\n", pInputExecOrderAction->ExchangeID);
		printf("Exchange ID: %s\n", pInputExecOrderAction->ExecOrderRef);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspForQuoteInsert(CThostFtdcInputForQuoteField* pInputForQuote,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond for inquiry -----------------\n");
	if (pInputForQuote)
	{
		printf("Broker ID: %s\n", pInputForQuote->BrokerID);
		printf("Investor ID: %s\n", pInputForQuote->InvestorID);
		printf("Invest Unit ID: %s\n", pInputForQuote->InvestUnitID);
		printf("Instrument ID: %s\n", pInputForQuote->InstrumentID);
		printf("For Quote Ref: %s\n", pInputForQuote->ForQuoteRef);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspQuoteInsert(CThostFtdcInputQuoteField* pInputQuote,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to quote -----------------\n");
	if (pInputQuote)
	{
		printf("Broker ID: %s\n", pInputQuote->BrokerID);
		printf("Investor ID: %s\n", pInputQuote->InvestorID);
		printf("Invest Unit ID: %s\n", pInputQuote->InvestUnitID);
		printf("Instrument ID: %s\n", pInputQuote->InstrumentID);
		printf("Ask Hedge Flag: %c\n", pInputQuote->AskHedgeFlag);
		printf("Ask Offset Flag: %c\n", pInputQuote->AskOffsetFlag);
		printf("Ask Order Ref: %s\n", pInputQuote->AskOrderRef);
		printf("Ask Price: %lf\n", validValue(pInputQuote->AskPrice));
		printf("Ask Volume: %d\n", pInputQuote->AskVolume);
		printf("Bid Hedge Flag: %c\n", pInputQuote->BidHedgeFlag);
		printf("Bid Offset Flag: %c\n", pInputQuote->BidOffsetFlag);
		printf("Bid Order Ref: %s\n", pInputQuote->BidOrderRef);
		printf("Bid Price: %lf\n", validValue(pInputQuote->BidPrice));
		printf("Bid Price: %d\n", pInputQuote->BidVolume);

	}
	notification(pRspInfo);
}

void TraderSpi::OnRspQuoteAction(CThostFtdcInputQuoteActionField* pInputQuoteAction,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to quote action -----------------\n");
	if (pInputQuoteAction)
	{
		printf("Broker ID: %s\n", pInputQuoteAction->BrokerID);
		printf("Investor ID: %s\n", pInputQuoteAction->InvestorID);
		printf("Invest Unit ID: %s\n", pInputQuoteAction->InvestUnitID);
		printf("Instrument ID: %s\n", pInputQuoteAction->InstrumentID);
		printf("Action Flag: %c\n", pInputQuoteAction->ActionFlag);
		printf("Exchange ID: %s\n", pInputQuoteAction->ExchangeID);
		printf("Quote Action Ref: %d\n", pInputQuoteAction->QuoteActionRef);
		printf("Quote Ref: %s\n", pInputQuoteAction->QuoteRef);
		printf("QuoteSysID: %s\n", pInputQuoteAction->QuoteSysID);
		printf("Front ID: %d\n", pInputQuoteAction->FrontID);

	}
	notification(pRspInfo);
}

void TraderSpi::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField* pInputBatchOrderAction,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to batch order operation -----------------\n");
	if (pInputBatchOrderAction)
	{
		printf("Broker ID: %s\n", pInputBatchOrderAction->BrokerID);
		printf("Investor ID: %s\n", pInputBatchOrderAction->InvestorID);
		printf("Invest Unit ID: %s\n", pInputBatchOrderAction->InvestUnitID);
		printf("Request ID: %d\n", pInputBatchOrderAction->RequestID);
		printf("Session ID: %d\n", pInputBatchOrderAction->SessionID);
		printf("Exchange ID: %s\n", pInputBatchOrderAction->ExchangeID);
		printf("Front ID: %d\n", pInputBatchOrderAction->FrontID);

	}
	notification(pRspInfo);
}

void TraderSpi::OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField* pInputOptionSelfClose,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond for options self-hedging inserting action -----------------\n");
	if (pInputOptionSelfClose)
	{
		printf("Broker ID: %s\n", pInputOptionSelfClose->BrokerID);
		printf("Investor ID: %s\n", pInputOptionSelfClose->InvestorID);
		printf("Invest Unit ID: %s\n", pInputOptionSelfClose->InvestUnitID);
		printf("Request ID: %d\n", pInputOptionSelfClose->RequestID);
		printf("Currency ID: %s\n", pInputOptionSelfClose->CurrencyID);
		printf("Exchange ID: %s\n", pInputOptionSelfClose->ExchangeID);
		printf("Instrument ID: %s\n", pInputOptionSelfClose->InstrumentID);
		printf("Instrument ID: %s\n", pInputOptionSelfClose->OptionSelfCloseRef);
		printf("Instrument ID: %c\n", pInputOptionSelfClose->OptSelfCloseFlag);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField* pInputOptionSelfCloseAction,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond for options self-hedging action -----------------\n");
	if (pInputOptionSelfCloseAction)
	{
		printf("Broker ID: %s\n", pInputOptionSelfCloseAction->BrokerID);
		printf("Investor ID: %s\n", pInputOptionSelfCloseAction->InvestorID);
		printf("Invest Unit ID: %s\n", pInputOptionSelfCloseAction->InvestUnitID);
		printf("Request ID: %d\n", pInputOptionSelfCloseAction->RequestID);
		printf("Exchange ID: %s\n", pInputOptionSelfCloseAction->ExchangeID);
		printf("Instrument ID: %s\n", pInputOptionSelfCloseAction->InstrumentID);
		printf("Option Self-Close Action Ref: %d\n", pInputOptionSelfCloseAction->OptionSelfCloseActionRef);
		printf("Option Self-Close Ref: %s\n", pInputOptionSelfCloseAction->OptionSelfCloseRef);
		printf("Option Self-Close Sys ID: %s\n", pInputOptionSelfCloseAction->OptionSelfCloseSysID);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspCombActionInsert(CThostFtdcInputCombActionField* pInputCombAction,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to combine inserting action -----------------\n");
	if (pInputCombAction)
	{
		printf("Broker ID: %s\n", pInputCombAction->BrokerID);
		printf("Investor ID: %s\n", pInputCombAction->InvestorID);
		printf("Invest Unit ID: %s\n", pInputCombAction->InvestUnitID);
		printf("Direction: %c\n", pInputCombAction->Direction);
		printf("Exchange ID: %s\n", pInputCombAction->ExchangeID);
		printf("Instrument ID: %s\n", pInputCombAction->InstrumentID);
		printf("CombActionRef: %s\n", pInputCombAction->CombActionRef);
		printf("CombDirection: %c\n", pInputCombAction->CombDirection);
		printf("Front ID: %d\n", pInputCombAction->FrontID);
		printf("Front ID: %d\n", pInputCombAction->Volume);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspQryOrder(CThostFtdcOrderField* pOrder,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to inquiry order -----------------\n");
	if (pOrder)
	{
		printf("Broker ID: %s\n", pOrder->BrokerID);
		printf("Investor ID: %s\n", pOrder->InvestorID);
		printf("Invest Unit ID: %s\n", pOrder->InvestUnitID);
		printf("Direction: %c\n", pOrder->Direction);
		printf("Exchange ID: %s\n", pOrder->ExchangeID);
		printf("Instrument ID: %s\n", pOrder->InstrumentID);
		printf("Account ID: %s\n", pOrder->AccountID);
		printf("ActiveTime: %s\n", pOrder->ActiveTime);
		printf("Front ID: %d\n", pOrder->FrontID);
		printf("Currency ID: %s\n", pOrder->CurrencyID);
		printf("Cancel Time: %s\n", pOrder->CancelTime);
		printf("Clearing Part ID: %s\n", pOrder->ClearingPartID);
		printf("Client ID: %s\n", pOrder->ClientID);
		printf("Comb Hedge Flag: %s\n", pOrder->CombHedgeFlag);
		printf("Comb Offset Flag: %s\n", pOrder->CombOffsetFlag);
		printf("Contingent Condition: %c\n", pOrder->ContingentCondition);
		printf("Branch ID: %s\n", pOrder->BranchID);
		printf("Broker Order Seq: %d\n", pOrder->BrokerOrderSeq);
		printf("Business Unit: %s\n", pOrder->BusinessUnit);
		printf("Force Close Reason: %c\n", pOrder->ForceCloseReason);
		printf("Insert Date: %s\n", pOrder->InsertDate);
		printf("Insert Time: %s\n", pOrder->InsertTime);
		printf("Install ID: %d\n", pOrder->InstallID);
		printf("Auto Suspend: %d\n", pOrder->IsAutoSuspend);
		printf("Swap Order: %d\n", pOrder->IsSwapOrder);
		printf("Limit Price: %lf\n", validValue(pOrder->LimitPrice));
		printf("Min Volume: %d\n", validValue(pOrder->MinVolume));
		printf("Settlement ID: %d\n", pOrder->SettlementID);
		printf("Status Msg: %s\n", pOrder->StatusMsg);
		printf("Stop Price: %lf\n", validValue(pOrder->StopPrice));
		printf("Suspend Time: %s\n", pOrder->SuspendTime);
		printf("User Force Close: %d\n", pOrder->UserForceClose);
		printf("User Product Info: %s\n", pOrder->UserProductInfo);
		printf("VolumeCondition: %c\n", pOrder->VolumeCondition);
		printf("VolumeTotal: %d\n", pOrder->VolumeTotal);
		printf("VolumeTotalOriginal: %d\n", pOrder->VolumeTotalOriginal);
		printf("VolumeTraded: %d\n", pOrder->VolumeTraded);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspQryTrade(CThostFtdcTradeField* pTrade,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to inquiry order -----------------\n");
	if (pTrade)
	{
		printf("Broker ID: %s\n", pTrade->BrokerID);
		printf("Investor ID: %s\n", pTrade->InvestorID);
		printf("Invest Unit ID: %s\n", pTrade->InvestUnitID);
		printf("Direction: %c\n", pTrade->Direction);
		printf("Exchange ID: %s\n", pTrade->ExchangeID);
		printf("Instrument ID: %s\n", pTrade->InstrumentID);
		printf("Offset Flag: %c\n", pTrade->OffsetFlag);

	}
	notification(pRspInfo);
}

void TraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to request investor postion -----------------\n");
	if (pInvestorPosition)
	{
		printf("Broker ID: %s\n", pInvestorPosition->BrokerID);
		printf("Investor ID: %s\n", pInvestorPosition->InvestorID);
		printf("Invest Unit ID: %s\n", pInvestorPosition->InvestUnitID);
		printf("Exchange ID: %s\n", pInvestorPosition->ExchangeID);
		printf("Instrument ID: %s\n", pInvestorPosition->InstrumentID);
		printf("Close Amount: %lf\n", validValue(pInvestorPosition->CloseAmount));
		printf("Close Profit: %lf\n", validValue(pInvestorPosition->CloseProfit));
		printf("Close Profit By Date: %lf\n", validValue(pInvestorPosition->CloseProfitByDate));
		printf("Close Profit By Trade: %lf\n", validValue(pInvestorPosition->CloseProfitByTrade));
		printf("Close Volume: %d\n", validValue(pInvestorPosition->CloseVolume));
		printf("CombLongFrozen: %d\n", validValue(pInvestorPosition->CombLongFrozen));
		printf("CombPosition: %d\n", validValue(pInvestorPosition->CombPosition));
		printf("CombShortFrozen: %d\n", validValue(pInvestorPosition->CombShortFrozen));
		printf("Commission: %lf\n", validValue(pInvestorPosition->Commission));
		printf("ExchangeMargin: %lf\n", validValue(pInvestorPosition->ExchangeMargin));
		printf("FrozenCash: %lf\n", validValue(pInvestorPosition->FrozenCash));
		printf("FrozenCommission: %lf\n", validValue(pInvestorPosition->FrozenCommission));
		printf("FrozenMargin: %lf\n", validValue(pInvestorPosition->FrozenMargin));
		printf("HedgeFlag: %c\n", pInvestorPosition->HedgeFlag);
		printf("ShortFrozen: %d\n", pInvestorPosition->ShortFrozen);
		printf("ShortFrozenAmount: %lf\n", validValue(pInvestorPosition->ShortFrozenAmount));
		printf("LongFrozen: %d\n", pInvestorPosition->LongFrozen);
		printf("LongFrozenAmount: %lf\n", validValue(pInvestorPosition->LongFrozenAmount));
		printf("MarginRateByMoney: %lf\n", validValue(pInvestorPosition->MarginRateByMoney));
		printf("MarginRateByVolume: %lf\n", validValue(pInvestorPosition->MarginRateByVolume));
		printf("OpenAmount: %lf\n", validValue(pInvestorPosition->OpenAmount));
		printf("OpenCost: %lf\n", validValue(pInvestorPosition->OpenCost));
		printf("OpenVolume: %d\n", validValue(pInvestorPosition->OpenVolume));
		printf("PosiDirection: %c\n", pInvestorPosition->PosiDirection);
		printf("Position: %d\n", pInvestorPosition->Position);
		printf("PositionCost: %lf\n", validValue(pInvestorPosition->PositionCost));
		printf("PositionCostOffset: %lf\n", validValue(pInvestorPosition->PositionCostOffset));
		printf("PositionDate: %c\n", pInvestorPosition->PositionDate);
		printf("PositionProfit: %lf\n", pInvestorPosition->PositionProfit);
		printf("PreMargin: %lf\n", validValue(pInvestorPosition->PreMargin));
		printf("PreSettlementPrice: %lf\n", validValue(pInvestorPosition->PreSettlementPrice));
		printf("SettlementPrice: %lf\n", validValue(pInvestorPosition->SettlementPrice));
		printf("TasPosition: %d\n", pInvestorPosition->TasPosition);
		printf("TasPositionCost: %lf\n", validValue(pInvestorPosition->TasPositionCost));
		printf("TodayPosition: %d\n", pInvestorPosition->TodayPosition);
		printf("TradingDay: %s\n", pInvestorPosition->TradingDay);
		printf("YdPosition: %d\n", pInvestorPosition->YdPosition);
		printf("TradingDay: %d\n", pInvestorPosition->YdStrikeFrozen);
	}
	notification(pRspInfo);
}

void TraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to inquiry trading account -----------------\n");
	if (pTradingAccount)
	{
		printf("Broker ID: %s\n", pTradingAccount->BrokerID);
		printf("Account ID: %s\n", pTradingAccount->AccountID);
		printf("Currency ID: %s\n", pTradingAccount->CurrencyID);
		printf("Available: %lf\n", validValue(pTradingAccount->Available));
		printf("Balance: %lf\n", validValue(pTradingAccount->Balance));
		printf("BizType: %c\n", pTradingAccount->BizType);
		printf("CashIn: %lf\n", validValue(pTradingAccount->CashIn));
		printf("CloseProfit: %lf\n", validValue(pTradingAccount->CloseProfit));
		printf("Commission: %lf\n", validValue(pTradingAccount->Commission));
		printf("Credit: %lf\n", validValue(pTradingAccount->Credit));
		printf("CurrMargin: %lf\n", validValue(pTradingAccount->CurrMargin));
		printf("DeliveryMargin: %lf\n", validValue(pTradingAccount->DeliveryMargin));
		printf("Deposit: %lf\n", validValue(pTradingAccount->Deposit));
		printf("ExchangeDeliveryMargin: %lf\n", validValue(pTradingAccount->ExchangeDeliveryMargin));
		printf("ExchangeMargin: %lf\n", validValue(pTradingAccount->ExchangeMargin));
		printf("FrozenCash: %lf\n", validValue(pTradingAccount->FrozenCash));
		printf("FrozenCommission: %lf\n", validValue(pTradingAccount->FrozenCommission));
		printf("FrozenMargin: %lf\n", validValue(pTradingAccount->FrozenMargin));
		printf("FrozenSwap: %lf\n", validValue(pTradingAccount->FrozenSwap));
		printf("FundMortgageAvailable: %lf\n", validValue(pTradingAccount->FundMortgageAvailable));
		printf("FundMortgageIn: %lf\n", validValue(pTradingAccount->FundMortgageIn));
		printf("FundMortgageOut: %lf\n", validValue(pTradingAccount->FundMortgageOut));
		printf("Interest: %lf\n", validValue(pTradingAccount->Interest));
		printf("InterestBase: %lf\n", validValue(pTradingAccount->InterestBase));
		printf("Mortgage: %lf\n", validValue(pTradingAccount->Mortgage));
		printf("MortgageableFund: %lf\n", validValue(pTradingAccount->MortgageableFund));
		printf("PositionProfit: %lf\n", validValue(pTradingAccount->PositionProfit));
		printf("PreBalance: %lf\n", validValue(pTradingAccount->PreBalance));
		printf("PreCredit: %lf\n", validValue(pTradingAccount->PreCredit));
		printf("PreCredit: %lf\n", validValue(pTradingAccount->PreDeposit));
		printf("PreFundMortgageIn: %lf\n", validValue(pTradingAccount->PreFundMortgageIn));
		printf("PreFundMortgageOut: %lf\n", validValue(pTradingAccount->PreFundMortgageOut));
		printf("PreMargin: %lf\n", validValue(pTradingAccount->PreMargin));
		printf("PreMortgage: %lf\n", validValue(pTradingAccount->PreMortgage));
		printf("RemainSwap: %lf\n", validValue(pTradingAccount->RemainSwap));
		printf("Reserve: %lf\n", validValue(pTradingAccount->Reserve));
		printf("ReserveBalance: %lf\n", validValue(pTradingAccount->ReserveBalance));
		printf("Settlement ID: %d\n", pTradingAccount->SettlementID);
		printf("SpecProductCloseProfit: %lf\n", validValue(pTradingAccount->SpecProductCloseProfit));
		printf("SpecProductCommission: %lf\n", validValue(pTradingAccount->SpecProductCommission));
		printf("SpecProductExchangeMargin: %lf\n", validValue(pTradingAccount->SpecProductExchangeMargin));
		printf("SpecProductFrozenCommission: %lf\n", validValue(pTradingAccount->SpecProductFrozenCommission));
		printf("SpecProductFrozenMargin: %lf\n", validValue(pTradingAccount->SpecProductFrozenMargin));
		printf("SpecProductPositionProfit: %lf\n", validValue(pTradingAccount->SpecProductPositionProfit));
		printf("SpecProductPositionProfitByAlg: %lf\n", validValue(pTradingAccount->SpecProductPositionProfitByAlg));
		printf("TradingDay: %s\n", pTradingAccount->TradingDay);
		printf("Withdraw: %lf\n", pTradingAccount->Withdraw);
		printf("WithdrawQuota: %lf\n", pTradingAccount->WithdrawQuota);
	}

	notification(pRspInfo);
}

void TraderSpi::OnRspQryInvestor(CThostFtdcInvestorField* pInvestor,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to inquiry investor -----------------\n");
	if (pInvestor)
	{
		printf("Broker ID: %s\n", pInvestor->BrokerID);
		printf("Address: %s\n", pInvestor->Address);
		printf("CommModel ID: %s\n", pInvestor->CommModelID);
		printf("Identified CardNo: %s\n", pInvestor->IdentifiedCardNo);
		printf("Identified CardType: %c\n", pInvestor->IdentifiedCardType);
		printf("InvestorGroup ID: %s\n", pInvestor->InvestorGroupID);
		printf("Investor ID: %s\n", pInvestor->InvestorID);
		printf("Investor Name: %s\n", pInvestor->InvestorName);
		printf("IsActive: %d\n", pInvestor->IsActive);
		printf("MarginModel ID: %s\n", pInvestor->MarginModelID);
		printf("Mobile: %s\n", pInvestor->Mobile);
		printf("OpenDate: %s\n", pInvestor->OpenDate);
		printf("Telephone: %s\n", pInvestor->Telephone);
	}

	notification(pRspInfo);
}

void TraderSpi::OnRspQryTradingCode(CThostFtdcTradingCodeField* pTradingCode,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to inquiry transaction code -----------------\n");
	if (pTradingCode)
	{
		printf("Broker ID: %s\n", pTradingCode->BrokerID);
		printf("BizType: %c\n", pTradingCode->BizType);
		printf("Branch ID: %s\n", pTradingCode->BranchID);
		printf("Client ID: %s\n", pTradingCode->ClientID);
		printf("Client ID Type: %c\n", pTradingCode->ClientIDType);
		printf("Exchange ID: %s\n", pTradingCode->ExchangeID);
		printf("Investor ID: %s\n", pTradingCode->InvestorID);
		printf("Investor Unit ID: %s\n", pTradingCode->InvestUnitID);
		printf("IsActive: %d\n", pTradingCode->IsActive);
	}

	notification(pRspInfo);
}

void TraderSpi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField* pInstrumentMarginRate,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to inquiry instrument margin rate -----------------\n");
	if (pInstrumentMarginRate)
	{
		printf("Broker ID: %s\n", pInstrumentMarginRate->BrokerID);
		printf("HedgeFlag: %c\n", pInstrumentMarginRate->HedgeFlag);
		printf("Instrument ID: %s\n", pInstrumentMarginRate->InstrumentID);
		printf("IsRelative: %d\n", pInstrumentMarginRate->IsRelative);
		printf("LongMarginRatioByMoney: %lf\n", validValue(pInstrumentMarginRate->LongMarginRatioByMoney));
		printf("LongMarginRatioByVolume: %lf\n", validValue(pInstrumentMarginRate->LongMarginRatioByVolume));
		printf("reserve1: %s\n", pInstrumentMarginRate->reserve1);
		printf("ShortMarginRatioByMoney: %lf\n", validValue(pInstrumentMarginRate->ShortMarginRatioByMoney));
		printf("ShortMarginRatioByVolume: %lf\n", validValue(pInstrumentMarginRate->ShortMarginRatioByVolume));
	}

	notification(pRspInfo);
}

void TraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to inquiry instrument -----------------\n");
	if (pInstrument)
	{
		printf("CombinationType: %c\n", pInstrument->CombinationType);
		printf("CreateDate: %s\n", pInstrument->CreateDate);
		printf("DeliveryMonth: %d\n", pInstrument->DeliveryMonth);
		printf("DeliveryYear: %d\n", pInstrument->DeliveryYear);
		printf("EndDelivDate: %s\n", pInstrument->EndDelivDate);
		printf("Exchange ID: %s\n", pInstrument->ExchangeID);
		printf("ExchangeInstID: %s\n", pInstrument->ExchangeInstID);
		printf("ExpireDate: %s\n", pInstrument->ExpireDate);
		printf("Instrument ID: %s\n", pInstrument->InstrumentID);
		printf("Instrument Name: %s\n", pInstrument->InstrumentName);
		printf("IsTrading: %d\n", pInstrument->IsTrading);
		printf("LongMarginRatio: %lf\n", validValue(pInstrument->LongMarginRatio));
		printf("MaxLimitOrderVolume: %d\n", pInstrument->MaxLimitOrderVolume);
		printf("MaxMarginSideAlgorithm: %c\n", pInstrument->MaxMarginSideAlgorithm);
		printf("MaxMarketOrderVolume: %d\n", pInstrument->MaxMarketOrderVolume);
		printf("MinLimitOrderVolume: %d\n", pInstrument->MinLimitOrderVolume);
		printf("MinMarketOrderVolume: %d\n", pInstrument->MinMarketOrderVolume);
		printf("Open Date: %s\n", pInstrument->OpenDate);
		printf("Options Type: %c\n", pInstrument->OptionsType);
		printf("Position Date Type: %c\n", pInstrument->PositionDateType);
		printf("Position Type: %c\n", pInstrument->PositionType);
		printf("PriceTick: %lf\n", pInstrument->PriceTick);
		printf("ProductClass: %c\n", pInstrument->ProductClass);
		printf("Product ID: %s\n", pInstrument->ProductID);
		printf("StartDelivDate: %s\n", pInstrument->StartDelivDate);
	}

	notification(pRspInfo);
}

void TraderSpi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField* pInstrumentCommissionRate,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to inquiry instrument commmission rate -----------------\n");
	if (pInstrumentCommissionRate)
	{
		printf("Broker ID: %s\n", pInstrumentCommissionRate->BrokerID);
		printf("BizType: %c\n", pInstrumentCommissionRate->BizType);
		printf("Instrument ID: %s\n", pInstrumentCommissionRate->InstrumentID);
		printf("CloseRatioByMoney: %lf\n", validValue(pInstrumentCommissionRate->CloseRatioByMoney));
		printf("CloseRatioByVolume: %lf\n", validValue(pInstrumentCommissionRate->CloseRatioByVolume));
		printf("CloseTodayRatioByMoney: %lf\n", validValue(pInstrumentCommissionRate->CloseTodayRatioByMoney));
		printf("CloseTodayRatioByVolume: %lf\n", validValue(pInstrumentCommissionRate->CloseTodayRatioByVolume));
		printf("Exchange ID: %s\n", pInstrumentCommissionRate->ExchangeID);
		printf("Investor ID: %s\n", pInstrumentCommissionRate->InvestorID);
		printf("InvestorRange: %c\n", pInstrumentCommissionRate->InvestorRange);
		printf("Invest Unit ID: %s\n", pInstrumentCommissionRate->InvestUnitID);
		printf("OpenRatioByMoney: %lf\n", validValue(pInstrumentCommissionRate->OpenRatioByMoney));
		printf("OpenRatioByVolume: %lf\n", validValue(pInstrumentCommissionRate->OpenRatioByVolume));
		printf("reserve1: %s\n", pInstrumentCommissionRate->reserve1);
	}

	notification(pRspInfo);
}

void TraderSpi::OnRspQryExchange(CThostFtdcExchangeField* pExchange,
	CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	printf("\n ----------------- respond to inquiry exchange -----------------\n");
	if (pExchange)
	{
		printf("Exchange ID: %s\n", pExchange->ExchangeID);
		printf("Exchange Name: %s\n", pExchange->ExchangeName);
		printf("ExchangeProperty: %c\n", pExchange->ExchangeProperty);
	}

	notification(pRspInfo);
}

void TraderSpi::OnRtnOrder(CThostFtdcOrderField* pOrder)
{
	printf("\n ----------------- respond to order insert -----------------\n");
	if (pOrder)
	{
		printf("ActiveTime: %s\n", pOrder->ActiveTime);
		printf("Active Trader ID: %s\n", pOrder->ActiveTraderID);
		printf("Active User ID: %s\n", pOrder->ActiveUserID);
		printf("Broker ID: %s\n", pOrder->BrokerID);
		printf("BrokerOrderSeq: %d\n", pOrder->BrokerOrderSeq);
		printf("CancelTime: %s\n", pOrder->CancelTime);
		printf("CombHedgeFlag: %s\n", pOrder->CombHedgeFlag);
		printf("CombOffsetFlag: %s\n", pOrder->CombOffsetFlag);
		printf("ContingentCondition: %c\n", pOrder->ContingentCondition);
		printf("Currency ID: %s\n", pOrder->CurrencyID);
		printf("Direction: %c\n", pOrder->Direction);
		printf("Exchange ID: %s\n", pOrder->ExchangeID);
		printf("ForceCloseReason: %c\n", pOrder->ForceCloseReason);
		printf("Front ID: %d\n", pOrder->FrontID);
		printf("Insert Date: %s\n", pOrder->InsertDate);
		printf("Insert Time: %s\n", pOrder->InsertTime);
		printf("Instrument ID: %s\n", pOrder->InstrumentID);
		printf("Investor ID: %s\n", pOrder->InvestorID);
		printf("Invest Unit ID: %s\n", pOrder->InvestUnitID);
		printf("IsAutoSuspend: %d\n", pOrder->IsAutoSuspend);
		printf("IsSwapOrder: %d\n", pOrder->IsSwapOrder);
		printf("LimitPrice: %lf\n", validValue(pOrder->LimitPrice));
		printf("MinVolume: %d\n", pOrder->MinVolume);
		printf("OrderPriceType: %c\n", pOrder->OrderPriceType);
		printf("OrderRef: %s\n", pOrder->OrderRef);
		printf("OrderSys ID: %s\n", pOrder->OrderSysID);
		printf("OrderStatus: %c\n", pOrder->OrderStatus);
		printf("OrderType: %c\n", pOrder->OrderType);
		printf("SessionID: %d\n", pOrder->SessionID);
		printf("SettlementID: %d\n", pOrder->SettlementID);
		printf("StatusMsg: %s\n", pOrder->StatusMsg);
		printf("StopPrice: %lf\n", validValue(pOrder->StopPrice));
		printf("TimeCondition: %c\n", pOrder->TimeCondition);
	}
}

void TraderSpi::OnRtnTrade(CThostFtdcTradeField* pTrade)
{
	printf("\n ----------------- respond to trading -----------------\n");
	if (pTrade)
	{
		printf("BrokerID: %s\n", pTrade->BrokerID);
		printf("BrokerOrderSeq: %d\n", pTrade->BrokerOrderSeq);
		printf("Direction: %c\n", pTrade->Direction);
		printf("Exchange ID: %s\n", pTrade->ExchangeID);
		printf("HedgeFlag: %c\n", pTrade->HedgeFlag);
		printf("Instrument ID: %s\n", pTrade->InstrumentID);
		printf("Investor ID: %s\n", pTrade->InvestorID);
		printf("Invest Unit ID: %s\n", pTrade->InvestUnitID);
		printf("OffsetFlag: %c\n", pTrade->OffsetFlag);
		printf("OrderRef: %s\n", pTrade->OrderRef);
		orderRefSet.push_back(pTrade->OrderRef);
		printf("OrderSys ID: %s\n", pTrade->OrderSysID);
		orderSysIDSet.push_back(pTrade->OrderSysID);
		printf("Price: %lf\n", validValue(pTrade->Price));
		printf("PriceSource: %c\n", pTrade->PriceSource);
		printf("Settlement ID: %d\n", pTrade->SettlementID);
		printf("TradeDate: %s\n", pTrade->TradeDate);
		printf("UserID: %s\n", pTrade->UserID);
		printf("Volume: %d\n", pTrade->Volume);
	}
}