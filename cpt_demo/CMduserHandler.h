#pragma once
#include <string>
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <ThostFtdcMdApi.h>

class CMduserHandler : public CThostFtdcMdSpi
{
private:
    CThostFtdcMdApi* mdApi;
    const char* brokerID = "9999";
    int nRequestID = 0;
public:
    CMduserHandler(CThostFtdcMdApi* userMdApi);

    ~CMduserHandler();

    void connect();

    void ReqUserLogin();

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    void logout();

    virtual void OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    void subscribe();

    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData);

};