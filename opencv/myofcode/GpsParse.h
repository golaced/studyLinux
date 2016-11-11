#ifndef _GPS_PARSE_H_
#define _GPS_PARSE_H_

enum ubs_protocol_bytes {
        PREAMBLE1 = 0xb5,
        PREAMBLE2 = 0x62,
        CLASS_NAV = 0x01,
        CLASS_ACK = 0x05,
        CLASS_CFG = 0x06,
        CLASS_MON = 0x0A,
        CLASS_RXM = 0x02,
        MSG_ACK_NACK = 0x00,
        MSG_ACK_ACK = 0x01,
        MSG_POSLLH = 0x2,
        MSG_STATUS = 0x3,
        MSG_DOP = 0x4,
        MSG_SOL = 0x6,
        MSG_VELNED = 0x12,
        MSG_CFG_PRT = 0x00,
        MSG_CFG_RATE = 0x08,
        MSG_CFG_SET_RATE = 0x01,
        MSG_CFG_NAV_SETTINGS = 0x24,
        MSG_CFG_SBAS = 0x16,
        MSG_CFG_GNSS = 0x3E,
        MSG_MON_HW = 0x09,
        MSG_MON_HW2 = 0x0B,
        MSG_NAV_SVINFO = 0x30,
        MSG_RXM_RAW = 0x10,
        MSG_RXM_RAWX = 0x15
    };
enum GPS_Status {
        NO_GPS = 0,             ///< No GPS connected/detected
        NO_FIX = 1,             ///< Receiving valid GPS messages but no lock
        GPS_OK_FIX_2D = 2,      ///< Receiving valid messages and 2D lock
        GPS_OK_FIX_3D = 3,      ///< Receiving valid messages and 3D lock
        GPS_OK_FIX_3D_DGPS = 4, ///< Receiving valid messages and 3D lock with differential improvements
        GPS_OK_FIX_3D_RTK = 5,  ///< Receiving valid messages and 3D lock, with relative-positioning improvements
    };
enum ubx_nav_status_bits {
        NAV_STATUS_FIX_VALID = 1,
        NAV_STATUS_DGPS_USED = 2
    };
enum ubs_nav_fix_type {
        FIX_NONE = 0,
        FIX_DEAD_RECKONING = 1,
        FIX_2D = 2,
        FIX_3D = 3,
        FIX_GPS_DEAD_RECKONING = 4,
        FIX_TIME = 5
    };

struct ubx_nav_posllh {
        uint32_t time;                                  // GPS msToW
        int32_t longitude;
        int32_t latitude;
        int32_t altitude_ellipsoid;
        int32_t altitude_msl;
        uint32_t horizontal_accuracy;
        uint32_t vertical_accuracy;
 };
struct ubx_nav_status {
        uint32_t time;                                  // GPS msToW
        uint8_t fix_type;
        uint8_t fix_status;
        uint8_t differential_status;
        uint8_t res;
        uint32_t time_to_first_fix;
        uint32_t uptime;                                // milliseconds
 };
 struct ubx_nav_solution {
        uint32_t time;
        int32_t time_nsec;
        uint16_t week;
        uint8_t fix_type;
        uint8_t fix_status;
        int32_t ecef_x;
        int32_t ecef_y;
        int32_t ecef_z;
        uint32_t position_accuracy_3d;
        int32_t ecef_x_velocity;
        int32_t ecef_y_velocity;
        int32_t ecef_z_velocity;
        uint32_t speed_accuracy;
        uint16_t position_DOP;
        uint8_t res;
        uint8_t satellites;
        uint32_t res2;
    };
		
		struct  ubx_nav_velned {
        uint32_t time;                                  // GPS msToW
        int32_t ned_north;
        int32_t ned_east;
        int32_t ned_down;
        uint32_t speed_3d;
        uint32_t speed_2d;
        int32_t heading_2d;
        uint32_t speed_accuracy;
        uint32_t heading_accuracy;
    };
		
		
		union UBX_MSGDATA{
        struct ubx_nav_posllh posllh;
        struct ubx_nav_status status;
        struct ubx_nav_solution solution;
        struct ubx_nav_velned velned;
        uint8_t bytes[4*13];
    };
		
typedef struct{
	int16_t gps_new_data;
	int16_t gps_new_display;
	int32_t lng;
	int32_t lat;
	int32_t alt;
	uint32_t pos_time;
	int32_t heading_2d;
	uint16_t hdop;
	uint8_t num_sats;
	uint8_t fix;
	float ground_speed;
	float velned_x;
	float velned_y;
	float velned_z;
}Gps_Status;


int ListenForGpsData(void);
void GetRawGps(Gps_Status* pGps);
#endif
