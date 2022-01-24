#include <SystemID.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int IPT_DefaultSystemID( struct SYSTEM_ID *p_pSystemID, MAKER_ID p_MakerID )
{
	strncpy( p_pSystemID->HardwareID, "SEGA SEGASATURN ", 16 );

	if( p_MakerID == MAKER_ID_SEGA )
	{
		strncpy( p_pSystemID->MakerID, "SEGA ENTERPRISES", 16 );
		strncpy( p_pSystemID->ProductNumber, "GS-9099   ", 10 );
	}
	if( p_MakerID == MAKER_ID_3RDPARTY )
	{
		strncpy( p_pSystemID->MakerID, "SEGA TP KAISHA-A", 16 );
		strncpy( p_pSystemID->ProductNumber, "T-99901G  ", 10 );
	}

	strncpy( p_pSystemID->VersionNumber, "V0.000", 6 );
	strncpy( p_pSystemID->ReleaseDate, "19941122", 8 );
	strncpy( p_pSystemID->DeviceInformation, "CD-1/1  ", 8 );
	strncpy( p_pSystemID->CompatibleAreaSymbols, "E         ", 10 );
	strncpy( p_pSystemID->Space, "      ", 6 );
	strncpy( p_pSystemID->Peripherals, "JAK             ", 16 );
	memset( p_pSystemID->Title, ' ', sizeof( p_pSystemID->Title ) );
	strncpy( p_pSystemID->Title, "GAME", 4 );
	memset( p_pSystemID->Reserved1, ' ', sizeof( p_pSystemID->Reserved1 ) );

	p_pSystemID->IPSize = 0x00001800;
	p_pSystemID->MasterStack= 0;
	p_pSystemID->SlaveStack = 0;
	p_pSystemID->FirstReadAddress = 0x06004000;
	p_pSystemID->FirstReadSize = 0;
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
	while( Area != ' ' && Counter < 10 )
	{
		if( Counter != 0 )
		{
			printf( "\n                              " );
		}

		switch( Area )
		{
			case 'J':
			{
				printf( "Japan" );
				break;
			}
			case 'T':
			{
				printf( "Asia NTSC" );
				break;
			}
			case 'U':
			{
				printf( "North America" );
				break;
			}
			case 'B':
			{
				printf( "South America NTSC" );
				break;
			}
			case 'K':
			{
				printf( "Korea" );
				break;
			}
			case 'A':
			{
				printf( "East Asia PAL" );
				break;
			}
			case 'E':
			{
				printf( "Europe" );
				break;
			}
			case 'L':
			{
				printf( "South America PAL" );
				break;
			}
			default:
			{
				printf( "UNKNOWN" );
				break;
			}
		}
		++Counter;
		Area = ( *( p_SystemID->CompatibleAreaSymbols + Counter ) );
	}
	printf( "\n" );

	printf( "Peripherals:                  " );

	Counter = 0;
	Peripheral = *( p_SystemID->Peripherals );

	while( Peripheral != ' ' && Counter < 10 )
	{
		if( Counter !=0 )
		{
			printf( "\n                              " );
		}

		switch( Peripheral )
		{
			case 'J':
			{
				printf( "Control pad" );
				break;
			}
			case 'A':
			{
				printf( "Analogue controller" );
				break;
			}
			case 'M':
			{
				printf( "Mouse" );
				break;
			}
			case 'K':
			{
				printf( "Keyboard" );
				break;
			}
			case 'S':
			{
				printf( "Steering controller" );
				break;
			}
			case 'T':
			{
				printf( "Multitap" );
				break;
			}
			default:
			{
				printf( "UNKNOWN : %c", Peripheral);
				break;
			}
		}

		++Counter;
		Peripheral = ( *( p_SystemID->Peripherals + Counter ) );
	}
	printf( "\n" );

	printf( "Title:                        %.122s\n", p_SystemID->Title );
	printf( "IP Size:                      0x%08X\n", p_SystemID->IPSize );

	if( p_SystemID->MasterStack == 0 )
	{
		MasterStack = 0x06001000;
	}
	else
	{
		MasterStack = p_SystemID->MasterStack;
	}

	printf( "Master stack pointer address: 0x%08X\n", MasterStack );

	if( p_SystemID->SlaveStack == 0 )
	{
		SlaveStack = 0x06000D00;
	}
	else
	{
		SlaveStack = p_SystemID->SlaveStack;
	}

	printf( "Slave stack pointer address:  0x%08X\n", SlaveStack );

	printf( "1st read address:             0x%08X\n",
		p_SystemID->FirstReadAddress );

	printf( "1st read size:                0x%08X\n",
		p_SystemID->FirstReadSize );
}

void IPT_SetMasterStackAddress( struct SYSTEM_ID *p_pSystemID,
                               int p_StackAddress ) {
    p_pSystemID->MasterStack = p_StackAddress;
}

int IPT_SetTitle( struct SYSTEM_ID *p_pSystemID, char *p_pTitle ) {

    if (p_pTitle == NULL) {
        fprintf (stderr,"Title not set\n");
        return EXIT_FAILURE;
    }

    if (strlen(p_pTitle) >= TITLE_SIZE ) {
        fprintf (stderr,"Title cannot be set, too long\n");
        return EXIT_FAILURE;
    }

    strcpy( p_pSystemID->Title, p_pTitle);

    return EXIT_SUCCESS;
}
