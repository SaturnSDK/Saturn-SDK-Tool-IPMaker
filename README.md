# Saturn-SDK-Tool-IPMaker
A
tool to generate IP files via the command line

|            Structure :             |
|:----------------------------------:|
|       System ID : 100H Bytes       |
|     Security Code : D00H Bytes     |
| Area Code Group : 20H - 100H Bytes |
|             AIP : XXX              |
|            SmpSys : XXX            |


## Usage : 

< cmd > -v -o ./IP.BIN -s 0x06004000 -t Test -p 2

## Profiles :

0 : SEGA
1 : 3rd party
1 : Custom 3rd Party

## TODO :

* Add missing Setters,
* Add help for command line arguments,
* Document the binary blobs, how to generate them,
* Figure out the System Init part, it is a mystery
* IP Size remains to understand

