/* func_020e9a68 @ 0x020e9a68, 0x4c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int NNS_FndAdjustFrmHeap(int);
extern int func_020e9cdc(int, int, int);

int func_020e9a68(int *r6)
{
    int r4;
    int r5;
    int r0;

    r4 = NNS_FndAdjustFrmHeap(r6[5]);
    if (r4 == 0) {
        return 0;
    }
    r5 = r4 + 0x18;
    r0 = func_020e9cdc(r6[3], (int) r6, r5);
    if (r0 < 0) {
        return 0;
    }
    r6[2] = r4;
    return r5;
}
