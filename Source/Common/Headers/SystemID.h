//
// System ID description
// Source : # ST-040-R4-051795 V1.0
//

#ifndef __IPMAKER_SYSTEMID_H__
#define __IPMAKER_SYSTEMID_H__

#define HWID_SIZE 		16
#define MAKERID_SIZE 	16
#define PRD_NB_SIZE 	10
#define VER_NB_SIZE 	6
#define RDATE_SIZE 		8
#define DEV_INFO_SIZE 	8
#define AREACODE_SIZE 	10
#define SPACE_SIZE 		6
#define PERIPH_SIZE 	16
#define TITLE_SIZE 		112
#define RESERVED1_SIZE 	16
#define IPSIZE_SIZE 	4
#define RESERVED2_SIZE  4
#define STACK_M_SIZE    4
#define STACK_S_SIZE    4
#define FADDR_SIZE    	4
#define FREAD_SIZE    	4
#define RESERVED3_SIZE  8

#define TOTAL_SIZE		256

struct SYSTEM_ID
{
	char	HardwareID[ HWID_SIZE ];
	char	MakerID[ MAKERID_SIZE ];
	char	ProductNumber[ PRD_NB_SIZE ];
	char	VersionNumber[ VER_NB_SIZE ];
	char	ReleaseDate[ RDATE_SIZE ];
	char	DeviceInformation[ DEV_INFO_SIZE ];
	char	CompatibleAreaSymbols[ AREACODE_SIZE ];
	char	Space[ SPACE_SIZE ];
	char	Peripherals[ PERIPH_SIZE ];
	char	Title[ TITLE_SIZE ];
	char	Reserved1[ RESERVED1_SIZE ];
	char 	IPSize[IPSIZE_SIZE];
	char	Reserved2[ RESERVED2_SIZE ];
	char	MasterStack[ STACK_M_SIZE ];
	char	SlaveStack[ STACK_S_SIZE ];
	char	FirstReadAddress[ FADDR_SIZE ];
	char	FirstReadSize[ FREAD_SIZE ];
	char	Reserved3[ RESERVED3_SIZE ];
} __attribute__((packed));

static const int AREA_JAPAN					= 0x00000001;
static const int AREA_EUROPE				= 0x00000002;
static const int AREA_NORTH_AMERICA			= 0x00000004;
static const int AREA_ASIA_NTSC				= 0x00000008;
static const int AREA_SOUTH_AMERICA_PAL		= 0x00000010;
static const int AREA_EAST_ASIA_PAL			= 0x00000020;
static const int AREA_KOREA					= 0x00000040;
static const int AREA_SOUTH_AMERICA_NTSC	= 0x00000080;

static const int PERIPHERAL_CONTROL_PAD				= 0x00000001;
static const int PERIPHERAL_ANALOGUE_CONTROLLER		= 0x00000002;
static const int PERIPHERAL_MOUSE					= 0x00000004;
static const int PERIPHERAL_KEYBOARD				= 0x00000008;
static const int PERIPHERAL_STEERING_CONTROLLER		= 0x00000010;
static const int PERIPHERAL_MULTITAP				= 0x00000020;

static const char sHardware_ID[]					= "SEGA SEGASATURN ";

static const char sSEGA_MakerID[]					= "SEGA ENTERPRISES";
static const char sThirdParty_MakerID[]				= "SEGA TP KAISHA-A";
static const char sThirdParty_MakerID_2[]			= "SEGA TP T-999   ";

static const char sSEGA_Product_Number[]			= "GS-9099   ";
static const char sThirdParty_Product_Number[]		= "T-99901G  ";

static const char sVersion_Number[]					= "V0.000";

static const char sReleaseDate[]					= "19941122";

static const char sDeviceInformation[]				= "CD-1/1  ";

static const char sCompatibleAreaSymbols[]			= "JTUBKAEL  ";
static const char sPeripherals[]					= "JAK             ";

static const char sDefaultGameTitle[]				= "GAME";

typedef enum
{
	MAKER_ID_SEGA,
	MAKER_ID_3RDPARTY
} MAKER_ID;

int IPT_DefaultSystemID( struct SYSTEM_ID *p_SystemID, MAKER_ID p_MakerID );

int IPT_SetMakerID( struct SYSTEM_ID *p_SystemID, char *p_pMakerID );

int IPT_SetProductNumber( struct SYSTEM_ID *p_SystemID,
	char *p_pProductNumber );

int IPT_SetVersionNumber( struct SYSTEM_ID *p_SystemID, int p_Major,
	int p_Minor );

int IPT_SetReleaseDate( struct SYSTEM_ID *p_SystemID, int p_Year, int p_Month,
	int p_Date );

int IPT_SetDeviceInformation( struct SYSTEM_ID *p_SystemID, int p_CDNumber,
	int p_CDCount );

int IPT_SetCompatibleAreas( struct SYSTEM_ID *p_SystemID, int p_Areas );

int IPT_SetCompatiblePeripherals( struct SYSTEM_ID *p_SystemID,
	int p_Peripherals );

int IPT_SetTitle( struct SYSTEM_ID *p_SystemID, const char *p_pTitle );

void IPT_SetIPSize( struct SYSTEM_ID *p_SystemID, int p_Size );

int IPT_GetIPSize( struct SYSTEM_ID *p_SystemID);

void IPT_SetMasterStackAddress( struct SYSTEM_ID *p_SystemID,
	int p_StackAddress );

int IPT_GetMasterStackAddress( struct SYSTEM_ID *p_SystemID );

void IPT_SetSlaveStackAddress( struct SYSTEM_ID *p_SystemID,
	int p_StackAddress );

int IPT_GetSlaveStackAddress( struct SYSTEM_ID *p_SystemID );

void IPT_SetFirstReadAddress( struct SYSTEM_ID *p_SystemID,
	int p_FirstReadAddress );

int IPT_GetFirstReadAddress( struct SYSTEM_ID *p_SystemID );

void IPT_SetFirstReadSize( struct SYSTEM_ID *p_SystemID,
                             int p_FirstReadSize );

int IPT_GetFirstReadSize( struct SYSTEM_ID *p_SystemID );

void IPT_PrintSystemID( struct SYSTEM_ID *p_SystemID );

#endif // __IPMAKER_SYSTEMID_H__

