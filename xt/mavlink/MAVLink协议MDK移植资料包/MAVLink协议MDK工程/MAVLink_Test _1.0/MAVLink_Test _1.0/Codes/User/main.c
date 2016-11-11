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
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PE端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->PB.5 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	GPIO_SetBits(GPIOC,GPIO_Pin_13);	
}



//-------------------------------mavlink----------------------------------

//结构体初始化
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
	
	//中断优先级组别设置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//初始化系统滴答定时器
	SysTick_Config(SystemCoreClock / 1000);	
	
	Scheduler_Init();
	
	//LED初始化
	LED_Init();
	
	//初始化串口1
	Uart1_Init(115200);
  
	//mavlink初始化
	mavlink_init();
	
	while (1)
  {
		if(cnt_1000ms >= 1000)//每过1000ms发送一次数据
		{
			//发送心跳包	
			mavlink_msg_heartbeat_send(MAVLINK_COMM_1,system_type,MAV_AUTOPILOT_GENERIC, MAV_MODE_MANUAL_DISARMED, 0, MAV_STATE_STANDBY);
			
			//发送姿态角包
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
			
			//串口1发送			
			Usart1_Send_Buf(buf,len);
						
			cnt_1000ms = 0;
		}
  }
}

void SysTick_IRQ(void)
{
	cnt_1000ms++;
}

//滴答定时器中断
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

