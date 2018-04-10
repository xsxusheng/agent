#include "../proto/CommonDefine.pb.h"
#include "AgentConstantDef.h"
using namespace com::fiberhome::fums::proto;




unordered_map<int, string> AppTypeMap({
        {EnumDefineData::GSLB, "GSLB"},
        {EnumDefineData::SS, "SS"},
        {EnumDefineData::EPG, "EPG"},
        {EnumDefineData::EPG_DB, "EPG_DB"},
        {EnumDefineData::EPG_CACHE, "EPG_CACHE"},
        {EnumDefineData::EPG_WEB, "EPG_WEB"},
        {EnumDefineData::EPG_LB, "EPG_LB"},
        {EnumDefineData::EPG_HA, "EPG_HA"},
        {EnumDefineData::EPG_LOG, "EPG_LOG"},
        {EnumDefineData::EPG_RSYNC, "EPG_RSYNC"},
	/*
        public static final String ACS_WEB = "ACS_WEB";
        public static final String ACS_HA = "ACS_HA";
        public static final String ACS_LB = "ACS_LB";
        public static final String ACS = "ACS";
        public static final String ACS_ALL = "ACS_ALL";

        public static final String AAA = "AAA";
        public static final String AAA_WEB = "AAA_WEB";
        public static final String AAA_HA = "AAA_HA";
        public static final String AAA_LB = "AAA_LB";
        public static final String AAA_ALL = "AAA_ALL";

        public static final String VODLD = "VODLD";
        public static final String TVLD = "TVLD";
        public static final String TVLD_TVLD = "TVLD_TVLD";
        public static final String TVLD_TLCC = "TVLD_TLCC";

        public static final String VCC = "VCC";

        public static final String MW = "MW";
        public static final String MW_MA = "MW_MA";
        public static final String MW_OSS = "MW_OSS";
        public static final String MW_JBOSS = "MW_JBOSS";
        public static final String MW_HA = "MW_HA";
        public static final String DB = "DB";
        public static final String DB_HA = "DB_HA";
        public static final String PC_EPG = "PC-EPG";
        // ADS
        public static final String ADS = "ADS";
        // RRS
        public static final String RRS = "RRS";
        public static final String RRS_HA = "RRS_HA";

        public static final String CMM = "CMM";
        public static final String CMMD2 = "CMMD2";
        public static final String TMS = "TMS";
        public static final String CMS = "CMS";
        public static final String ESS = "ESS";
        public static final String OSS = "OSS";
        public static final String TCMS = "TCMS";
        public static final String TVMS = "TVMS";
        public static final String NGINX = "NGINX";
        public static final String EPG4K = "EPG4K";
        public static final String TVGW = "TVGW";
	*/
        {EnumDefineData::CSD, "CSD"},
        {EnumDefineData::LRS, "LRS"},
        {EnumDefineData::LCM, "LCM"},
        {EnumDefineData::CSP, "CSP"},
        {EnumDefineData::CSV, "CSV"},
        {EnumDefineData::DRS, "DRS"},
        {EnumDefineData::CSX, "CSX"},
        {EnumDefineData::CSJ, "CSJ"},
        {EnumDefineData::AGENT, "AGENT"}
});
/*
// ------------------------GSLB相关
// 统计
string GSLB_STATISTICS_SCRIPT("/opt/fonsview/NE/gslb/bin/sts.sh app");
string GSLB_SERVICE_STATISTICS_SCRIPT("/opt/fonsview/NE/gslb/bin/sts.sh service");

// 控制
string GSLB_START_APP_CTRL_SCRIPT("/opt/fonsview/NE/gslb/bin/start.sh");
string GSLB_HA_START_APP_CTRL_SCRIPT("/opt/fonsview/NE/gslb/bin/start.sh peer");// no
string GSLB_STOP_APP_CTRL_SCRIPT("/opt/fonsview/NE/gslb/bin/stop.sh");
string GSLB_RESTART_APP_CTRL_SCRIPT("/opt/fonsview/NE/gslb/bin/restart.sh");
string GSLB_VIEW_APP_STATUS_STATUS_SCRIPT("/opt/fonsview/NE/gslb/bin/status.sh app");
string GSLB_VIEW_DAEMON_STATUS_STATUS_SCRIPT("/opt/fonsview/NE/gslb/bin/status.sh daemon");

// HA相关
string GSLB_HA_CTRL_CTRL_SCRIPT("/opt/fonsview/NE/gslb/bin/ha_switch.sh");
string GSLB_VIEW_HA_STATUS_SCRIPT("/opt/fonsview/NE/gslb/bin/status.sh ha");

// 服务器运行异常
string GSLB_VIEW_STATUS_SCRIPT("/opt/fonsview/NE/gslb/bin/status.sh servers");
string GSLB_VIEW_RUNNING_VERSION_SCRIPT("/opt/fonsview/NE/gslb/bin/version.sh");

// ------------------------SS控制与状态脚本
// 性能统计
string SS_CLUSTER_STATISTICS_SCRIPT("/opt/fonsview/NE/ss/bin/sts.sh cluster");
string SS_NODE_STATISTICS_SCRIPT("/opt/fonsview/NE/ss/bin/sts.sh");
string SS_VCDN_STATISTICS_SCRIPT("/opt/fonsview/NE/ss/bin/vcdn_sp_sts.sh");
string SS_VCDN_PRO_STATISTICS_SCRIPT("/opt/fonsview/NE/ss/bin/vcdn_providerid_sts.sh");

// VCDN配置存放路径
string SS_VCDN_CONFIG_STORAGE_PATH("/opt/fonsview/NE/ss/etc");

// 控制
string SS_START_APP_CTRL_SCRIPT("/opt/fonsview/NE/ss/bin/start.sh");
string SS_STOP_APP_CTRL_SCRIPT("/opt/fonsview/NE/ss/bin/stop.sh");
string SS_RESTART_APP_CTRL_SCRIPT("/opt/fonsview/NE/ss/bin/restart.sh");
string SS_VIEW_APP_STATUS_STATUS_SCRIPT("/opt/fonsview/NE/ss/bin/status.sh app");
string SS_VIEW_DAEMON_STATUS_STATUS_SCRIPT("/opt/fonsview/NE/ss/bin/status.sh daemon");

// HA相关
string SS_HA_CTRL_CTRL_SCRIPT("/opt/fonsview/NE/ss/bin/ha_switch.sh");
string SS_VIEW_HA_STATUS_SCRIPT("/opt/fonsview/NE/ss/bin/status.sh ha");
// 查看运行版本
string SS_VIEW_RUNNING_VERSION_SCRIPT("/opt/fonsview/NE/ss/bin/version.sh");

// 查看配置脚本
string SS_APP_CONF_VIEW_SCRIPT("/opt/fonsview/NE/ss/bin/config_check.sh app");

// ------------------------EPG控制与状态脚本
// app控制
string EPG_START_ALL_SERVICE("/opt/fonsview/NE/epg/bin/start.sh");
string EPG_STOP_ALL_SERVICE("/opt/fonsview/NE/epg/bin/stop.sh");
string EPG_RESTART_ALL_SERVICE("/opt/fonsview/NE/epg/bin/restart.sh");

string EPG_START_DB_SERVICE("/opt/fonsview/NE/epg/bin/start.sh db");
string EPG_STOP_DB_SERVICE("/opt/fonsview/NE/epg/bin/stop.sh db");
string EPG_RESTART_DB_SERVICE("/opt/fonsview/NE/epg/bin/restart.sh db");

string EPG_START_CACHE_SERVICE("/opt/fonsview/NE/epg/bin/start.sh cache");
string EPG_STOP_CACHE_SERVICE("/opt/fonsview/NE/epg/bin/stop.sh cache");
string EPG_RESTART_CACHE_SERVICE("/opt/fonsview/NE/epg/bin/restart.sh cache");

string EPG_START_WEB_SERVICE("/opt/fonsview/NE/epg/bin/start.sh web");
string EPG_STOP_WEB_SERVICE("/opt/fonsview/NE/epg/bin/stop.sh web");
string EPG_RESTART_WEB_SERVICE("/opt/fonsview/NE/epg/bin/restart.sh web");

string EPG_START_LB_SERVICE("/opt/fonsview/NE/epg/bin/start.sh lb");
string EPG_STOP_LB_SERVICE("/opt/fonsview/NE/epg/bin/stop.sh lb");
string EPG_RESTART_LB_SERVICE("/opt/fonsview/NE/epg/bin/restart.sh lb");

string EPG_START_HA_SERVICE("/opt/fonsview/NE/epg/bin/start.sh ha");
string EPG_STOP_HA_SERVICE("/opt/fonsview/NE/epg/bin/stop.sh ha");
string EPG_RESTART_HA_SERVICE("/opt/fonsview/NE/epg/bin/restart.sh ha");

string EPG_START_LOG_SERVICE("/opt/fonsview/NE/epg/bin/start.sh log");
string EPG_STOP_LOG_SERVICE("/opt/fonsview/NE/epg/bin/stop.sh log");
string EPG_RESTART_LOG_SERVICE("/opt/fonsview/NE/epg/bin/restart.sh log");

string EPG_START_RSYNC_SERVICE("/opt/fonsview/NE/epg/bin/start.sh rsync");
string EPG_STOP_RSYNC_SERVICE("/opt/fonsview/NE/epg/bin/stop.sh rsync");
string EPG_RESTART_RSYNC_SERVICE("/opt/fonsview/NE/epg/bin/restart.sh rsync");

// HA相关
string EPG_HA_CTRL_SCRIPT("/opt/fonsview/NE/epg/bin/ha_switch.sh");
string EPG_VIEW_HA_STATUS_SCRIPT("/opt/fonsview/NE/epg/bin/status.sh ha");

string EPG_VIEW_RUNNING_VERSION_SCRIPT("/opt/fonsview/NE/epg/bin/version.sh");
string EPG_VIEW_APP_STATUS_STATUS_SCRIPT("/opt/fonsview/NE/epg/bin/status.sh app");

// EPG服务器运行状态
string EPG_SERVER_RUNNING_STATUS_SCRIPT("/opt/fonsview/NE/epg/bin/status.sh");

// EPG性能统计
string EPG_STATISTICS_SCRIPT("/opt/fonsview/NE/epg/bin/sts.sh");

// --------------------ACS && 机顶盒相关
// 日志路径
string TM_VERSION_PATH("/opt/fonsview/etc/acs/upgrade/");
string TM_PERF_FILE_PATH("/opt/fonsview/etc/acs/upload_log/");
string TM_OPR_LOG_PATH("/opt/fonsview/etc/acs/operation_log/");

// 控制脚本
string ACS_ALL_START("/opt/fonsview/NE/acs/bin/start.sh");
string ACS_START("/opt/fonsview/NE/acs/bin/start.sh acs");
string ACS_START_HA("/opt/fonsview/NE/acs/bin/start.sh ha");
string ACS_START_LB("/opt/fonsview/NE/acs/bin/start.sh lb");

string ACS_ALL_STOP("/opt/fonsview/NE/acs/bin/stop.sh");
string ACS_STOP("/opt/fonsview/NE/acs/bin/stop.sh acs");
string ACS_STOP_LB("/opt/fonsview/NE/acs/bin/stop.sh lb");
string ACS_STOP_HA("/opt/fonsview/NE/acs/bin/stop.sh ha");

string ACS_ALL_RESTART("/opt/fonsview/NE/acs/bin/restart.sh");
string ACS_RESTART("/opt/fonsview/NE/acs/bin/restart.sh acs");
string ACS_RESTART_HA("/opt/fonsview/NE/acs/bin/restart.sh ha");
string ACS_RESTART_LB("/opt/fonsview/NE/acs/bin/restart.sh lb");

string ACS_ALL_STATUS("/opt/fonsview/NE/acs/bin/status.sh");
string ACS_STATUS("/opt/fonsview/NE/acs/bin/status.sh acs");
string ACS_VIEW_HA("/opt/fonsview/NE/acs/bin/status.sh ha");
string ACS_VIEW_LB("/opt/fonsview/NE/acs/bin/status.sh lb");
string ACS_VIEW_HASTATUS("/opt/fonsview/NE/acs/bin/ha_status.sh");

// HA切换
string ACS_SWITCH_HA("/opt/fonsview/NE/acs/bin/ha_switch.sh");

// 服务器状态
string VIEW_ACS_SERVER_STATUS("/opt/fonsview/NE/acs/bin/xml_status.perl");

// 查看版本
string VIEW_APP_ACS_VERSION_SCRIPT("/opt/fonsview/NE/acs/bin/version.sh");

// --------------------AAA相关
// 控制
string AAA_START("/opt/fonsview/NE/aaa/bin/start.sh");
string AAA_STOP("/opt/fonsview/NE/aaa/bin/stop.sh");
string AAA_RESTART("/opt/fonsview/NE/aaa/bin/restart.sh");
string AAA_STATUS("/opt/fonsview/NE/aaa/bin/status.sh");

string AAA_START_WEB("/opt/fonsview/NE/aaa/bin/start.sh tomcat");
string AAA_STOP_WEB("/opt/fonsview/NE/aaa/bin/stop.sh tomcat");
string AAA_RESTART_WEB("/opt/fonsview/NE/aaa/bin/restart.sh tomcat");
string AAA_VIEW_WEB("/opt/fonsview/NE/aaa/bin/status.sh webservice");

string AAA_START_LB("/opt/fonsview/NE/aaa/bin/start.sh lb");
string AAA_STOP_LB("/opt/fonsview/NE/aaa/bin/stop.sh lb");
string AAA_RESTART_LB("/opt/fonsview/NE/aaa/bin/restart.sh lb");
string AAA_VIEW_LB("/opt/fonsview/NE/aaa/bin/status.sh lbservice");

string AAA_START_HA("/opt/fonsview/NE/aaa/bin/start.sh ha");
string AAA_STOP_HA("/opt/fonsview/NE/aaa/bin/stop.sh ha");
string AAA_RESTART_HA("/opt/fonsview/NE/aaa/bin/restart.sh ha");
string AAA_VIEW_HA("/opt/fonsview/NE/aaa/bin/status.sh haservice");
string AAA_HA_SWITCH("/opt/fonsview/NE/aaa/bin/hachange.sh");

// 服务器状态
string VIEW_AAA_SERVER_STATUS("/opt/fonsview/NE/aaa/bin/status.sh");

// 性能
string AAA_STATISTICS_SCRIPT("/opt/fonsview/NE/aaa/bin/sts.sh");

// 版本
string AAA_VERSION_SCRIPT("/opt/fonsview/NE/aaa/bin/version.sh");

// ---------------------VODLD相关
string VODLD_START("/opt/fonsview/NE/vodld/bin/start.sh");
string VODLD_STOP("/opt/fonsview/NE/vodld/bin/stop.sh");
string VODLD_RESTART("/opt/fonsview/NE/vodld/bin/restart.sh");
string VODLD_STATUS("/opt/fonsview/NE/vodld/bin/status.sh");
string VODLD_VERSION_SCRIPT("/opt/fonsview/NE/vodld/bin/version.sh");

// ---------------------TVLD相关
string TLCC_VIEW_HA("/opt/fonsview/NE/tvld/bin/status.sh ha");
string TLCC_HA_SWITCH("/opt/fonsview/NE/tvld/bin/ha_switch.sh"); // 只发给主用

string TVLD_START("/opt/fonsview/NE/tvld/bin/start.sh");
string TVLD_STOP("/opt/fonsview/NE/tvld/bin/stop.sh");
string TVLD_RESTART("/opt/fonsview/NE/tvld/bin/restart.sh");
string TVLD_STATUS("/opt/fonsview/NE/tvld/bin/status.sh");
string TVLD_VERSION_SCRIPT("/opt/fonsview/NE/tvld/bin/version.sh");

string TVLD_TVLD_START("/opt/fonsview/NE/tvld/bin/start.sh tvld");
string TVLD_TVLD_STOP("/opt/fonsview/NE/tvld/bin/stop.sh tvld");
string TVLD_TVLD_RESTART("/opt/fonsview/NE/tvld/bin/restart.sh tvld");
string TVLD_TVLD_STATUS("/opt/fonsview/NE/tvld/bin/status.sh tvld");
string TVLD_TVLD_VERSION_SCRIPT("/opt/fonsview/NE/tvld/bin/version.sh tvld");

string TVLD_TLCC_START("/opt/fonsview/NE/tvld/bin/start.sh tlcc");
string TVLD_TLCC_STOP("/opt/fonsview/NE/tvld/bin/stop.sh tlcc");
string TVLD_TLCC_RESTART("/opt/fonsview/NE/tvld/bin/restart.sh tlcc");
string TVLD_TLCC_STATUS("/opt/fonsview/NE/tvld/bin/status.sh tlcc");
string TVLD_TLCC_VERSION_SCRIPT("/opt/fonsview/NE/tvld/bin/version.sh tlcc");

// NTP status
string NTP_STATUS_YES("yes");
string NTP_STATUS_NO("no");

// ------------------VCC状态与控制脚本
// app控制
string VCC_VIEW_HA("/opt/fonsview/NE/vcc/bin/ha_status.py");
string VCC_HA_SWITCH("/opt/fonsview/NE/vcc/bin/ha_switch.sh");// 只发给主用
string VCC_START("/opt/fonsview/NE/vcc/bin/start.sh");
string VCC_STOP("/opt/fonsview/NE/vcc/bin/stop.sh");
string VCC_RESTART("/opt/fonsview/NE/vcc/bin/restart.sh");
string VCC_STATUS("/opt/fonsview/NE/vcc/bin/status.sh");
// 查看版本
string VCC_VERSION_SCRIPT("/opt/fonsview/NE/vcc/bin/version.sh");
// 服务器状态
string VIEW_VCC_SERVER_STATUS("/opt/fonsview/NE/vcc/bin/status.sh");
// ADS
string ADS_STATUS("service adsd status");
string ADS_START("service adsd start");
string ADS_STOP("service adsd stop");
string ADS_RESTART("service adsd restart");
*/
// -------JBoss状态与mw控制脚本
/*
string JBOSS_STATUS("service jboss status");
string JBOSS_STOP(AgentUtil.getScripPath() + "killjboss");
string JBOSS_START(AgentUtil.getScripPath() + "mw_jboss_start.sh");
string JBOSS_RESTART(AgentUtil.getScripPath() + "mw_jboss_start.sh");
string MW_MA_START("service jboss -s ma-ear.ear");
string MW_MA_STOP(AgentUtil.getScripPath() + "ma_stop.sh");
string MW_OSS_START("service jboss -s oss-ear.ear");
string MW_OSS_STOP(AgentUtil.getScripPath() + "oss_stop.sh");
string MW_MA_RESTART("service jboss -r ma-ear.ear");
string MW_OSS_RESTART("service jboss -r oss-ear.ear");
string MW_START("service jboss -s ma-ear.ear;service jboss -s oss-ear.ear");
string MW_STOP(AgentUtil.getScripPath() + "mw_hot_stop.sh oss-ear.ear ma-ear.ear");
string MW_RESTART("service jboss -r ma-ear.ear;service jboss -r oss-ear.ear");

string MW_HA_STATUS(AgentUtil.getScripPath() + "/ucarp/status.sh ha");
string MW_HASERVICE_STATUS(AgentUtil.getScripPath() + "/ucarp/status.sh haservice");
string MW_HASERVICE_STOP(AgentUtil.getScripPath() + "/ucarp/stop.sh ha");
string MW_HASERVICE_START(AgentUtil.getScripPath() + "/ucarp/start.sh ha");
string MW_HASERVICE_RESTART(AgentUtil.getScripPath() + "/ucarp/restart.sh ha");
*//*
// DB状态
string DB_STATUS(AgentUtil.getScripPath() + "db_status.sh");
string DB_MIRRORHA_STATUS(AgentUtil.getScripPath() + "mirror_status.sh");
string DB_STOP("service mysqld stop");
string DB_START("service mysqld start");
string DB_MIRRORHA_STOP(AgentUtil.getScripPath() + "mirrorha_stop.sh");
string DB_MIRRORHA_START(AgentUtil.getScripPath() + "mirrorha_start.sh");
string DB_RESTART("service mysqld restart");
string DB_MIRRORHA_RESTART(AgentUtil.getScripPath() + "mirrorha_restart.sh");
string DB_VERSION(AgentUtil.getScripPath() + "db_version.sh");
string DB_HA_STATUS(AgentUtil.getScripPath() + "ha_status.sh");

// RRS网元状态与控制脚本
string RRS_STATUS("/opt/fonsview/NE/rrs/bin/status.sh");
string RRS_START("/opt/fonsview/NE/rrs/bin/start.sh");
string RRS_STOP("/opt/fonsview/NE/rrs/bin/stop.sh");
string RRS_RESTART("/opt/fonsview/NE/rrs/bin/restart.sh");
string RRS_VERSION("/opt/fonsview/NE/rrs/bin/version.sh");
string RRS_HA_SWITCH("/opt/fonsview/NE/rrs/bin/ha_switch.sh");
string RRS_HA_STATUS("/opt/fonsview/NE/rrs/bin/ha_status.sh");
string RRS_VIEW_SERVICE_STATUS("/opt/fonsview/NE/rrs/bin/status.sh");
// RRS统计
string RRS_STATISTICS_SCRIPT("/opt/fonsview/NE/rrs/bin/rrs_sts.sh");

// CMM网元状态与控制脚本
string CMM_STATUS("/opt/fonsview/NE/cmm/bin/status.sh");
string CMM_START("/opt/fonsview/NE/cmm/bin/start.sh");
string CMM_STOP("/opt/fonsview/NE/cmm/bin/stop.sh");
string CMM_VERSION("/opt/fonsview/NE/cmm/bin/version.sh");
string CMM_RESTART("/opt/fonsview/NE/cmm/bin/restart.sh");
// CMMD2网元状态与控制脚本
string CMMD2_STATUS("/opt/fonsview/NE/cmmd2/bin/status.sh");
string CMMD2_START("/opt/fonsview/NE/cmmd2/bin/start.sh");
string CMMD2_STOP("/opt/fonsview/NE/cmmd2/bin/stop.sh");
string CMMD2_VERSION("/opt/fonsview/NE/cmmd2/bin/version.sh");
string CMMD2_RESTART("/opt/fonsview/NE/cmmd2/bin/restart.sh");

// TMS网元状态与控制脚本
string TMS_STATUS("/opt/fonsview/NE/tms/bin/status.sh");
string TMS_START("/opt/fonsview/NE/tms/bin/start.sh");
string TMS_STOP("/opt/fonsview/NE/tms/bin/stop.sh");
string TMS_VERSION("/opt/fonsview/NE/tms/bin/version.sh");
string TMS_RESTART("/opt/fonsview/NE/tms/bin/restart.sh");

// CMS网元状态与控制脚本
string CMS_STATUS("/opt/fonsview/NE/cms/bin/status.sh");
string CMS_START("/opt/fonsview/NE/cms/bin/start.sh");
string CMS_STOP("/opt/fonsview/NE/cms/bin/stop.sh");
string CMS_VERSION("/opt/fonsview/NE/cms/bin/version.sh");
string CMS_RESTART("/opt/fonsview/NE/cms/bin/restart.sh");

// ESS网元状态与控制脚本
string ESS_STATUS("/opt/fonsview/NE/ess/bin/status.sh");
string ESS_START("/opt/fonsview/NE/ess/bin/start.sh");
string ESS_STOP("/opt/fonsview/NE/ess/bin/stop.sh");
string ESS_VERSION("/opt/fonsview/NE/ess/bin/version.sh");
string ESS_RESTART("/opt/fonsview/NE/ess/bin/restart.sh");

// OSS网元状态与控制脚本
string OSS_STATUS("/opt/fonsview/NE/oss/bin/status.sh");
string OSS_START("/opt/fonsview/NE/oss/bin/start.sh");
string OSS_STOP("/opt/fonsview/NE/oss/bin/stop.sh");
string OSS_VERSION("/opt/fonsview/NE/oss/bin/version.sh");
string OSS_RESTART("/opt/fonsview/NE/oss/bin/restart.sh");

// TCMS网元状态与控制脚本
string TCMS_STATUS("/opt/fonsview/NE/tcms/bin/status.sh");
string TCMS_START("/opt/fonsview/NE/tcms/bin/start.sh");
string TCMS_STOP("/opt/fonsview/NE/tcms/bin/stop.sh");
string TCMS_VERSION("/opt/fonsview/NE/tcms/bin/version.sh");
string TCMS_RESTART("/opt/fonsview/NE/tcms/bin/restart.sh");

// TVMS网元状态与控制脚本
string TVMS_STATUS("/opt/fonsview/NE/tvms/bin/status.sh");
string TVMS_START("/opt/fonsview/NE/tvms/bin/start.sh");
string TVMS_STOP("/opt/fonsview/NE/tvms/bin/stop.sh");
string TVMS_VERSION("/opt/fonsview/NE/tvms/bin/version.sh");
string TVMS_RESTART("/opt/fonsview/NE/tvms/bin/restart.sh");

// NGINX网元状态与控制脚本
string NGINX_STATUS("/opt/fonsview/NE/nginx/bin/status.sh");
string NGINX_START("/opt/fonsview/NE/nginx/bin/start.sh");
string NGINX_STOP("/opt/fonsview/NE/nginx/bin/stop.sh");
string NGINX_VERSION("/opt/fonsview/NE/nginx/bin/version.sh");
string NGINX_RESTART("/opt/fonsview/NE/nginx/bin/restart.sh");

// EPG4K网元状态与控制脚本
string EPG4K_STATUS("/opt/fonsview/NE/epg4k/bin/status.sh");
string EPG4K_START("/opt/fonsview/NE/epg4k/bin/start.sh");
string EPG4K_STOP("/opt/fonsview/NE/epg4k/bin/stop.sh");
string EPG4K_VERSION("/opt/fonsview/NE/epg4k/bin/version.sh");
string EPG4K_RESTART("/opt/fonsview/NE/epg4k/bin/restart.sh");

// TVGW网元状态与控制脚本
string TVGW_STATUS("/opt/fonsview/NE/tvgw/bin/status.sh");
string TVGW_START("/opt/fonsview/NE/tvgw/bin/start.sh");
string TVGW_STOP("/opt/fonsview/NE/tvgw/bin/stop.sh");
string TVGW_VERSION("/opt/fonsview/NE/tvgw/bin/version.sh");
string TVGW_RESTART("/opt/fonsview/NE/tvgw/bin/restart.sh");
*/
    // CSD网元状态与控制脚本
