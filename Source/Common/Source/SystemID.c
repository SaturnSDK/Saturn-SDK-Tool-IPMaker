#include "SystemID.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"

int IPT_DefaultSystemID( struct SYSTEM_ID *p_pSystemID, MAKER_ID p_MakerID )
{
    // Clean up the place before further actions
    memset(p_pSystemID, 0, sizeof (struct SYSTEM_ID));

    memcpy(p_pSystemID->HardwareID, sHardware_ID, HWID_SIZE);

    switch (p_MakerID) {
        case MAKER_ID_SEGA:
            memcpy(p_pSystemID->MakerID, sSEGA_MakerID, MAKERID_SIZE);
            memcpy(p_pSystemID->ProductNumber, sSEGA_Product_Number, PRD_NB_SIZE);
            break;
        case MAKER_ID_3RDPARTY:
            memcpy(p_pSystemID->MakerID, sThirdParty_MakerID, MAKERID_SIZE);
            memcpy(p_pSystemID->ProductNumber, sThirdParty_Product_Number, PRD_NB_SIZE);
            break;
        default:
            fprintf (stderr,"Wrong Maker ID\n");
            return 1;
    }

    memcpy(p_pSystemID->VersionNumber, sVersion_Number, VER_NB_SIZE);
    memcpy(p_pSystemID->ReleaseDate, sReleaseDate, RDATE_SIZE);
    memcpy( p_pSystemID->DeviceInformation, sDeviceInformation, DEV_INFO_SIZE );
    memcpy( p_pSystemID->CompatibleAreaSymbols, sCompatibleAreaSymbols, AREACODE_SIZE );
	memset( p_pSystemID->Space, ' ', SPACE_SIZE );
    memcpy( p_pSystemID->Peripherals, sPeripherals, PERIPH_SIZE );

    IPT_SetTitle(p_pSystemID, sDefaultGameTitle);

	memset( p_pSystemID->Reserved1, ' ', RESERVED1_SIZE );

    IPT_SetIPSize(p_pSystemID, 0x00001800);

    IPT_SetMasterStackAddress(p_pSystemID, 0x00000000);
    IPT_SetSlaveStackAddress(p_pSystemID, 0x00000000);

    IPT_SetFirstReadAddress(p_pSystemID, 0x06004000);

    IPT_SetFirstReadSize(p_pSystemID, 0);

	memset( p_pSystemID->Reserved3, ' ', sizeof( p_pSystemID->Reserved3 ) );

	return 0;
}

void IPT_PrintSystemID( struct SYSTEM_ID *p_SystemID )
{
	char Area;
	char Peripheral;
	int Counter;
	int MasterStack;
	int SlaveStack;

	printf( "Hardware ID:                  %.16s\n", p_SystemID->HardwareID );
	printf( "Maker ID:                     %.16s\n", p_SystemID->MakerID );
	printf( "Product number:               %.10s\n",
		p_SystemID->ProductNumber );
	printf( "Version:                      %.6s\n", p_SystemID->VersionNumber );
	printf( "Release date:                 %.4s/%.2s/%.2s\n",
		p_SystemID->ReleaseDate, p_SystemID->ReleaseDate + 4,
		p_SystemID->ReleaseDate + 6 );
	printf( "Device information:           %.8s\n",
		p_SystemID->DeviceInformation );
	printf( "Compatible areas:             " );

	Area = *( p_SystemID->CompatibleAreaSymbols );
	Counter = 0;
	while( Area != ' ' && Counter < 10 ) {
		if( Counter != 0 ) {
			printf( "\n                              " );
		}

		switch( Area ) {
			case 'J':
				printf( "Japan" );
				break;
			case 'T':
				printf( "Asia NTSC" );
				break;
			case 'U':
				printf( "North America" );
				break;
			case 'B':
				printf( "South America NTSC" );
				break;
			case 'K':
				printf( "Korea" );
				break;
			case 'A':
				printf( "East Asia PAL" );
				break;
			case 'E':
				printf( "Europe" );
				break;
			case 'L':
				printf( "South America PAL" );
				break;
			default:
				printf( "UNKNOWN" );
				break;
		}
		++Counter;
		Area = ( *( p_SystemID->CompatibleAreaSymbols + Counter ) );
	}
	printf( "\n" );

	printf( "Peripherals:                  " );

	Counter = 0;
	Peripheral = *( p_SystemID->Peripherals );

	while( Peripheral != ' ' && Counter < 10 ) {
		if( Counter !=0 ) {
			printf( "\n                              " );
		}

		switch( Peripheral ) {
			case 'J':
				printf( "Control pad" );
				break;
			case 'A':
				printf( "Analog Controller (Mission Stick)" );
				break;
			case 'M':
				printf( "Mouse" );
				break;
			case 'K':
				printf( "Keyboard" );
				break;
			case 'S':
				printf( "Steering controller (Arcade Racer" );
				break;
			case 'T':
				printf( "Multitap (6Player)" );
				break;
            case 'G':
                printf( "Gun (Virtua Gun/Stunner)" );
                break;
            case 'C':
                printf( "Saturn-to-Saturn cable" );
                break;
            case 'P':
                printf( "MPEG" );
                break;
            case 'F':
                printf( "FDD" );
                break;
            case 'D':
                printf( "Modem" );
                break;
            case 'X':
                printf( "XBAND" );
                break;
			default:
				printf( "UNKNOWN : %c", Peripheral);
				break;
		}

		++Counter;
		Peripheral = ( *( p_SystemID->Peripherals + Counter ) );
	}
	printf( "\n" );

	printf( "Title:                        %.122s\n", p_SystemID->Title );
	printf( "IP Size:                      0x%08X\n", IPT_GetIPSize(p_SystemID) );

	if( (MasterStack = IPT_GetMasterStackAddress(p_SystemID)) == 0 ) {
		MasterStack = 0x06001000;
	}

	printf( "Master stack pointer address: 0x%08X\n", MasterStack );

	if( (SlaveStack = IPT_GetSlaveStackAddress(p_SystemID)) == 0 ) {
		SlaveStack = 0x06000D00;
	}

	printf( "Slave stack pointer address:  0x%08X\n", SlaveStack );

	printf( "1st read address:             0x%08X\n",
            IPT_GetFirstReadAddress(p_SystemID) );

	printf( "1st read size:                0x%08X\n",
            IPT_GetFirstReadSize(p_SystemID) );
}

