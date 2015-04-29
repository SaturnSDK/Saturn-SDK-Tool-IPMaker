#include <stdio.h>
#include <SystemID.h>

int main( int p_Argc, char **p_ppArgv )
{
	FILE *pSystemIDFile;
	struct SYSTEM_ID SystemID;

	printf( "SEGA Saturn SDK | IP Maker\n" );

	IPT_DefaultSystemID( &SystemID, MAKER_ID_SEGA );

	pSystemIDFile = fopen( "SystemID", "w" );

	fwrite( &SystemID, sizeof( SystemID ), 1, pSystemIDFile );

	fclose( pSystemIDFile );

	printf( "System ID Information\n" );
	printf( "---------------------\n" );

	IPT_PrintSystemID( SystemID );

	return 0;
}

