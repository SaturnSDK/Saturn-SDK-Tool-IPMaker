/* Main.c */
/* GNU General Public License v3.0 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "SystemID.h"
#include "SecurityCode.h"
#include "AreaCodes.h"

/* 2 defines */
/* 3 external declarations */
/* 4 typedefs */
/* 5 global variable declarations */
/* 6 function prototypes */

void help();

int main( int argc, char *argv[] )
{

    int opt;
	FILE *pSystemIDFile = NULL;
	struct SYSTEM_ID SystemID;

    char* sInputFile = NULL;
    char* sOutputFile = NULL;

    unsigned char bVerbose = 0;

    int startAddress = 0x0;
    unsigned char bSetStartAddress = 0;

    char* sTitle = NULL;
    char* sZone = NULL;

    size_t len = 0;

	printf( "SEGA Saturn SDK | IP Maker\n" );

    // Read Arguments from cli
    while((opt = getopt(argc, argv, ":i:o:s:vh")) != -1)
    {
        switch (opt) {
            case 'i':
                printf("input filename: %s\n", optarg);
                len = strlen(optarg);
                sInputFile = malloc(len+1);
                strcpy(sInputFile, optarg);
                break;
            case 'o':
                printf("output filename: %s\n", optarg);
                len = strlen(optarg);
                sOutputFile = malloc(len+1);
                strcpy(sOutputFile, optarg);
                break;
            case 's':
                printf("Start address: %s\n", optarg);
                startAddress = (int)strtol(optarg, NULL, 16);
                bSetStartAddress = 1;
                break;
            case 't':
                printf("Title: %s\n", optarg);
                len = strlen(optarg);
                sTitle = malloc(len+1);
                strcpy(sTitle, optarg);
                break;
            case 'z':
                printf("Zone: %s\n", optarg);
                len = strlen(optarg);
                sZone = malloc(len+1);
                strcpy(sZone, optarg);
                break;
            case 'v':
                printf("Verbose\n");
                bVerbose = 1;
                break;
            case ':':
                fprintf (stderr, "option needs a value\n");
                exit(EXIT_FAILURE);
                break;
            case 'h' :
                help();
                break;
            case '?':
            default:
                fprintf (stderr, "unknown option: %c\n", optopt);
                exit(EXIT_FAILURE);
                break;
        }
    }

    if (sInputFile != NULL) {
        pSystemIDFile = fopen( sInputFile, "r" );

        if (pSystemIDFile == NULL) {
            fprintf (stderr,"Cannot open file : %s\n", sInputFile);
            exit(EXIT_FAILURE);
        }

        fread(&SystemID, sizeof(SystemID), 1, pSystemIDFile);
        fclose(pSystemIDFile);
    } else {
        // Set Default attributes
        IPT_DefaultSystemID( &SystemID, MAKER_ID_SEGA );
    }

    //
    // SETTERS !
    //

    if (bSetStartAddress) {
        IPT_SetMasterStackAddress(&SystemID, startAddress);
    }

    if (sTitle) {
        IPT_SetTitle(&SystemID, sTitle);
    }

    if (sZone) {
        IPT_SetCompatibleAreas(&SystemID, sZone);
    }

    if (sOutputFile) {
        pSystemIDFile = fopen( sOutputFile, "w" );

        if (pSystemIDFile == NULL) {
            fprintf (stderr,"Cannot open file : %s\n", sOutputFile);
            exit(EXIT_FAILURE);
        }

        // Write System ID
        fwrite(&SystemID, sizeof(SystemID), 1, pSystemIDFile);

        // Write Security Code
        fwrite(sys_sec_obj, sys_sec_obj_len, 1, pSystemIDFile);

        // Write Area Codes
        char Area = *( SystemID.CompatibleAreaSymbols );
        int Counter = 0;
        while( Area != ' ' && Counter < 10 ) {
            if( Counter != 0 ) {
                printf( "\n                              " );
            }

            switch( Area ) {
                case 'J':
                    fwrite(sys_areb_obj, sys_areb_obj_len, 1, pSystemIDFile);
                    break;
                case 'T':
                    fwrite(sys_aret_obj, sys_aret_obj_len, 1, pSystemIDFile);
                    break;
                case 'U':
                    fwrite(sys_areu_obj, sys_areu_obj_len, 1, pSystemIDFile);
                    break;
                case 'B':
                    fwrite(sys_areb_obj, sys_areb_obj_len, 1, pSystemIDFile);
                    break;
                case 'K':
                    fwrite(sys_arek_obj, sys_arek_obj_len, 1, pSystemIDFile);
                    break;
                case 'A':
                    fwrite(sys_area_obj, sys_area_obj_len, 1, pSystemIDFile);
                    break;
                case 'E':
                    fwrite(sys_aree_obj, sys_aree_obj_len, 1, pSystemIDFile);
                    break;
                case 'L':
                    fwrite(sys_arel_obj, sys_arel_obj_len, 1, pSystemIDFile);
                    break;
                default:
                    printf( "UNKNOWN" );
                    break;
            }
            ++Counter;
            Area = ( *( SystemID.CompatibleAreaSymbols + Counter ) );
        }

        fclose(pSystemIDFile);
    }

    if (!sInputFile && !sOutputFile) {
        fprintf (stderr,"Not enough arguments\n");
        help();
        exit(EXIT_FAILURE);
    }

    if(bVerbose) {
        printf("System ID Information\n");
        printf("---------------------\n");

        IPT_PrintSystemID(&SystemID);
    }

    if(sInputFile) {
        free(sInputFile);
    }

    if(sOutputFile) {
        free(sOutputFile);
    }

    if(sTitle) {
        free(sTitle);
    }

    if (sZone) {
        free(sZone);
    }

	return EXIT_SUCCESS;
}

void help() {

        printf("TODO\n");
        return;
}
