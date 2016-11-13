#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include "debug.h"

#if (defined __QNX__) | (defined __QNXNTO__)
    /* QNX specific headers */
    #include <unix.h>
#else
    /* Linux / MacOS POSIX timer headers */
    #include <sys/time.h>
    #include <time.h>
    #include <arpa/inet.h>
#endif


#include "xtofmavlinktest.h"
#include "mavlink/common/mavlink.h"

extern "C"
{
    #include "xtofReadSonar.h"
};

#define FALSE -1
#define TRUE 0

mavlink_system_t mavlink_system;
struct sockaddr_in g_gcAddr;
int g_sock;
int g_uartFd;//串口

/* QNX timer version */
#if (defined __QNX__) | (defined __QNXNTO__)
uint64_t microsSinceEpoch()
{
    
    struct timespec time;
    
    uint64_t micros = 0;
    
    clock_gettime(CLOCK_REALTIME, &time);  
    micros = (uint64_t)time.tv_sec * 100000 + time.tv_nsec/1000;
    return micros;
}
#else
//the units is us not ms 
uint64_t microsSinceEpoch()
{
    
    struct timeval tv;
    
    uint64_t micros = 0;
    
    gettimeofday(&tv, NULL);  
    micros =  ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;
    //printf("%lu\n",micros);
    return micros;
}
#endif


int mavlink_example()
{
    char target_ip[100];
    
    float position[6] = {};
    int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in gcAddr; 
    struct sockaddr_in locAddr;
    //struct sockaddr_in fromAddr;
    uint8_t buf[BUFFER_LENGTH];
    ssize_t recsize;
    socklen_t fromlen;
    int bytes_sent;
    mavlink_message_t msg;
    uint16_t len;
    int i = 0;
    //int success = 0;
    unsigned int temp = 0;
    
    // Check if --help flag was used
    //if ((argc == 2) && (strcmp(argv[1], help) == 0))
    // {
    //     printf("\n");
    //     printf("\tUsage:\n\n");
    //     printf("\t");
    //    // printf("%s", argv[0]);
    //     printf(" <ip address of QGroundControl>\n");
    //     printf("\tDefault for localhost: udp-server 127.0.0.1\n\n");
    //     //exit(EXIT_FAILURE);
    // }
    
    
    // Change the target ip if parameter was given
    #ifdef DEBIAN
        strcpy(target_ip, "115.156.233.176");
    #else
        strcpy(target_ip, "127.0.0.1");
    #endif
    // if (argc == 2)
    // {
    //     strcpy(target_ip, argv[1]);
    // }
    
    
    memset(&locAddr, 0, sizeof(locAddr));
    locAddr.sin_family = AF_INET;
    locAddr.sin_addr.s_addr = INADDR_ANY;
    locAddr.sin_port = htons(14551);
    
    /* Bind the socket to port 14551 - necessary to receive packets from qgroundcontrol */ 
    if (-1 == bind(sock,(struct sockaddr *)&locAddr, sizeof(struct sockaddr)))
    {
        perror("error bind failed");
        close(sock);
        exit(EXIT_FAILURE);
    } 
    
    /* Attempt to make it non blocking */
    if (fcntl(sock, F_SETFL, O_NONBLOCK | FASYNC) < 0)
    {
        fprintf(stderr, "error setting nonblocking: %s\n", strerror(errno));
        close(sock);
        exit(EXIT_FAILURE);
    }
    
    
    memset(&gcAddr, 0, sizeof(gcAddr));
    gcAddr.sin_family = AF_INET;
    gcAddr.sin_addr.s_addr = inet_addr(target_ip);
    gcAddr.sin_port = htons(14550);
            
    for (;;) 
    {
        
        /*Send Heartbeat */
        mavlink_msg_heartbeat_pack(1, 200, &msg, MAV_TYPE_HELICOPTER, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
        len = mavlink_msg_to_send_buffer(buf, &msg);
        bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&gcAddr, sizeof(struct sockaddr_in));
        
        // /* Send Status */
        // mavlink_msg_sys_status_pack(1, 200, &msg, 0, 0, 0, 500, 11000, -1, -1, 0, 0, 0, 0, 0, 0);
        // len = mavlink_msg_to_send_buffer(buf, &msg);
        // bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&gcAddr, sizeof (struct sockaddr_in));
        
        /* Send Local Position */
        // mavlink_msg_local_position_ned_pack(1, 200, &msg, microsSinceEpoch(), 
        //                                 position[0], position[1], position[2],
        //                                 position[3], position[4], position[5]);
        // len = mavlink_msg_to_send_buffer(buf, &msg);
        // bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&gcAddr, sizeof(struct sockaddr_in));
        
        // /* Send attitude */
        // mavlink_msg_attitude_pack(1, 200, &msg, microsSinceEpoch(), 1.2, 1.7, 3.14, 0.01, 0.02, 0.03);
        // len = mavlink_msg_to_send_buffer(buf, &msg);
        // bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&gcAddr, sizeof(struct sockaddr_in));
        
        
        // memset(buf, 0, BUFFER_LENGTH);
        // recsize = recvfrom(sock, (void *)buf, BUFFER_LENGTH, 0, (struct sockaddr *)&gcAddr, &fromlen);
        // if (recsize > 0)
        // {
        //     // Something received - print out all bytes and parse packet
        //     mavlink_message_t msg;
        //     mavlink_status_t status;
            
        //     printf("Bytes Received: %d\nDatagram: ", (int)recsize);
        //     for (i = 0; i < recsize; ++i)
        //     {
        //         temp = buf[i];
        //         printf("%02x ", (unsigned char)temp);
        //         if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status))
        //         {
        //             // Packet received
        //             printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
        //         }
        //     }
        //     printf("\n");
        // }
        memset(buf, 0, BUFFER_LENGTH);
        sleep(1); // Sleep one second
    }
}

