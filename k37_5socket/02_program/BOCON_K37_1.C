
/***************************************************************************
*串口2和串口7不设置污染物,且仪表型号设置为10000,串口做为modbus从站输出数据
*串口8的地址参数设置为100可开启累积流量显示,设置为其他关闭显示,不上传累积流量编码
*串口8的地址参数设置为200可开启累积流量显示,设置为其他关闭显示,上传累积流量编码B11
*串口8的地址参数设置为201可开启累积流量显示,设置为其他关闭显示,上传累积流量编码B21
*串口8的地址参数设置为202可开启累积流量显示,设置为其他关闭显示,上传累积流量编码B00
*串口读modbus流量计,累积流量与瞬时流量的偏移位置可在串口8的起始寄存器设置
*设备号设置为96,屏蔽服务器下发命令的错误响应
*设备号设置为97,服务器1下发的数据包通过服务器5输出
*设备号设置为98,串口1启动输出服务器下发的数据包功能
*设备号设置为99,平台反控命令数据包不需要添加回车换行
*设置设备号为100,可将模拟量读取的值从湿基值转化为干基值输出
*设备号设置为101,8011仪表折算开启氧含量限制,超过设置的氧含量上限值,不进行折算
*设备号设置为102,8011仪表折算开启氧含量限制,超过设置的氧含量上限值,折算值等于实测值
*系统设置->采集器参数设置->设置标志 1"F",2"M",3"S",4"C",5"B",关闭设置恢复默认"D""T""N"三种状态设置为0
*
*(污染物反控作样输出,串口8上限作为周期时间判断,串口8报警下限作为界限值判断,串口8地址为污染物的索引值
*污染物反控输出地址为设置仪表串口的地址功能码为串口8的数据排序,串口8的起始寄存器跟数量分别为反控的的寄存器值和写入的值)
*(非modbus的反控作样需另添加仪表)(默认不启动该功能)
*
*(污染物控制继电器)(默认不启动该功能)
*
*(串口作为modbustcp服务端响应输出数据)(默认不启动该功能)
*
*(串口输出8014国标数据包)(默认不启动该功能)
*
******************************************************************************/


#class auto
#memmap xmem

#if 0
COMPILE_SECONDARY_PROG //编译升级文件宏
#endif

#define SW_VERSION   "BOCON_V41_180627_1"//软件版本号
#define SOCKET_NUMBER		5//服务器个数
#define COLECTWATSEC		5//间隔多长时间采集一次数据,单位s
#define BOCON_UDP0_TCP1         1//1TCP,0DUP
#define TCPGPRSBUF		1036//TCP收发数据的缓冲区大小
#define TCPTIMEOUT		300//TCP的超时连接
#define PROTO_ACK_FLAG		0//HJ/T 212协议是否需要应答的标志，0、1、3
#define PROTO_ACK_9011		1//是否发送9011请求应答的开关
#define PROTO_ACK_9012		1//是否发送9012操作执行结果应答的开关
#define MODBUS_TCP_SERVER	0//开启modbusTcp服务器
#define YANCHEN_KELIWU_BMP	1//1烟尘0颗粒物
#define FEIQI_BIAOKUANG_BMP	1//1废气0标况流量
/*****************************************/
//可通过宏开启的仪表型号,因程序太大这些仪表为屏蔽状态
//开启后可能会造成程序太大,需屏蔽另外一些仪表型号
//1开启0关闭,可全部关闭
#define DEV_10001_10010			0
#define DEV_1010_1011_1012 		0
#define DEV_1018_1021_1022 		0
#define DEV_10321_10322			0
#define DEV_1043_1044 			0
#define DEV_1023_1033			0
#define DEV_1998_1999 			0
#define DEV_2011_2012 			0
#define DEV_2111_2112_2113_2114_2115 	0
#define DEV_2017_2018_2019 		0
#define DEV_2020_20221			0
#define DEV_3001_3005 			0
#define DEV_4001_4002_4004_4005 	0
#define DEV_4007_4008_4017 		0
#define DEV_5001                	0
#define DEV_6001_6008 			0
#define DEV_6008_6016 			0
#define DEV_7017_8009_8016		0
#define DEV_8024_8025			0
#define DEV_8056_8156_8070		0
/*****************************************/


