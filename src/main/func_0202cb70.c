/* func_0202cb70 @ 0x0202cb70, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c1d18[];
extern int func_0202d6e4(unsigned char *data_021c1d18, int size);
extern int func_0202cca4(int a, int b, int c, int idx, int d);
extern void MI_CpuCopy8(void *dst, const void *src, int size);

extern unsigned char data_020c8950[];

int func_0202cb70(int p0, int *p1, int p2, int p3, int p4)
{
    int res = 0;
    int i, marker;

    MI_CpuCopy8((void *) data_020c8950, data_021c1d18, 5);
    i = res;
    marker = i;

    for (; i < 5; i++) {
        int idx = func_0202d6e4(data_021c1d18, 5);
        if (idx < 0 || idx >= 5) {
            break;
        }
        if (func_0202cca4(p0, p2, p3, idx, p4) == 1) {
            *p1 = idx;
            res = 1;
            break;
        } else {
            data_021c1d18[idx] = marker;
        }
    }

    return res;
}
