// cpt_demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <CMduserHandler.h>
#include <stdio.h>

using namespace std;

const char* marketFront = "tcp://127.0.0.1:41213";
const char* tradeFront = "tcp://127.0.0.1:41205";
HANDLE sign = CreateEvent(NULL, false, false, NULL);

int main()
{   
    while (true)
    {
        cout << "Select Which Mod You Want To Use\n";
        cout << "mod 1: request market\n";
        cout << "mod 2: request trade\n";
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
            //WaitForSingleObject(sign, INFINITE);
            //userMdApi->Join();
            mdApi.ReqUserLogin();
            mdApi.subscribe();
            //mdApi.logout();
            _getch();
            userMdApi->Release();
            exit(-1);
            break;
        }
        case 2:
        {
            cout << "developinting";
            exit(-1);
            break;
        }
        default:
            break;
        }
    }
    return 0;
}