string CSD_STATUS("/opt/fonsview/NE/csd/bin/status.sh");
string CSD_START("/opt/fonsview/NE/csd/bin/start.sh");
string CSD_STOP("/opt/fonsview/NE/csd/bin/stop.sh");
string CSD_VERSION("/opt/fonsview/NE/csd/bin/version.sh");
string CSD_RESTART("/opt/fonsview/NE/csd/bin/restart.sh");

// LRS网元状态与控制脚本
string LRS_STATUS("/opt/fonsview/NE/lrs/bin/status.sh");
string LRS_START("/opt/fonsview/NE/lrs/bin/start.sh");
string LRS_STOP("/opt/fonsview/NE/lrs/bin/stop.sh");
string LRS_VERSION("/opt/fonsview/NE/lrs/bin/version.sh");
string LRS_RESTART("/opt/fonsview/NE/lrs/bin/restart.sh");

// LCM网元状态与控制脚本
string LCM_STATUS("/opt/fonsview/NE/lcm/bin/status.sh");
string LCM_START("/opt/fonsview/NE/lcm/bin/start.sh");
string LCM_STOP("/opt/fonsview/NE/lcm/bin/stop.sh");
string LCM_VERSION("/opt/fonsview/NE/lcm/bin/version.sh");
string LCM_RESTART("/opt/fonsview/NE/lcm/bin/restart.sh");