int mavlinkUartInit()
{
    int fd ;

    fd = open(MAVLINK_UART_DEVICE,O_RDWR);
    if(-1 == fd)
    {
        fprintf(stderr,"can not open mavlink uart\n");
    }
    setSpeed(fd, MAVLINK_UART_BAUDRATE);
    if(setParity(fd,8,1,'N') == FALSE)
    {
        fprintf(stderr, "set parity error\n");
    }
    fprintf(stderr, "open mavlink uart\n");
    
    g_uartFd = fd;
    return fd;
}


int mavlinkNetInit()
{
    char target_ip[100];

   // struct sockaddr_in gcAddr; 
    struct sockaddr_in locAddr;
    //struct sockaddr_in fromAddr;
    uint8_t buf[BUFFER_LENGTH];
    ssize_t recsize;
    socklen_t fromlen;
    int bytes_sent;
    mavlink_message_t msg;
    uint16_t len;
    int i = 0;
    //int success = 0;
    unsigned int temp = 0;

    g_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    
    // Change the target ip if parameter was given
    #ifdef DEBIAN
        strcpy(target_ip, "10.42.0.1");
    #else
        strcpy(target_ip, "127.0.0.1");
    #endif
    
    locAddr.sin_family = AF_INET;
    locAddr.sin_addr.s_addr = INADDR_ANY;
    locAddr.sin_port = htons(14551);
    
    /* Bind the socket to port 14551 - necessary to receive packets from qgroundcontrol */ 
    if (-1 == bind(g_sock,(struct sockaddr *)&locAddr, sizeof(struct sockaddr)))
    {
        perror("error bind failed");
        close(g_sock);
        exit(EXIT_FAILURE);
    } 
    
    /* Attempt to make it non blocking */
    if (fcntl(g_sock, F_SETFL, O_NONBLOCK | FASYNC) < 0)
    {
        fprintf(stderr, "error setting nonblocking: %s\n", strerror(errno));
        close(g_sock);
        exit(EXIT_FAILURE);
    }
    
    
    g_gcAddr.sin_family = AF_INET;
    g_gcAddr.sin_addr.s_addr = inet_addr(target_ip);
    g_gcAddr.sin_port = htons(14550);
}

void mavlink_send_bytes(mavlink_channel_t chan, const uint8_t * ch, uint16_t length)
{
    if(chan == MAVLINK_COMM_0)
    {
        sendto(g_sock, ch, length, 0, (struct sockaddr*)&g_gcAddr, sizeof(struct sockaddr_in));//网络套接字
    }
    else if(chan == MAVLINK_COMM_1)
    {
        printf("uart write length:%d\n", length);
        printf("uart write: %s",ch);
        write(g_uartFd, ch, length);//串口
    }
}