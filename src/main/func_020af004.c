/* func_020af004 @ 0x020af004, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x5A];
    unsigned short : 9;
    unsigned short bf : 2;
    unsigned short : 5;
} BitFieldStruct;

void func_020af004(BitFieldStruct *s, unsigned short val)
{
    unsigned short tmp = val & 3;
    s->bf = tmp;
}