// CSP网元状态与控制脚本
string CSP_STATUS("/opt/fonsview/NE/csp/bin/status.sh");
string CSP_START("/opt/fonsview/NE/csp/bin/start.sh");
string CSP_STOP("/opt/fonsview/NE/csp/bin/stop.sh");
string CSP_VERSION("/opt/fonsview/NE/csp/bin/version.sh");
string CSP_RESTART("/opt/fonsview/NE/csp/bin/restart.sh");

// CSV网元状态与控制脚本
string CSV_STATUS("/opt/fonsview/NE/csv/bin/status.sh");
string CSV_START("/opt/fonsview/NE/csv/bin/start.sh");
string CSV_STOP("/opt/fonsview/NE/csv/bin/stop.sh");
string CSV_VERSION("/opt/fonsview/NE/csv/bin/version.sh");
string CSV_RESTART("/opt/fonsview/NE/csv/bin/restart.sh");

// DRS网元状态与控制脚本
string DRS_STATUS("/opt/fonsview/NE/drs/bin/status.sh");
string DRS_START("/opt/fonsview/NE/drs/bin/start.sh");
string DRS_STOP("/opt/fonsview/NE/drs/bin/stop.sh");
string DRS_VERSION("/opt/fonsview/NE/drs/bin/version.sh");
string DRS_RESTART("/opt/fonsview/NE/drs/bin/restart.sh");

