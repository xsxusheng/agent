/**************************************************************
 * File: SwapUsage.h
 * Function: SWAP
 *
 *************************************************************/
#pragma once





class CSwapUsage
{
public:
    CSwapUsage();
    ~CSwapUsage();


    unsigned long long GetTotal(){return m_nTotal;}
    unsigned long long GetUsed(){return m_nUsed;}
    unsigned long long GetFree(){return m_nFree;}
    unsigned long long GetPageIn(){return m_nPageIn;}
    unsigned long long GetPageOut(){return m_nPageOut;}

    int GetSwapUsage();

protected:


private:
    unsigned long long m_nTotal;
    unsigned long long m_nUsed;
    unsigned long long m_nFree;
    unsigned long long m_nPageIn;
    unsigned long long m_nPageOut;


};




















