/* func_02078380 @ 0x02078380, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020778b0(short *dest, unsigned short src);

void func_02078380(short *dest, char value, unsigned short *src)
{
    int i;
    unsigned short *p = src;
    for (i = 0; i < 4; i++) {
        func_020778b0(&dest[i], *p);
        p++;
    }
    ((char *) dest)[8] = value;
}
