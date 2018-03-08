/*************************************************************************
	> File Name: rabbitmqConfig.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月09日 星期五 15时16分14秒
 ************************************************************************/

#include <string>
#include "../utils/Properties.h"

using namespace std;

class RabbitmqConfig
{
public:
    RabbitmqConfig();
    ~RabbitmqConfig();
    static int Init();
    static string GetHost();
    static string GetVnmhost();
    static string GetUserName();
    static string GetPassword();
    static int    GetPort();
    static string GetExchangeNmr();
    static string GetExchangeNms();
    static string GetCommQueue();
    static string GetHeartQueue();
    static string GetAlarmQueue();
    static string GetPerfQueue();
    static string GetCommRoutingKey();
    static string GetHeartRoutingKey();
    static string GetAlarmRoutingKey();
    static string GetPerfRoutingKey();
    
private:
    static Properties *sm_props; 
};
