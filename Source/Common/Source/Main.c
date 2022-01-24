/* Main.c */
/* GNU General Public License v3.0 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "SystemID.h"

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

    size_t len = 0;

	printf( "SEGA Saturn SDK | IP Maker\n" );

    // Read Arguments from cli
    while((opt = getopt(argc, argv, ":i:o:vh")) != -1)
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

        if (pSystemIDFile != NULL) {
            fread(&SystemID, sizeof(SystemID), 1, pSystemIDFile);
            fclose(pSystemIDFile);

        } else {
            fprintf (stderr,"Cannot open file : %s\n", sInputFile);
            exit(EXIT_FAILURE);
        }
    }

    if (sOutputFile) {
        pSystemIDFile = fopen( sOutputFile, "w" );

        if (pSystemIDFile != NULL) {
            // Set Default attributes
            IPT_DefaultSystemID( &SystemID, MAKER_ID_SEGA );

            fwrite(&SystemID, sizeof(SystemID), 1, pSystemIDFile);
            fclose(pSystemIDFile);

        } else {
            fprintf (stderr,"Cannot open file : %s\n", sOutputFile);
            exit(EXIT_FAILURE);
        }
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

	return EXIT_SUCCESS;
}

void help() {

        printf("TODO\n");
        return;
}
