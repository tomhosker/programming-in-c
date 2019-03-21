/* MY FILE */
/* A key to the various control codes used throughout "main.c". */

#define RED_AN 0x81
#define GREEN_AN 0x82
#define YELLOW_AN 0x83
#define BLUE_AN 0x84
#define MAGENTA_AN 0x85
#define CYAN_AN 0x86
#define WHITE_AN 0x87

#define SINGLE_HEIGHT 0x8C
#define DOUBLE_HEIGHT 0x8D

#define RED_GR 0x91
#define GREEN_GR 0x92
#define YELLOW_GR 0x93
#define BLUE_GR 0x94
#define MAGENTA_GR 0x95
#define CYAN_GR 0x96
#define WHITE_GR 0x97

#define CONTIGUOUS_GR 0x99
#define SEPARATED_GR 0x9A

#define BLACK_BG 0x9C
#define NEW_BG 0x9D

#define HOLD_GR 0x9E
#define RELEASE_GR 0x9F

#define SPACE 0xA0

#define FIRST_CONTROL 0x80
#define FIRST_ANFGC RED_AN /* "FIRST_ANFGC", i.e. the first colour of the block of Alpha-Numeric ForeGround Colours. */
#define LAST_ANFGC WHITE_AN
#define FIRST_GR RED_GR /* "FIRST_GR", i.e. the first of the block of graphics commands. */
#define LAST_GR SEPARATED_GR
#define FIRST_GR_CC RED_GR /* "FIRST_GR_CC", i.e. the first of the block of graphics Colour Codes. */
#define LAST_GR_CC WHITE_GR
#define FIRST_ASCII_A SPACE /* "FIRST_ASCII_A", i.e. the first character of the first block of ASCII characters. */
#define LAST_ASCII_A 0xDA
#define FIRST_ASCII_B 0xE1  /* "FIRST_ASCII_B", i.e. the first character of the second block of ASCII characters. */
#define LAST_ASCII_B 0xFA
#define FIRST_NON_ASCII_A 0xDB
#define LAST_NON_ASCII_A 0xE0
#define FIRST_NON_ASCII_B 0xFB