// CSX网元状态与控制脚本
string CSX_STATUS("/opt/fonsview/NE/csx/bin/status.sh");
string CSX_START("/opt/fonsview/NE/csx/bin/start.sh");
string CSX_STOP("/opt/fonsview/NE/csx/bin/stop.sh");
string CSX_VERSION("/opt/fonsview/NE/csx/bin/version.sh");
string CSX_RESTART("/opt/fonsview/NE/csx/bin/restart.sh");

// CSJ网元状态与控制脚本
string CSJ_STATUS("/opt/fonsview/NE/csj/bin/status.sh");
string CSJ_START("/opt/fonsview/NE/csj/bin/start.sh");
string CSJ_STOP("/opt/fonsview/NE/csj/bin/stop.sh");
string CSJ_VERSION("/opt/fonsview/NE/csj/bin/version.sh");
string CSJ_RESTART("/opt/fonsview/NE/csj/bin/restart.sh");

// epg4k统计tcp链接数脚本
string EPG4K_STATISTICS_SCRIPT("/opt/fonsview/NE/agent/tcpconnectnum.sh");
// epg4k统计实时并发数脚本
string EPG4K_CONCURRENT_NUM_SCRIPT("/opt/fonsview/NE/agent/lvs_conn_num.sh");
// dns重定向请求数获取脚本
string DNS_REDIRECT_REQUEST_SCRIPT_FILE("/opt/fonsview/NE/drs/proc/dns_statis");
string DNS_REDIRECT_REQUEST_SCRIPT("/opt/fonsview/NE/agent/script/ucarp/dns_redirect_request.sh");


