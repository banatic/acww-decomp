/* constellations_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b1768 @ 0x020b1768, 0xc bytes, Thumb
 * func_020b1758 @ 0x020b1758, 0x10 bytes, Thumb
 */

extern unsigned char data_020e42a0[];
extern int data_021f4b08[];

void *func_020b1768(unsigned int param)
{
    return &data_020e42a0[param * 8];
}

void func_020b1758(void)
{
    int *p = data_021f4b08;
    p[1] = 0;
    p[0] = 0;
}
