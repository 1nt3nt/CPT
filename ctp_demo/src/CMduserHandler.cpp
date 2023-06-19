#include "CMduserHandler.h"

using namespace std;

CMduserHandler::CMduserHandler(CThostFtdcMdApi* userMdApi) : mdApi(userMdApi) {};

CMduserHandler::~CMduserHandler() {};

// prevent nan, inf value
template<typename T> T validValue(T val)
{
    T ref = 0.0;
    return (val >= DBL_MAX) ? ref : val;
}

void CMduserHandler::OnFrontConnected()
{
    
    printf("On Front Connected \n");
    static const char* version = mdApi->GetApiVersion();
    printf("Current Version: %s\n", version);
 
}

void CMduserHandler::ReqAutenticate()
{
    CThostFtdcReqAuthenticateField auField;
    memset(&auField, 0, sizeof(auField));
    strcpy_s(auField.BrokerID, brokerID);
    strcpy_s(auField.UserID, uId);
    strcpy_s(auField.AppID, "simnow_client_test");
    strcpy_s(auField.AuthCode, "0000000000000000");
}

void CMduserHandler::Login()
{
    CThostFtdcReqUserLoginField logReq = { 0 };
    int status = mdApi->ReqUserLogin(&logReq, nRequestID++);
}

void CMduserHandler::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    printf("\n ----------------- Login Successfully----------------- \n");

    if (pRspUserLogin)
    {
        printf("\nTrading day: %s\n", pRspUserLogin->TradingDay);
        printf("LoginTime: %s\n", pRspUserLogin->LoginTime);
        printf("Broker ID: %s\n", pRspUserLogin->BrokerID);
        printf("User ID: %s\n", pRspUserLogin->UserID);
        printf("Session ID: %d\n", pRspUserLogin->SessionID);
        printf("Front ID: %d\n", pRspUserLogin->FrontID);
        printf("Session ID: %d\n", pRspUserLogin->SessionID);
        printf("Max Order Reference: %s\n", pRspUserLogin->MaxOrderRef);
    }
    if (pRspInfo)
    {
        printf("Error ID: %d\n", pRspInfo->ErrorID);
        printf("Error message: %s \n", pRspInfo->ErrorMsg);
    }
}

void CMduserHandler::Logout()
{
    CThostFtdcUserLogoutField logout = { 0 };
    strcpy_s(logout.BrokerID, brokerID);
    strcpy_s(logout.UserID, uId);
    mdApi->ReqUserLogout(&logout, nRequestID++);
}

void CMduserHandler::OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    if (pUserLogout)
    {
        printf("\nBrokerID: %s \n", pUserLogout->BrokerID);
        printf("UserID: %s \n", pUserLogout->UserID);
        printf("logout successfully!\n");
    }
    if (pRspInfo)
    {
        printf("Error ID: %d\n", pRspInfo->ErrorID);
        printf("Error message: %s \n", pRspInfo->ErrorMsg);
    }
}

void CMduserHandler::Subscribe()
{
    char** ppInstrument = new char* [50];
    ppInstrument[0] = (char*)"au2307";
    int status = mdApi->SubscribeMarketData(ppInstrument, 1);
}

void CMduserHandler::OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    if (pSpecificInstrument)
    {
        printf("\n ----------------- Subscription Successfully ----------------- \n");
        printf("\nInstrumentID: %s\n", pSpecificInstrument->InstrumentID);
    }
    if (pRspInfo)
    {
        printf("Error ID: %d\n", pRspInfo->ErrorID);
        printf("Error message: %s \n", pRspInfo->ErrorMsg);
    }
}

void CMduserHandler::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
    printf("\n ----------------- Depth Market Data ----------------- \n");

    if (pDepthMarketData)
    {
        printf("\n Trading day: %s\n", pDepthMarketData->TradingDay);
        printf("Action Day: %s\n", pDepthMarketData->ActionDay);
        printf("Ask Price1: %0.3lf\n", validValue(pDepthMarketData->AskPrice1));
        printf("Ask Volume1: %d\n", pDepthMarketData->AskVolume1);
        printf("Bid Price: %0.3lf\n", validValue(pDepthMarketData->BidPrice1));
        printf("Bid Volume1: %d\n", pDepthMarketData->BidVolume1);
        printf("BandingLowerPrice: %lf\n", validValue(pDepthMarketData->BandingLowerPrice));
        printf("BandingUpperPrice: %lf\n", validValue(pDepthMarketData->BandingUpperPrice));
        printf("Close Price: %0.3lf\n", validValue(pDepthMarketData->ClosePrice));
        printf("CurrDelta: %lf\n", validValue(pDepthMarketData->CurrDelta));
        printf("ExchangeID: %s\n", pDepthMarketData->ExchangeID);
        printf("ExchangeInstID: %s\n", pDepthMarketData->ExchangeInstID);    
        printf("HighestPrice: %lf\n", validValue(pDepthMarketData->HighestPrice));
        printf("InstrumentID: %s\n", pDepthMarketData->InstrumentID);
        printf("LastPrice: %lf\n", validValue(pDepthMarketData->LastPrice));
        printf("LowerLimitPrice: %lf\n", validValue(pDepthMarketData->LowerLimitPrice));
        printf("LowestPrice: %lf\n", validValue(pDepthMarketData->LowestPrice));
        printf("OpenInterest: %0.3lf\n", validValue(pDepthMarketData->OpenInterest));
        printf("Open Price: %0.3lf\n", validValue(pDepthMarketData->OpenPrice));
        printf("PreClosePrice: %0.3lf\n", validValue(pDepthMarketData->PreClosePrice));
        printf("PreDelta: %0.3lf\n", validValue(pDepthMarketData->PreDelta));
        printf("PreOpenInterest: %0.3lf\n", validValue(pDepthMarketData->PreOpenInterest));
        printf("PreSettlementPrice: %0.3lf\n", validValue(pDepthMarketData->PreSettlementPrice));
        printf("Settlement Price: %0.3lf\n", validValue(pDepthMarketData->SettlementPrice));
        printf("UpdateMillisec: %d\n", pDepthMarketData->UpdateMillisec);
        printf("UpdateTime: %s\n", pDepthMarketData->UpdateTime);
        printf("UpperLimitPrice: %0.3lf\n", validValue(pDepthMarketData->UpperLimitPrice));
        printf("Volume: %d\n", pDepthMarketData->Volume);
    }
}