unordered_map<string, string> AgentConstantDef::S_START_SCRIPTS_MAP({
        {AppTypeMap[EnumDefineData::CSD], CSD_START},
        {AppTypeMap[EnumDefineData::LRS], LRS_START},
        {AppTypeMap[EnumDefineData::LCM], LCM_START},
        {AppTypeMap[EnumDefineData::CSP], CSP_START},
        {AppTypeMap[EnumDefineData::CSV], CSV_START},
        {AppTypeMap[EnumDefineData::DRS], DRS_START},
        {AppTypeMap[EnumDefineData::CSX], CSX_START},
        {AppTypeMap[EnumDefineData::CSJ], CSJ_START},
});

string AgentConstantDef::GetStartScript(const string &appType)
{
	return S_START_SCRIPTS_MAP[appType];
}


unordered_map<string, string> AgentConstantDef::S_STOP_SCRIPTS_MAP({
        {AppTypeMap[EnumDefineData::CSD], CSD_STOP},
        {AppTypeMap[EnumDefineData::LRS], LRS_STOP},
        {AppTypeMap[EnumDefineData::LCM], LCM_STOP},
        {AppTypeMap[EnumDefineData::CSP], CSP_STOP},
        {AppTypeMap[EnumDefineData::CSV], CSV_STOP},
        {AppTypeMap[EnumDefineData::DRS], DRS_STOP},
        {AppTypeMap[EnumDefineData::CSX], CSX_STOP},
        {AppTypeMap[EnumDefineData::CSJ], CSJ_STOP},
{"",""}
});
string AgentConstantDef::GetStopScript(const string &appType)
{
	return S_STOP_SCRIPTS_MAP[appType];
}

