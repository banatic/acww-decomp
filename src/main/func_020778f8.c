/* func_020778f8 @ 0x020778f8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(int arg, short *buf, int size);

short func_020778f8(int arg)
{
    short buf;
    MI_CpuCopy8(arg, &buf, 2);
    return buf;
}
