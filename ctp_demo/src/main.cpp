// cpt_demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include "CMduserHandler.h"
#include "trader_handler.h"
#include "trader_spi.h"
#include <stdio.h>

using namespace std;

//04:00 -- 21 : 00 next day 7 * 24 test environment
//const char* marketFront = "tcp://180.168.146.187:10131";
//const char* tradeFront = "tcp://180.168.146.187:10130";

// Mon - Fri
const char* marketFront = "tcp://180.168.146.187:10211";
const char* tradeFront = "tcp://180.168.146.187:10201";

int main()
{
    CThostFtdcMdApi* pUserMdApi = CThostFtdcMdApi::CreateFtdcMdApi(".\\flow\\", false, false);
    CMduserHandler mdApi(pUserMdApi);

    CThostFtdcTraderApi* pTradeApi = CThostFtdcTraderApi::CreateFtdcTraderApi(".\\flow\\");
    TraderHandler tdHandler(pTradeApi);
    TraderSpi* pTdspi = new TraderSpi();

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
                cin.clear();
                cin.ignore(10000, '\n');
                pUserMdApi->RegisterSpi(&mdApi);
                pUserMdApi->RegisterFront(const_cast<char*> (marketFront));
                pUserMdApi->Init();
                Sleep(1500);
                //mdApi.connect();
                mdApi.Login();
                Sleep(1000);
                mdApi.Subscribe();
                Sleep(1500);
                mdApi.Logout();
                Sleep(1000);
                pUserMdApi->Release();
                printf("----------------- End -----------------\n \n");
                break;
            }
            case 2:
            {
                cin.clear();
                cin.ignore(10000, '\n');
                tdHandler.Connect(const_cast<char*>(tradeFront), pTdspi);
                Sleep(1000);
                int op;
                tdHandler.ReqUserLogin();
                Sleep(1500);
                tdHandler.ReqQryInstrument();
                Sleep(1000);
                tdHandler.ReqSettlementInfoConfirm();
                Sleep(1000);

                while (true)
                {
                    printf("Request Placing order ÏÂµ¥: 201\n");
                    printf("Request Withdraw order ³·µ¥: 202\n");
                    cin >> op;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    switch (op)
                    {
                        case 201:
                        {
                            tdHandler.ReqOrderInsert();
                            Sleep(1200);
                            printf("----------------- End -----------------\n \n");
                            break;
                        }
                        case 202:
                        {
                            tdHandler.ReqOrderAction(pTdspi->getOrderSysID());
                            Sleep(1200);
                            printf("----------------- End -----------------\n \n");
                            break;
                        }
                        default:
                        {
                            return 0;
                        }
                    }
                }
                break;
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

