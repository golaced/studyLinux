#include "includes.h"

//#include "checksum.h"

#include "mavlink_bridge_header.h"
#include "mavlink.h"
#include "checksum.h"
#include "protocol.h"
#include "common.h"

#include "ANO_Drv_Usart1.h"

static uint16_t cnt_1000ms;

void Scheduler_Init(void)
{
	cnt_1000ms = 0;
}

#define LED0 PCout(13)
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->PB.5 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
	GPIO_SetBits(GPIOC,GPIO_Pin_13);	
}



//-------------------------------mavlink----------------------------------

//�ṹ���ʼ��
mavlink_system_t mavlink_system;
void mavlink_init(void)
{
	mavlink_system.sysid = 20;                   ///< ID 20 for this airplane
	mavlink_system.compid = MAV_COMP_ID_IMU;     ///< The component sending the message is the IMU, it could be also a Linux process
	mavlink_system.type = MAV_TYPE_QUADROTOR;    ///< This system is an quadcopter

}

mavlink_message_t msg;
// Define the system type, in this case an airplane
uint8_t system_type = MAV_TYPE_QUADROTOR;
uint8_t autopilot_type = MAV_AUTOPILOT_PIXHAWK;//MAV_AUTOPILOT_GENERIC;
uint8_t system_mode = MAV_MODE_PREFLIGHT; ///< Booting up
uint32_t custom_mode = 0;                 ///< Custom mode, can be defined by user/adopter
uint8_t system_state = MAV_STATE_STANDBY; ///< System ready for flight

int main(void)
{
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	unsigned short len;
	
	//�ж����ȼ��������
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//��ʼ��ϵͳ�δ�ʱ��
	SysTick_Config(SystemCoreClock / 1000);	
	
	Scheduler_Init();
	
	//LED��ʼ��
	LED_Init();
	
	//��ʼ������1
	Uart1_Init(115200);
  
	//mavlink��ʼ��
	mavlink_init();
	
	while (1)
  {
		if(cnt_1000ms >= 1000)//ÿ��1000ms����һ������
		{
			//����������	
			mavlink_msg_heartbeat_send(MAVLINK_COMM_1,system_type,MAV_AUTOPILOT_GENERIC, MAV_MODE_MANUAL_DISARMED, 0, MAV_STATE_STANDBY);
			
			//������̬�ǰ�
			mavlink_msg_attitude_pack(	mavlink_system.sysid, 
																	mavlink_system.compid,
																	&msg,
																	30,
																	(float)(5.2f/180.0f*3.14f),			//roll
																	(float)(-3.2f/180.0f*3.14f),		//pitch
																	(float)(1.2f/180.0f*3.14f),			//yaw
																	(float)1.2f,
																	(float)1.2f,
																	(float)1.2f);
			len = mavlink_msg_to_send_buffer(buf, &msg);			
			
			//����1����			
			Usart1_Send_Buf(buf,len);
						
			cnt_1000ms = 0;
		}
  }
}

void SysTick_IRQ(void)
{
	cnt_1000ms++;
}

//�δ�ʱ���ж�
void SysTick_Handler(void)
{
	SysTick_IRQ();
}

/**
 * @brief Send multiple chars (uint8_t) over a comm channel
 *
 * @param chan MAVLink channel to use
 * @param ch Character to send
 */
void mavlink_send_uart_bytes(mavlink_channel_t chan, const uint8_t * ch, uint16_t length)
{
	if (chan == MAVLINK_COMM_0)
	{
		
	}
	if (chan == MAVLINK_COMM_1)
	{
		/* send to UART1 */
		Usart1_Send_Buf(ch, length);
	}
	if (chan == MAVLINK_COMM_2)
	{

	}
}

/*
 * Internal function to give access to the channel status for each channel
 */
mavlink_status_t* mavlink_get_channel_status(uint8_t channel)
{
	static mavlink_status_t m_mavlink_status[MAVLINK_COMM_NUM_BUFFERS];
	return &m_mavlink_status[channel];
}

/*
 * Internal function to give access to the channel buffer for each channel
 */
mavlink_message_t* mavlink_get_channel_buffer(uint8_t channel)
{
	static mavlink_message_t m_mavlink_buffer[MAVLINK_COMM_NUM_BUFFERS];
	return &m_mavlink_buffer[channel];
}

