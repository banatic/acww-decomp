/* func_020372bc @ 0x020372bc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020372bc(unsigned short *arg0);

void func_020372bc(unsigned short *arg0)
{
    unsigned int val;
    unsigned char val2;

    val = 0xffff;
    *(unsigned short *) (arg0 + 6) = (unsigned short) val;
    *(unsigned int *) (arg0 + 4) = 0x18;
    val2 = 0;
    *(unsigned char *) ((unsigned char *) arg0 + 14) = val2;
    *(unsigned char *) ((unsigned char *) arg0 + 15) = val2;
    *(unsigned char *) ((unsigned char *) arg0 + 16) = val2;
    return;
}
