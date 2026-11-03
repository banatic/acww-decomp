/* scene_query_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b6598 @ 0x020b6598, 0x14 bytes, Thumb
 * func_020b6590 @ 0x020b6590, 0x8 bytes, Thumb
 */

extern unsigned char func_020b65ac(unsigned int);
extern unsigned char data_021ebcc8[];
extern int data_021f6a14;

int func_020b6598(void)
{
    unsigned char *ptr;
    unsigned int value;

    ptr = (unsigned char *) data_021ebcc8;
    value = ptr[8];
    value = value << 0x18;
    value = value >> 0x1a;
    return func_020b65ac(value);
}

int func_020b6590(void)
{
    return (int) &data_021f6a14;
}