unordered_map<string, string> AgentConstantDef::S_RESTART_SCRIPTS_MAP({
        {AppTypeMap[EnumDefineData::CSD], CSD_RESTART},
        {AppTypeMap[EnumDefineData::LRS], LRS_RESTART},
        {AppTypeMap[EnumDefineData::LCM], LCM_RESTART},
        {AppTypeMap[EnumDefineData::CSP], CSP_RESTART},
        {AppTypeMap[EnumDefineData::CSV], CSV_RESTART},
        {AppTypeMap[EnumDefineData::DRS], DRS_RESTART},
        {AppTypeMap[EnumDefineData::CSX], CSX_RESTART},
        {AppTypeMap[EnumDefineData::CSJ], CSJ_RESTART},
{"",""}
});
string AgentConstantDef::GetRestartScript(const string &appType)
{
	return S_RESTART_SCRIPTS_MAP[appType];
}

unordered_map<string, string> AgentConstantDef::S_VIEW_STATUS_SCRIPTS_MAP({
        {AppTypeMap[EnumDefineData::CSD], CSD_STATUS},
        {AppTypeMap[EnumDefineData::LRS], LRS_STATUS},
        {AppTypeMap[EnumDefineData::LCM], LCM_STATUS},
        {AppTypeMap[EnumDefineData::CSP], CSP_STATUS},
        {AppTypeMap[EnumDefineData::CSV], CSV_STATUS},
        {AppTypeMap[EnumDefineData::DRS], DRS_STATUS},
        {AppTypeMap[EnumDefineData::CSX], CSX_STATUS},
        {AppTypeMap[EnumDefineData::CSJ], CSJ_STATUS},
});

