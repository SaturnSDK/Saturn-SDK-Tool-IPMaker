/* Main.c */
/* GNU General Public License v3.0 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "SystemID.h"

/* 2 defines */
/* 3 external declarations */
/* 4 typedefs */
/* 5 global variable declarations */
/* 6 function prototypes */



int main( int argc, char *argv[] )
{
	FILE *pSystemIDFile = NULL;
	struct SYSTEM_ID SystemID;

	printf( "SEGA Saturn SDK | IP Maker\n" );

    // Set Default attributes
	IPT_DefaultSystemID( &SystemID, MAKER_ID_SEGA );



	pSystemIDFile = fopen( "SystemID", "w" );

    if (pSystemIDFile != NULL) {

        fwrite(&SystemID, sizeof(SystemID), 1, pSystemIDFile);

        fclose(pSystemIDFile);

        printf("System ID Information\n");
        printf("---------------------\n");

        IPT_PrintSystemID(&SystemID);

    } else {
        printf("Cannot open file!\n");

        exit(EXIT_FAILURE);
    }
	return EXIT_SUCCESS;
}

