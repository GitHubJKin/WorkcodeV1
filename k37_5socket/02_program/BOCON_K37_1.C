
/***************************************************************************
*����2�ʹ���7��������Ⱦ��,���Ǳ��ͺ�����Ϊ10000,������Ϊmodbus��վ�������
*����8�ĵ�ַ��������Ϊ100�ɿ����ۻ�������ʾ,����Ϊ�����ر���ʾ,���ϴ��ۻ���������
*����8�ĵ�ַ��������Ϊ200�ɿ����ۻ�������ʾ,����Ϊ�����ر���ʾ,�ϴ��ۻ���������B11
*����8�ĵ�ַ��������Ϊ201�ɿ����ۻ�������ʾ,����Ϊ�����ر���ʾ,�ϴ��ۻ���������B21
*����8�ĵ�ַ��������Ϊ202�ɿ����ۻ�������ʾ,����Ϊ�����ر���ʾ,�ϴ��ۻ���������B00
*���ڶ�modbus������,�ۻ�������˲ʱ������ƫ��λ�ÿ��ڴ���8����ʼ�Ĵ�������
*�豸������Ϊ96,���η������·�����Ĵ�����Ӧ
*�豸������Ϊ97,������1�·������ݰ�ͨ��������5���
*�豸������Ϊ98,����1��������������·������ݰ�����
*�豸������Ϊ99,ƽ̨�����������ݰ�����Ҫ���ӻس�����
*�����豸��Ϊ100,�ɽ�ģ������ȡ��ֵ��ʪ��ֵת��Ϊ�ɻ�ֵ���
*�豸������Ϊ101,8011�Ǳ����㿪������������,�������õ�����������ֵ,����������
*�豸������Ϊ102,8011�Ǳ����㿪������������,�������õ�����������ֵ,����ֵ����ʵ��ֵ
*ϵͳ����->�ɼ�����������->���ñ�־ 1"F",2"M",3"S",4"C",5"B",�ر����ûָ�Ĭ��"D""T""N"����״̬����Ϊ0
*
*(��Ⱦ�ﷴ���������,����8������Ϊ����ʱ���ж�,����8����������Ϊ����ֵ�ж�,����8��ַΪ��Ⱦ�������ֵ
*��Ⱦ�ﷴ�������ַΪ�����Ǳ����ڵĵ�ַ������Ϊ����8����������,����8����ʼ�Ĵ����������ֱ�Ϊ���صĵļĴ���ֵ��д���ֵ)
*(��modbus�ķ����������������Ǳ�)(Ĭ�ϲ������ù���)
*
*(��Ⱦ����Ƽ̵���)(Ĭ�ϲ������ù���)
*
*(������Ϊmodbustcp�������Ӧ�������)(Ĭ�ϲ������ù���)
*
*(�������8014�������ݰ�)(Ĭ�ϲ������ù���)
*
******************************************************************************/


#class auto
#memmap xmem

#if 0
COMPILE_SECONDARY_PROG //���������ļ���
#endif

#define SW_VERSION   "BOCON_V41_180627_1"//�����汾��
#define SOCKET_NUMBER		5//����������
#define COLECTWATSEC		5//����೤ʱ��ɼ�һ������,��λs
#define BOCON_UDP0_TCP1         1//1TCP,0DUP
#define TCPGPRSBUF		1036//TCP�շ����ݵĻ�������С
#define TCPTIMEOUT		300//TCP�ĳ�ʱ����
#define PROTO_ACK_FLAG		0//HJ/T 212Э���Ƿ���ҪӦ��ı�־��0��1��3
#define PROTO_ACK_9011		1//�Ƿ���9011����Ӧ��Ŀ���
#define PROTO_ACK_9012		1//�Ƿ���9012����ִ�н��Ӧ��Ŀ���
#define MODBUS_TCP_SERVER	0//����modbusTcp������
#define YANCHEN_KELIWU_BMP	1//1�̳�0������
#define FEIQI_BIAOKUANG_BMP	1//1����0�������
/*****************************************/
//��ͨ���꿪�����Ǳ��ͺ�,�����̫����Щ�Ǳ�Ϊ����״̬
//��������ܻ���ɳ���̫��,����������һЩ�Ǳ��ͺ�
//1����0�ر�,��ȫ���ر�
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


