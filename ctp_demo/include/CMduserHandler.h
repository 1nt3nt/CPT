#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <math.h>
#include <float.h>
#include <ctime>
#include "ThostFtdcMdApi.h"


class CMduserHandler : public CThostFtdcMdSpi
{
private:
    CThostFtdcMdApi* mdApi;
    TThostFtdcBrokerIDType brokerID = "9999";
    TThostFtdcUserIDType uId = "214060";
    int nRequestID = 0;

    // constructor & destructor
public:
    CMduserHandler(CThostFtdcMdApi* userMdApi);

    ~CMduserHandler();

    // methods
public:
    void ReqAutenticate();

    void Login();

    void Logout();

    void Subscribe();

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnFrontConnected();

    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData);
};