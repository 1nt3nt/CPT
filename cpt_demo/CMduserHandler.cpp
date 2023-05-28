#include <CMduserHandler.h>

using namespace std;

CMduserHandler::CMduserHandler(CThostFtdcMdApi* userMdApi) : mdApi(userMdApi) {};

CMduserHandler::~CMduserHandler() {}

void CMduserHandler::connect()
{
    mdApi->RegisterSpi(this);
    mdApi->RegisterFront((char*)"tcp://180.168.146.187:10131");
    mdApi->Init();
}

void CMduserHandler::ReqUserLogin()
{
    CThostFtdcReqUserLoginField logReq = { 0 };
    strcpy_s(logReq.BrokerID, brokerID);
    int status = mdApi->ReqUserLogin(&logReq, nRequestID++);
    //std::string BrokerID, password;
    try
    {
        strcpy_s(logReq.BrokerID, brokerID);
        int status = mdApi->ReqUserLogin(&logReq, nRequestID++);
        if (status == 0)
        {
            cout << "Login successfully";
        }
        else throw(status);
    }
    catch (int fail)
    {
        cout << "Fail to Login, error code: " << fail << "\n";
        cout << "Error code explanation" << "\n";
        switch (fail)
        {
        case -1:
            cout << "Internet Disconnected \n";
            break;
        case -2:
            cout << "Outstanding requests exceed number of licenses \n";
            break;
        case -3:
            cout << "The number of requests sent per second exceeds the number of licenses \n";
            break;
        default:
            break;
        }
    }
}

void CMduserHandler::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspUserLogin)
    {
        cout << pRspUserLogin->TradingDay << '\n';
        cout << pRspUserLogin->LoginTime << '\n';
    }
    if (pRspInfo)
    {
        cout << pRspInfo->ErrorID << '\n';
        cout << pRspInfo->ErrorMsg << '\n';
    }
}

void CMduserHandler::logout()
{
    CThostFtdcUserLogoutField logout = { 0 };
    strcpy_s(logout.BrokerID, brokerID);
    mdApi->ReqUserLogout(&logout, nRequestID++);
    cout << "logout successfully";
}

void CMduserHandler::OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    if (pUserLogout)
    {
        cout << pUserLogout->BrokerID;
        cout << pUserLogout->UserID;
    }
    if (pRspInfo)
        cout << pRspInfo->ErrorMsg;
}

void CMduserHandler::subscribe()
{
    char** ppInstrument = new char* [50];
    ppInstrument[0] = (char*)"IF1809";
    try
    {
        int status = mdApi->SubscribeMarketData(ppInstrument, 1);
        if (status == 0) cout << "Subscription Request Sent successfully \n";
        else throw(status);
    }
    catch (int fail)
    {
        cout << "Fail to subscribe, error code: " << fail << "\n";
        cout << "Error code explanation" << "\n";
        switch (fail)
        {
        case -1:
            cout << "Internet Disconnected \n";
            break;
        case -2:
            cout << "Outstanding requests exceed number of licenses \n";
            break;
        case -3:
            cout << "The number of requests sent per second exceeds the number of licenses \n";
            break;
        default:
            break;
        }
    }

}

void CMduserHandler::OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    if (pSpecificInstrument)
    {
        cout << pSpecificInstrument->InstrumentID;
    }
}

void CMduserHandler::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
    printf( pDepthMarketData->TradingDay);
}