#define FENSHAOLU	          	0//����¯��س�����򿪣��������겻��ͻ
//���º�ͬʱֻ�ܿ���1��
#define XIAMENYUANSHENGTAI        	0//����Դ��̬
#define DALIANHAOHAISHUI          	0//�����ƺ�ˮ����
#define JAINGXIYIZHENG	          	0//��������,������Ⱦ��,�Ǳ�9999,10322
#define JIANGXIJIAHAOYONGSHENG		0//�����κ���ʢ�����Ƽ�,ͬ��������,�����Ǳ�9998
#define WUXIHUANTONG	          	0//������ͨ,�Ǳ�1037,�Ǳ�10322
#define NANJINGHONGKAI	          	0//�Ͼ��迭,���ӱ���98
#define SUZHOUWEISHUI	          	0//������ˮ
#define HUIZHOULVKE_MODBUSTCP     	0//�����̿ơ���modbusTCP��com1���
#define ZHAOQINGLVTUO             	0//�������ػ����ͻ�,����S09��̬����,�����Ǳ�
#define JIAOTONGWUZI              	0//����¯���򣬽�ͮ����
#define HANGZHOUHAICHI            	0//���ݺ���
#define HAERBINGWEIER	          	0//������ά��,��������������ݰ�
#define GUIZHOUCHENGDA			0//���ݳɴ�,��������
#define XIJIANGHUANBAO			0//��������,��������
#define SUZHOUCHENSHUO			0//�����˶,��������
#define JIANGXIBOYUAN			0//������Զ,������ˮ������
#define KAIMINGKEJI			0//�����Ƽ�,��������,�޸ĵ�λ
#define XIAMENLIANAOMEIYE		0//����������ҵ,��������,����Ǳ���485
#define HUNANTUOAN			0//����ʡ�ذ�,��VOC1��VOC2,���ϴ�
#define JUGUANGKEJI			0//�۹�Ƽ�,��������
#define CHENGDUXINYITENG		0//�ɶ�������,��������
#define SICHUANHONGMEI			0//�Ĵ�����,������5���̳�����ĳ�039
#define SHIYONGWUJIN			0//�������
#define HEBEIBAIJIN			0//�ӱ��׾�,ȡ�������Զ�����
#define GUANGZHOUXINHUAN		0//�����»������ֹ�˾��ͳһk37�İ汾
#define GUANGZHOUXINHUANHEYUAN	        0//�����»���Դ������Դ�У�ƽ̨Э�鲻ͬ
#define CHANGSHAHUASHIJIE		0//��ɳ��ʱ��	,����¯����
#define GUANGDONGTIANRUI		0//�㶫����,9999�Ǳ������������ۼ�
#define XICHANGSANFENG			0//�������壬S06 ������ǰ��־λ״̬
#define HAERBINGJIEYUAN			0//��������Դ�����ӿ�ʢ������
#define NANJINGHONGLI			0//�Ͼ��������������ƣ�����Э��
#define GUANGZHOUSHIJING		0//������������������
#define GUANGZHOUBIYUAN			0//���ݱ�Դ
#define QINGDAOLUBO			    1//�ൺ·�������ӱ���


#if(HUIZHOULVKE_MODBUSTCP == 1)
#define SET_POINT_NUM   	2//������ʾС����λ��,�Լ��ϴ�������С����λ��,���÷�Χ1-3(�������ϴ���С�����ݲ��޸�)
#else
#define SET_POINT_NUM   	4//������ʾС����λ��,�Լ��ϴ�������С����λ��,���÷�Χ1-3(�������ϴ���С�����ݲ��޸�)
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


char hjt212_state[SOCKET_NUMBER];               //ͨ����·��״̬
						//0-δ����
						//1-����δ��½
						//2�ѵ�½

