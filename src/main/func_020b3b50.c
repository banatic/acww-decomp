/* func_020b3b50 @ 0x020b3b50, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021f4b44;
extern void *data_021f4bf4[];

void *func_020b3b50(unsigned short *p)
{
    unsigned int v;
    int flag;

    if (data_021f4b44 != 0) {
        flag = 0;
        v = *p;
        if (v >= 0x5000 && v <= 0x5021) {
            flag = 1;
        }

        if (flag) {
            v &= 0xfff;
        } else {
            v = -1;
        }

        if (v != -1) {
            return data_021f4bf4[v];
        }
    }
    return 0;
}
