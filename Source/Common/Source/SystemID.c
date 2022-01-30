#include "SystemID.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
            memcpy(p_pSystemID->ReleaseDate, sInitialReleaseDate, RDATE_SIZE);
            break;
        case MAKER_ID_3RDPARTY:
            memcpy(p_pSystemID->MakerID, sThirdParty_MakerID, MAKERID_SIZE);
            memcpy(p_pSystemID->ProductNumber, sThirdParty_Product_Number, PRD_NB_SIZE);
            memcpy(p_pSystemID->ReleaseDate, sInitialReleaseDate, RDATE_SIZE);
            break;
        case MAKER_ID_3RDPARTY_OWN: {
                time_t now;
                time(&now);
                struct tm *local = localtime(&now);
                memcpy(p_pSystemID->MakerID, sThirdPartyOwn_MakerID, MAKERID_SIZE);
                memcpy(p_pSystemID->ProductNumber, sThirdPartyOwn_Product_Number, PRD_NB_SIZE);
                IPT_SetReleaseDate(p_pSystemID,
                                   local->tm_year + 1900,
                                   local->tm_mon + 1,
                                   local->tm_mday);
            }
            break;
        default:
            fprintf (stderr,"Wrong Maker ID\n");
            return 1;
    }

    memcpy(p_pSystemID->VersionNumber, sVersion_Number, VER_NB_SIZE);

    memcpy( p_pSystemID->DeviceInformation, sDeviceInformation, DEV_INFO_SIZE );
    memcpy( p_pSystemID->CompatibleAreaSymbols, sCompatibleAreaSymbols, AREACODE_SIZE );
	memset( p_pSystemID->Space, ' ', SPACE_SIZE );
    memcpy( p_pSystemID->Peripherals, sDefaultPeripherals, PERIPH_SIZE );
    IPT_SetTitle(p_pSystemID, sDefaultGameTitle);
	memset( p_pSystemID->Reserved1, ' ', RESERVED1_SIZE );
    IPT_SetIPSize(p_pSystemID, nDefaultIPSize);
    IPT_SetMasterStackAddress(p_pSystemID, nDefaultMasterStackAddress);
    IPT_SetSlaveStackAddress(p_pSystemID, nDefaultSlaveStackAddress);
    IPT_SetFirstReadAddress(p_pSystemID, nDefaultFirstReadAddress);
    IPT_SetFirstReadSize(p_pSystemID, nDefaultFirstReadSize);

	memset( p_pSystemID->Reserved3, ' ', sizeof( p_pSystemID->Reserved3 ) );

	return 0;
}