/*******************************************************************************
��������ϵͳʱ��֮ǰ�ȵ��ñ�������������ض�ʱ����ָ��
flag		1-ʱ����󣬲���Ҫ����NandFlashдָ��
    0-ʱ���С����Ҫ���ص���NandFlashдָ��
*******************************************************************************/
void update_rtc(char flag)
{
    auto char c;

    reboot_task();
    tm_ts = SEC_TIMER;                   //menu��ʱ�Ķ�ʱ��
    sampleSEC = SEC_TIMER;               //����������ʱ��
    samplemsgSEC = SEC_TIMER;            //�������涨ʱ��

    for (c = 0; c < SOCKET_NUMBER; c++)
    {
	tm_out[c] = SEC_TIMER;          //�����������Ӷ�ʱ��
	heartBeat[c] = SEC_TIMER;       //��������������ʱ��
	reqTimeout[c] = SEC_TIMER;
	sec_alarm[c] = SEC_TIMER;
	sec_rt_data[c] = SEC_TIMER;
	sec_rt_dev[c] = SEC_TIMER;
	sec_temp_info[c] = SEC_TIMER;
    }

    if (flag == 0)
    { //��ʱ���С
	update_nf_ptr();    //����Flashдָ��
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
�����յ��ķ��������ݰ�����ȡ����������
���������err_flag�	5-��ͷ��
    4-�����ȴ�
    3-CRC��
    2-MN�����
    1-���������
    0-��ȷ����
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
    parsePackage(no);            //�����յ������ݰ�
				 //DBG(prtRxData(no);
    if (err_flag[no] < 4)
    {
	parseCmd(no);           //����Ԥ����������ʱ����4���µ�ֵ������Ӧֻ����0��1
    }
    else                         //Ҳ���������Ӧ��Ӧ
    {
	ack_flag[no] = 0;
	if (devNo != 96)
	{
	    packReqAck(no, getFlag(no));  //�յ����������Ӧ��������
	}
    }
}

void chk_hjt212_state(char no)
{
    if (TCP_OK[no] == 0)             //δ����
    {
	hjt212_state[no] = 0;
    }
    else if (hjt212_state[no] == 2) //���������ѵ�½������ͨ��״̬
    {
	if (tcp_tlen[no] == 0)
	{
	    chk_hjt212_cmd(no);
	}
    }
    else if (hjt212_state[no] == 1) //���������ѳ�ʼ����δ��½
    {
	if (login[no] == 1) hjt212_state[no] = 2;    //�յ�½�ɹ����ñ�־
	else                              //��δ��½
	{
	    //hjt212_state[no] ++;	//�Ƿ��Զ����´˱�־������ȷ�������Ӧ?
	    if (strcmp(dialName, "LOGIN") == 0)
	    {
		if (SEC_TIMER >= (sec_rt_data[no] + rtdInterval[no]))
		{
		    sec_rt_data[no] = SEC_TIMER; //��ʵʱ�����ϱ������ڷ��͵�½����
		    txLogReq(no, 1);        //1-8011��2-9021
		}
		else if (ack_flag[no] == 80) //����Ƿ��յ�Ӧ��
		{
		    exeCmd(no);             //�ȴ���������Ӧ��½����
		}
	    }
	    else
	    {
		hjt212_state[no]++;
		login[no]++;               //����Ҫ��½
	    }
	}
    }
    else if (hjt212_state[no] == 0) //��������δ��ʼ������
    {
	if (strcmp(dialName, "LOGIN") == 0)
	{
	    hjt212_init(no, 0, 3);      //��ʼ��Ϊδ��½����Ҫ���͵�½����
	}
	else
	{
	    hjt212_init(no, 1, 3);      //����2��0-δ��½��1-�ѵ�½
					//����3��0-���ϴ���1-�Զ��ϴ�ʵʱ���ݣ�
					//			2-�Զ��ϴ��豸״̬��3-���Զ��ϴ�
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

//������
void main(void)
{
    k37Init();        //��ʼ���ײ�Ӳ������
    k37_hmi_init();   //��ʼ���˻��ӿ�
    initTcpVar();     //��ʼ������ӿ�
    polCodeInit();    //��ʼ��������ͱ�������
    nf_operate_init(); //��ʼ��Nand Flash�洢ϵͳ
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
	disp_flag_S06();	//S06��ֵ��Ϊflagֵ
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