#define FENSHAOLU	          	0//焚烧炉相关程序需打开，与其他宏不冲突
//以下宏同时只能开启1个
#define XIAMENYUANSHENGTAI        	0//厦门源生态
#define DALIANHAOHAISHUI          	0//大连浩海水处理
#define JAINGXIYIZHENG	          	0//江西怡正,添加污染物,仪表9999,10322
#define JIANGXIJIAHAOYONGSHENG		0//江西嘉豪永盛环保科技,同江西怡正,添加仪表9998
#define WUXIHUANTONG	          	0//无锡环通,仪表1037,仪表10322
#define NANJINGHONGKAI	          	0//南京鸿凯,添加编码98
#define SUZHOUWEISHUI	          	0//苏州卫水
#define HUIZHOULVKE_MODBUSTCP     	0//惠州绿科——modbusTCP，com1输出
#define ZHAOQINGLVTUO             	0//肇庆绿拓环保客户,添加S09热态流量,添加仪表
#define JIAOTONGWUZI              	0//焚烧炉程序，交彤物资
#define HANGZHOUHAICHI            	0//杭州海驰
#define HAERBINGWEIER	          	0//哈尔滨维尔,串口输出国标数据包
#define GUIZHOUCHENGDA			0//贵州成达,添加驱动
#define XIJIANGHUANBAO			0//西江环保,添加驱动
#define SUZHOUCHENSHUO			0//苏州宸硕,反控作样
#define JIANGXIBOYUAN			0//江西博远,添加卫水服务器
#define KAIMINGKEJI			0//凯铭科技,添加驱动,修改单位
#define XIAMENLIANAOMEIYE		0//厦门联奥美业,添加驱动,多个仪表接485
#define HUNANTUOAN			0//湖南省拓安,读VOC1和VOC2,不上传
#define JUGUANGKEJI			0//聚光科技,添加驱动
#define CHENGDUXINYITENG		0//成都鑫翼腾,添加驱动
#define SICHUANHONGMEI			0//四川弘美,服务器5把烟尘编码改成039
#define SHIYONGWUJIN			0//适用五金
#define HEBEIBAIJIN			0//河北白晶,取消断线自动补发
#define GUANGZHOUXINHUAN		0//广州新环阳江分公司，统一k37的版本
#define GUANGZHOUXINHUANHEYUAN	        0//广州新环河源，传河源市，平台协议不同
#define CHANGSHAHUASHIJIE		0//长沙华时捷	,焚烧炉程序
#define GUANGDONGTIANRUI		0//广东天瑞,9999仪表两个流量计累加
#define XICHANGSANFENG			0//西昌三峰，S06 代表当前标志位状态
#define HAERBINGJIEYUAN			0//哈尔滨洁源，添加科盛留样器
#define NANJINGHONGLI			0//南京弘礼，添加流量计，反控协议
#define GUANGZHOUSHIJING		0//广州世锦，添加驱动
#define GUANGZHOUBIYUAN			0//广州碧源
#define QINGDAOLUBO			    1//青岛路博，添加编码


#if(HUIZHOULVKE_MODBUSTCP == 1)
#define SET_POINT_NUM   	2//设置显示小数点位数,以及上传服务器小数点位数,设置范围1-3(服务器上传的小数点暂不修改)
#else
#define SET_POINT_NUM   	4//设置显示小数点位数,以及上传服务器小数点位数,设置范围1-3(服务器上传的小数点暂不修改)
#endif


#define ENABLE 		1
#define DISABLE  	0

#define COM_1		0
#define COM_2    	1
#define COM_3    	2
#define COM_4    	3
#define COM_5    	4
#define COM_6    	5
#define COM_7    	6

