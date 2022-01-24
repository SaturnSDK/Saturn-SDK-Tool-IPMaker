#ifndef __IPMAKER_SYSTEMID_H__
#define __IPMAKER_SYSTEMID_H__

#define TITLE_SIZE 112

struct SYSTEM_ID
{
	char	HardwareID[ 16 ];
	char	MakerID[ 16 ];
	char	ProductNumber[ 10 ];
	char	VersionNumber[ 6 ];
	char	ReleaseDate[ 8 ];
	char	DeviceInformation[ 8 ];
	char	CompatibleAreaSymbols[ 10 ];
	char	Space[ 6 ];
	char	Peripherals[ 16 ];
	char	Title[ TITLE_SIZE ];
	char	Reserved1[ 16 ];
	int		IPSize;
	int		Reserved2;
	int		MasterStack;
	int		SlaveStack;
	int		FirstReadAddress;
	int		FirstReadSize;
	char	Reserved3[ 8 ];
};

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

typedef enum
{
	MAKER_ID_SEGA,
	MAKER_ID_3RDPARTY
}MAKER_ID;

int IPT_DefaultSystemID( struct SYSTEM_ID *p_pSystemID, MAKER_ID p_MakerID );

int IPT_SetMakerID( struct SYSTEM_ID *p_pSystemID, char *p_pMakerID );

int IPT_SetProductNumber( struct SYSTEM_ID *p_pSystemID,
	char *p_pProductNumber );

int IPT_SetVersionNumber( struct SYSTEM_ID *p_pSystemID, int p_Major,
	int p_Minor );

int IPT_SetReleaseDate( struct SYSTEM_ID *p_pSystemID, int p_Year, int p_Month,
	int p_Date );

int IPT_SetDeviceInformation( struct SYSTEM_ID *p_pSystemID, int p_CDNumber,
	int p_CDCount );

int IPT_SetCompatibleAreas( struct SYSTEM_ID *p_pSystemID, int p_Areas );

int IPT_SetCompatiblePeripherals( struct SYSTEM_ID *p_pSystemID,
	int p_Peripherals );

int IPT_SetTitle( struct SYSTEM_ID *p_pSystemID, char *p_pTitle );

int IPT_SetIPSize( struct SYSTEM_ID *p_pSystemID, int p_Size );

void IPT_SetMasterStackAddress( struct SYSTEM_ID *p_pSystemID,
	int p_StackAddress );

int IPT_SetSlaveStackAddress( struct SYSTEM_ID p_SystemID,
	int p_StackAddress );

int IPT_SetFirstReadAddress( struct SYSTEM_ID *p_pSystemID,
	int p_FirstReadAddress );

void IPT_PrintSystemID( struct SYSTEM_ID *p_SystemID );

#endif // __IPMAKER_SYSTEMID_H__

