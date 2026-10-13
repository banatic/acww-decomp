/* func_020825e8 @ 0x020825e8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020825c8(unsigned short *p);
extern int func_020825d8(unsigned short *p);
int func_020825e8(unsigned short *p)
{
    int r = 0;
    int k = (*p & 0xf000) >> 12;
    switch (k) {
        case 0xe:
            r = func_020825d8(p);
            break;
        case 0xd:
            r = func_020825c8(p);
            break;
    }
    return r;
}