#define SOCKET_1      	0
#define SOCKET_2      	1
#define SOCKET_3      	2
#define SOCKET_4      	3
#define SOCKET_5      	4

#define K37PUTNAME		glXPutBitmap ( 53,  0, 206, 16, BoconBocon_bmp);
#define K37MAINMENU		glXPutBitmap ( 86, 45, 148, 29, BoconK37MainMenu_bmp);


//#use "modbusProtocol_5socket.lib"
#use "ModbusSetMenu.lib"
#use "BOCON_K37_HISTORY_5socket.LIB"
#use "bocon_k37_config_5socket.lib"
#use "bocon_k37_no_config.elib"
#use "BOCON_K37_NET_5socket.LIB"
#use "bocon_k37_tcp_5socket.lib"
#use "BOCON_K37_SMP_5socket.LIB"
#use "BOCON_K37_SMP_SUM_5socket.LIB"
#use "BOCON_RECORD_5socket_v7.LIB"
#use "BOCON_K37_MENU_5socket.LIB"
#use "bocon_k37_hjt212_5socket.lib"
#use "BOCON_K37_DEVICE_5socket.LIB"
#use "bocon_reboot_5socket.lib"


char hjt212_state[SOCKET_NUMBER];               //通信链路的状态
						//0-未联机
						//1-联机未登陆
						//2已登陆

/*******************************************************************************
重新设置系统时钟之前先调用本函数，调整相关定时器和指针
flag		1-时间调大，不需要更新NandFlash写指针
    0-时间调小，需要往回调整NandFlash写指针
*******************************************************************************/
void update_rtc(char flag)
{
    auto char c;

    reboot_task();
    tm_ts = SEC_TIMER;                   //menu超时的定时器
    sampleSEC = SEC_TIMER;               //调整采样定时器
    samplemsgSEC = SEC_TIMER;            //调整保存定时器

    for (c = 0; c < SOCKET_NUMBER; c++)
    {
	tm_out[c] = SEC_TIMER;          //更新网络连接定时器
	heartBeat[c] = SEC_TIMER;       //更新网络心跳定时器
	reqTimeout[c] = SEC_TIMER;
	sec_alarm[c] = SEC_TIMER;
	sec_rt_data[c] = SEC_TIMER;
	sec_rt_dev[c] = SEC_TIMER;
	sec_temp_info[c] = SEC_TIMER;
    }

    if (flag == 0)
    { //将时间改小
	update_nf_ptr();    //调整Flash写指针
    }
}


void save_before_reset(void)
{
//	glPrintf(261, 216, &fi6x8, "%.2f", batVolt);	//Debug
//   msDelay(2000);
}

void prtRxData(char no)
{
    auto int i;
    printf("%s%dRx: ", RED, no);
    for (i = 0; i < tcp_rlen[no]; i++)
    {
	printf("%c", deal_buf[i]);
    }
    printf("%s\n", BLACK);
}

/*******************************************************************************
解析收到的服务器数据包，提取服务器命令
解析结果在err_flag里：	5-包头错
    4-包长度错
    3-CRC错
    2-MN号码错
    1-访问密码错
    0-正确解析
*******************************************************************************/
void parse_cmd(char no)
{
#if (MODBUS_TCP_SERVER == 1)
    if (no == 2)
    {
	modbus_tcp_tasks(no);
	return;
    }
#endif
    parsePackage(no);            //解析收到的数据包
				 //DBG(prtRxData(no);
    if (err_flag[no] < 4)
    {
	parseCmd(no);           //命令预处理，调试时接受4以下的值，正常应只接受0或1
    }
    else                         //也许错误包不应响应
    {
	ack_flag[no] = 0;
	if (devNo != 96)
	{
	    packReqAck(no, getFlag(no));  //收到错误包，响应给服务器
	}
    }
}