void IPT_PrintSystemID( struct SYSTEM_ID *p_SystemID )
{
	char cArea;
	char cPeripheral;
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

    cArea = *( p_SystemID->CompatibleAreaSymbols );
	Counter = 0;
	while( cArea != ' ' && Counter < 10 ) {
		if( Counter != 0 ) {
			printf( "\n                              " );
		}

		switch( (Area)cArea ) {
			case eJapan:
				printf( "Japan" );
				break;
			case eAsiaNTSC:
				printf( "Asia NTSC" );
				break;
			case eNorthAmerica:
				printf( "North America" );
				break;
			case eSouthAmericaNTSC:
				printf( "South America NTSC" );
				break;
			case eKorea:
				printf( "Korea" );
				break;
			case eEastAsiaPAL:
				printf( "East Asia PAL" );
				break;
			case eEurope:
				printf( "Europe" );
				break;
			case eSouthAmericaPAL:
				printf( "South America PAL" );
				break;
			default:
				printf( "UNKNOWN" );
				break;
		}
		++Counter;
        cArea = ( *( p_SystemID->CompatibleAreaSymbols + Counter ) );
	}
	printf( "\n" );

	printf( "Peripherals:                  " );

	Counter = 0;
    cPeripheral = *( p_SystemID->Peripherals );

	while( cPeripheral != ' ' && Counter < 10 ) {
		if( Counter !=0 ) {
			printf( "\n                              " );
		}

		switch( (Peripheral)cPeripheral ) {
			case eControlPad:
				printf( "Control pad" );
				break;
			case eAnalogController:
				printf( "Analog Controller (Mission Stick)" );
				break;
			case eMouse:
				printf( "Mouse" );
				break;
			case eKeyboard:
				printf( "Keyboard" );
				break;
			case eSteeringController:
				printf( "Steering controller (Arcade Racer" );
				break;
			case eMultitap:
				printf( "Multitap (6Player)" );
				break;
            case eGun:
                printf( "Gun (Virtua Gun/Stunner)" );
                break;
            case eSaturn2Saturn:
                printf( "Saturn-to-Saturn cable" );
                break;
            case eMPEG:
                printf( "MPEG" );
                break;
            case eFDD:
                printf( "FDD" );
                break;
            case eModem:
                printf( "Modem" );
                break;
            case eXBAND:
                printf( "XBAND" );
                break;
			default:
				printf( "UNKNOWN : %c", cPeripheral);
				break;
		}

		++Counter;
        cPeripheral = ( *( p_SystemID->Peripherals + Counter ) );
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


void IPT_SetReleaseDate( struct SYSTEM_ID *p_SystemID, int p_Year, int p_Month,
                         int p_Day ) {
    memset(p_SystemID->ReleaseDate, ' ', RDATE_SIZE);
    sprintf(p_SystemID->ReleaseDate, "%d%02d%02d", p_Year, p_Month, p_Day);
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
void IPT_SetIPSize( struct SYSTEM_ID *p_SystemID, uint32_t p_Size ) {
    // TODO :  Add range validation and alignment
    memcpy(p_SystemID->IPSize, &p_Size, sizeof (p_SystemID->IPSize));
}

uint32_t IPT_GetIPSize( struct SYSTEM_ID *p_SystemID) {
    return *(uint32_t *)p_SystemID->IPSize;
}

void IPT_SetMasterStackAddress( struct SYSTEM_ID *p_SystemID,
                                uint32_t p_StackAddress ) {
    memcpy(p_SystemID->MasterStack, &p_StackAddress, sizeof (p_SystemID->MasterStack));
}

uint32_t IPT_GetMasterStackAddress( struct SYSTEM_ID *p_SystemID ) {
    return *(uint32_t *)p_SystemID->MasterStack;
}

void IPT_SetSlaveStackAddress( struct SYSTEM_ID *p_SystemID,
                               uint32_t p_StackAddress ) {
    memcpy(p_SystemID->SlaveStack, &p_StackAddress, sizeof (p_SystemID->SlaveStack));
}

uint32_t IPT_GetSlaveStackAddress( struct SYSTEM_ID *p_SystemID ) {
    return *(uint32_t *)p_SystemID->SlaveStack;
}

void IPT_SetFirstReadAddress( struct SYSTEM_ID *p_SystemID,
                              uint32_t p_FirstReadAddress ) {
    memcpy(p_SystemID->FirstReadAddress, &p_FirstReadAddress, sizeof (p_SystemID->FirstReadAddress));
}

uint32_t IPT_GetFirstReadAddress( struct SYSTEM_ID *p_SystemID ) {
    return *(uint32_t *)p_SystemID->FirstReadAddress;
}

void IPT_SetFirstReadSize( struct SYSTEM_ID *p_SystemID,
                           uint32_t p_FirstReadSize ) {
    memcpy(p_SystemID->FirstReadSize, &p_FirstReadSize, sizeof (p_SystemID->FirstReadSize));
}

uint32_t IPT_GetFirstReadSize( struct SYSTEM_ID *p_SystemID ) {
    return *(uint32_t *)p_SystemID->FirstReadSize;
}

int IPT_SetCompatibleAreas( struct SYSTEM_ID *p_SystemID, char * p_sAreas ) {
    if (p_sAreas == NULL) {
        fprintf (stderr,"ERROR : Area not set\n");
        return EXIT_FAILURE;
    }

    size_t len = strlen(p_sAreas);

    if (len > AREACODE_SIZE ) {
        fprintf (stderr,"WARNING : Area too long, it will be truncated\n");
    }

    // TODO : Add content validation ... not my war !

    memset(p_SystemID->CompatibleAreaSymbols, ' ', AREACODE_SIZE);

    memcpy( p_SystemID->CompatibleAreaSymbols, p_sAreas, len);

    return EXIT_SUCCESS;
}