string AgentConstantDef::GetViewStatusScript(const string &appType)
{
	return S_VIEW_STATUS_SCRIPTS_MAP[appType];
}

unordered_map<string, string> AgentConstantDef::S_VIEW_DAEMON_STATUS_SCRIPTS_MAP({
{"",""}
});
string AgentConstantDef::GetViewDaemonStatusScript(const string &appType)
{
	return S_VIEW_DAEMON_STATUS_SCRIPTS_MAP[appType];
}
unordered_map<string, string> AgentConstantDef::S_VIEW_VERSION_SCRIPTS_MAP({
        {AppTypeMap[EnumDefineData::CSD], CSD_VERSION},
        {AppTypeMap[EnumDefineData::LRS], LRS_VERSION},
        {AppTypeMap[EnumDefineData::LCM], LCM_VERSION},
        {AppTypeMap[EnumDefineData::CSP], CSP_VERSION},
        {AppTypeMap[EnumDefineData::CSV], CSV_VERSION},
        {AppTypeMap[EnumDefineData::DRS], DRS_VERSION},
        {AppTypeMap[EnumDefineData::CSX], CSX_VERSION},
        {AppTypeMap[EnumDefineData::CSJ], CSJ_VERSION},
});
string AgentConstantDef::GetViewRunningVersionScript(const string &appType)
{
	return S_VIEW_VERSION_SCRIPTS_MAP[appType];
}

unordered_map<string, string> AgentConstantDef::S_HA_START_SCRIPTS_MAP({
{"",""}
});
string AgentConstantDef::GetHaStartScript(const string &appType)
{
	return S_HA_START_SCRIPTS_MAP[appType];
}

unordered_map<string, string> AgentConstantDef::S_HA_RESTART_SCRIPTS_MAP({
{"",""}
});
string AgentConstantDef::GetHaRestartScript(const string &appType)
{
	return S_HA_RESTART_SCRIPTS_MAP[appType];
}

unordered_map<string, string> AgentConstantDef::S_SWITCH_HA_SCRIPTS_MAP({
{"",""}
});
string AgentConstantDef::GetSwitchHaScript(const string &appType)
{
	return S_SWITCH_HA_SCRIPTS_MAP[appType];
}

unordered_map<string, string> AgentConstantDef::S_SERVER_STATUS_SCRIPTS_MAP({
{"",""}
});
string AgentConstantDef::GetServerStatusScript(const string &appType)
{
	return S_SERVER_STATUS_SCRIPTS_MAP[appType];
}

