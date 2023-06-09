// cpt_demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include "CMduserHandler.h"
#include "trader_handler.h"
#include "trader_spi.h"
#include <stdio.h>

using namespace std;

//const char* marketFront = "tcp://180.168.146.187:10131"; 04:00 -- 21:00 next day
//const char* tradeFront = "tcp://180.168.146.187:10130";
const char* marketFront = "tcp://180.168.146.187:10211";
const char* tradeFront = "tcp://180.168.146.187:10201";

int main()
{   
    while (true)
    {
        printf("Select Which Mod You Want To Use\n");
        printf("mod 1: request market\n");
        printf("mod 2: request trade\n");
        int mod;
        cin >> mod;
        switch (mod)
        {
        case 1:
        {
            CThostFtdcMdApi* userMdApi = CThostFtdcMdApi::CreateFtdcMdApi(".\\flow\\", false, false);
            CMduserHandler mdApi(userMdApi);
            userMdApi->RegisterSpi(&mdApi);
            userMdApi->RegisterFront(const_cast<char*> (marketFront));
            userMdApi->Init();
            //mdApi.connect();
            Sleep(1000);
            mdApi.Login();
            Sleep(1000);
            mdApi.Subscribe();
            return 0;
        }
        case 2:
        {
            CThostFtdcTraderApi* trade_Api = CThostFtdcTraderApi::CreateFtdcTraderApi(".\\flow\\");
            TraderHandler td_handler(trade_Api);
            TraderSpi* tdSpi = new TraderSpi();
            td_handler.Connect(const_cast<char*>(tradeFront), tdSpi);
            //char broke_id[11], uid[16], pass[41];
            Sleep(1000);
            int indicator;
            td_handler.ReqUserLogin();
            Sleep(1000);

            td_handler.ReqSettlementInfoConfirm();
            Sleep(1000);
            td_handler.ReqQryInstrument();
            Sleep(1000);
            int session_id;
            printf("Please enter session id\n");
            cin >> session_id;
            Sleep(1000);
            td_handler.ReqOrderAction(session_id);
            Sleep(1000);

            //printf("Please login. 1: YES, 0: NO\n");
            //cin >> indicator;
            //if (indicator)
            //{
            //    td_handler.ReqUserLogin();
            //    Sleep(1000);
            //    td_handler.ReqSettlementInfoConfirm();
            //    Sleep(1000);
            //    printf("Press 1: Place orderÏÂµ¥\n");
            //    printf("Press 2: Withdraw order³·µ¥\n");
            //    cin >> mod;
            //    switch (mod)
            //    {
            //    case 1:
            //        td_handler.ReqQryInstrument();
            //        Sleep(2000);
            //        td_handler.ReqOrderInsert();
            //        Sleep(2000);
            //        return 0;
            //        break;
            //    case 2:
            //        //td_handler.ReqAuthenticate();
            //        td_handler.ReqOrderAction();
            //        //return 0;
            //        break;
            //    default:
            //        trade_Api->Release();
            //        return 0;
            //    }
            //}
            //else
            //{
            //    trade_Api->Release();
            //}
        }
        default:
        {
            cout << "Close\n";
            return 0;
        }
        }
    }
    return 0;
}

