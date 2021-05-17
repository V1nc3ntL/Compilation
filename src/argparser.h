#ifndef __ARG_PARSER_HH__
#define __ARG_PARSER_HH__
#define BANNER "\n***\tGraves\tLefebvre\tCompilateur minicc\t***\n"
#define ERROR -1

#define B_OPTION 0x01
#define H_OPTION 0x02
// More than one option
#define M_OPTION 0x03
#define O_OPTION 0x04
#define R_OPTION 0x08
#define S_OPTION 0x10
#define T_OPTION 0x20
#define V_OPTION 0x40
#define NO_OPTION 0x80
#define MIN_TRACE 0
#define MAX_TRACE 5
#define MIN_REG 4
#define MAX_REG 8
#define DEFAULT_OUT_NAME "out.s"
#define OPTIONS_DESC "\n*** Compilateur minicc : options\n\t-b:\tAffiche le nom du compilateur et de ses programmeurs\n\t-h:\tAffiche la liste des options\n\t-o\t\n\t-r\t\n\t-s\t\n\t-t\t\n\t-v\t\n"

#endif