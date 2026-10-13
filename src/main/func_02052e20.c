/* func_02052e20 @ 0x02052e20, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_020dcfe0[];

unsigned char func_02052e20(int *p)
{
    int v = *p;
    if (v < 3) {
        return data_020dcfe0[v][0x10];
    } else {
        return 0;
    }
}
