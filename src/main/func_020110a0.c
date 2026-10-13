/* func_020110a0 @ 0x020110a0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020110a0(void *s, short *src)
{
    short *dst;
    int off0;
    int off1;

    dst = (short *) ((char *) s + 0x8c);
    off0 = 0;
    off1 = 2;

    dst[1] = *(short *) ((char *) src + off0);
    *(short *) ((char *) s + 0x94) = *(short *) ((char *) dst + off1);
}
