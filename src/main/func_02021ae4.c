/* func_02021ae4 @ 0x02021ae4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02021ae4 {
    unsigned short val;
} *func_02081abc(int);

int func_02021ae4(int a, int b)
{
    return func_02081abc(b)->val != 0xfff1;
}