/*
 * The game title uses English alphanumeric characters only.
 * A space can be inserted in the game title. “/-:” can be
 * used as a delimiter between titles when more than one title is
 * listed.
 *
 * When there are multiple titles:
 * 1) “TITLE1/TITLE2/TITLE3∆∆∆∆”
 * 2) “J:TITLE1∆∆U:TITLE2∆∆∆∆∆∆”
 */
int IPT_SetTitle( struct SYSTEM_ID *p_SystemID, const char *p_pTitle ) {

    if (p_pTitle == NULL) {
        fprintf (stderr,"ERROR : Title not set\n");
        return EXIT_FAILURE;
    }

    size_t len = strlen(p_pTitle);

    if (len > TITLE_SIZE ) {
        fprintf (stderr,"WARNING : Title too long, it will be truncated\n");
    }

    // TODO : Add content validation ... not my war !

    memset(p_SystemID->Title, ' ', TITLE_SIZE);

    memcpy( p_SystemID->Title, p_pTitle, len);

    return EXIT_SUCCESS;
}

/*
 * Specifies the size (byte number) of the Initial Program (IP).
 *
 * AIP is placed immediately after the boot code, creating a
 * single file, and the size of the file is specified. Parameters
 * must be all long-word aligned (multiples of 4H).
 * Range : 1000 ~ 8000H
 */
void IPT_SetIPSize( struct SYSTEM_ID *p_SystemID, int p_Size ) {
    // TODO :  Add range validation and alignment
    sprintf(p_SystemID->IPSize, "%d", p_Size);
}

int IPT_GetIPSize( struct SYSTEM_ID *p_SystemID) {
    return atol(p_SystemID->IPSize);
}

void IPT_SetMasterStackAddress( struct SYSTEM_ID *p_SystemID,
                                int p_StackAddress ) {
    sprintf(p_SystemID->MasterStack, "%d", p_StackAddress);
}

int IPT_GetMasterStackAddress( struct SYSTEM_ID *p_SystemID ) {
    return atol(p_SystemID->MasterStack);
}

void IPT_SetSlaveStackAddress( struct SYSTEM_ID *p_SystemID,
                              int p_StackAddress ) {
    sprintf(p_SystemID->SlaveStack, "%d", p_StackAddress);
}

int IPT_GetSlaveStackAddress( struct SYSTEM_ID *p_SystemID ) {
    return atol(p_SystemID->SlaveStack);
}

void IPT_SetFirstReadAddress( struct SYSTEM_ID *p_SystemID,
                             int p_FirstReadAddress ){
    sprintf(p_SystemID->FirstReadAddress, "%d", p_FirstReadAddress);
}

int IPT_GetFirstReadAddress( struct SYSTEM_ID *p_SystemID ) {
    return atol(p_SystemID->FirstReadAddress);
}

void IPT_SetFirstReadSize( struct SYSTEM_ID *p_SystemID,
                          int p_FirstReadSize ) {
    sprintf(p_SystemID->FirstReadSize, "%d", p_FirstReadSize);
}

int IPT_GetFirstReadSize( struct SYSTEM_ID *p_SystemID ) {
    return atol(p_SystemID->FirstReadSize);
}
