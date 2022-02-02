/* Main.c */
/* GNU General Public License v3.0 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "SystemID.h"
#include "SecurityCode.h"
#include "AreaCodes.h"
#include "SystemInit.h"
#include "SmpSys.h"

static char sEmptyBuffer[0x20] = { 0 };

void help();

int main( int argc, char *argv[] )
{

    int opt;
	FILE *pSystemIDFile = NULL;
	struct SYSTEM_ID SystemID;

    char* sInputFile = NULL;
    char* sOutputFile = NULL;

    unsigned char bVerbose = 0;

    uint32_t startAddress = 0x0;
    unsigned char bSetStartAddress = 0;

    char* sTitle = NULL;
    char* sZone = NULL;

    size_t len = 0;

    MAKER_ID type = MAKER_ID_SEGA;

	printf( "SEGA Saturn SDK | IP Maker\n" );

    // Read Arguments from cli
    while((opt = getopt(argc, argv, ":i:o:s:t:z:p:vh")) != -1)
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
                startAddress = (uint32_t)strtoll(optarg, NULL, 16);
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
            case 'p':
                printf("Profile: %s\n", optarg);
                type = (MAKER_ID)optarg[0];
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
        IPT_DefaultSystemID( &SystemID, type );
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
        char cArea = *( SystemID.CompatibleAreaSymbols );
        int Counter = 0;
        while( cArea != ' ' && Counter < 10 ) {
            if( Counter != 0 ) {
                printf( "\n                              " );
            }

            switch( (Area)cArea ) {
                case eJapan:
                    fwrite(sys_arej_obj, sys_arej_obj_len, 1, pSystemIDFile);
                    break;
                case eAsiaNTSC:
                    fwrite(sys_aret_obj, sys_aret_obj_len, 1, pSystemIDFile);
                    break;
                case eNorthAmerica:
                    fwrite(sys_areu_obj, sys_areu_obj_len, 1, pSystemIDFile);
                    break;
                case eSouthAmericaNTSC:
                    fwrite(sys_areb_obj, sys_areb_obj_len, 1, pSystemIDFile);
                    break;
                case eKorea:
                    fwrite(sys_arek_obj, sys_arek_obj_len, 1, pSystemIDFile);
                    break;
                case eEastAsiaPAL:
                    fwrite(sys_area_obj, sys_area_obj_len, 1, pSystemIDFile);
                    break;
                case eEurope:
                    fwrite(sys_aree_obj, sys_aree_obj_len, 1, pSystemIDFile);
                    break;
                case eSouthAmericaPAL:
                    fwrite(sys_arel_obj, sys_arel_obj_len, 1, pSystemIDFile);
                    break;
                default:
                    printf( "UNKNOWN AREA : %c", cArea);
                    break;
            }
            ++Counter;
            cArea = ( *( SystemID.CompatibleAreaSymbols + Counter ) );
        }

        if (Counter == 0) {
            fprintf (stderr,"No compatible area specified");
            exit(EXIT_FAILURE);
        }

        // Write AIP
        fwrite(sys_init_obj, sys_init_obj_len, 1, pSystemIDFile);

        // Write SmpSys
       // fwrite(smpsys_text, smpsys_text_len, 1, pSystemIDFile);
        fwrite(test_text, test_text_len, 1, pSystemIDFile);

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