void chk_hjt212_state(char no)
{
    if (TCP_OK[no] == 0)             //未联机
    {
	hjt212_state[no] = 0;
    }
    else if (hjt212_state[no] == 2) //已联机，已登陆，正常通信状态
    {
	if (tcp_tlen[no] == 0)
	{
	    chk_hjt212_cmd(no);
	}
    }
    else if (hjt212_state[no] == 1) //已联机，已初始化，未登陆
    {
	if (login[no] == 1) hjt212_state[no] = 2;    //刚登陆成功，置标志
	else                              //还未登陆
	{
	    //hjt212_state[no] ++;	//是否自动更新此标志，无需等服务器响应?
	    if (strcmp(dialName, "LOGIN") == 0)
	    {
		if (SEC_TIMER >= (sec_rt_data[no] + rtdInterval[no]))
		{
		    sec_rt_data[no] = SEC_TIMER; //以实时数据上报的周期发送登陆请求
		    txLogReq(no, 1);        //1-8011，2-9021
		}
		else if (ack_flag[no] == 80) //检查是否收到应答
		{
		    exeCmd(no);             //等待服务器响应登陆请求
		}
	    }
	    else
	    {
		hjt212_state[no]++;
		login[no]++;               //不需要登陆
	    }
	}
    }
    else if (hjt212_state[no] == 0) //已联机，未初始化变量
    {
	if (strcmp(dialName, "LOGIN") == 0)
	{
	    hjt212_init(no, 0, 3);      //初始化为未登陆，需要发送登陆请求
	}
	else
	{
	    hjt212_init(no, 1, 3);      //参数2：0-未登陆，1-已登陆
					//参数3：0-不上传，1-自动上传实时数据，
					//			2-自动上传设备状态，3-都自动上传
	}
	hjt212_state[no]++;
    }
}

void k37_hjt212_task(void)
{
    static char no;

    costate
    {
	while (1)
	{
	    for (no = 0; no < SOCKET_NUMBER; no++)
	    {
#if (MODBUS_TCP_SERVER == 1)
		if (no == 2)
		{
		    continue;
		}
#endif
		chk_hjt212_state(no);
		waitfor(DelayMs(100));
	    }
	}
    }
}

//主函数
void main(void)
{
    k37Init();        //初始化底层硬件驱动
    k37_hmi_init();   //初始化人机接口
    initTcpVar();     //初始化网络接口
    polCodeInit();    //初始化编码表和编码索引
    nf_operate_init(); //初始化Nand Flash存储系统
    smp_init();
    initDevice();
    init_reboot();
    restoreSysParam();
    while (1)
    {
	k37Run();
	k37_key_disp_task();
	k37_sample_task();
	k37_hjt212_task();
#if (BOCON_UDP0_TCP1 == 0)
	bocon_udp_task();
#else
	bocon_tcp_task();
#endif
	reboot_task();

#if (ZHAOQINGLVTUO == 1)
            b01_smp_ctrl_task_zhaoqing();
#endif

#if (GUANGDONGTIANRUI == 1)
if (Savech[8].polIndex >= BOCON_NO_OF_POL  && ai_param[8].model == 1001)
	    get_flux_jiubo(0);
#endif


#if(XICHANGSANFENG == 1)
	disp_flag_S06();	//S06的值作为flag值
#else
	disp_flag_status_task();
#endif

	if (Savech[9].polIndex >= BOCON_NO_OF_POL && ai_param[9].model == 10000) modbusRS485Task(1);
	if (Savech[14].polIndex >= BOCON_NO_OF_POL && ai_param[14].model == 10000) modbusRS485Task(6);
#if(NANJINGHONGLI == 1)
	b01_smp_ctrl_task();
#endif
//	polcode_ctrl_realy_task();
//	com_modbus_slave_task(COM_1);
//	tcp_modbus_slave_task(COM_1);
//	com_8014_pack_task(COM_2);


#if (HAERBINGWEIER == 1)
	if (Savech[9].polIndex >= BOCON_NO_OF_POL && ai_param[9].model == 20000) com_8014_pack_task(COM_2);
#endif

#if(HUIZHOULVKE_MODBUSTCP == 1)
	modbusTcpRS232_task();
#endif



    }
}


