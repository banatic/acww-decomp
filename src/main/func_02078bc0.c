/* func_02078bc0 @ 0x02078bc0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9b9c(void *ptr);
extern void *data_021c9ac0;

void func_02078bc0(void *param)
{
    void **r5;
    void **r7;
    int r4;
    void **r6;
    void *r0;
    void *sp_val;

    r7 = param;
    r5 = data_021c9ac0;
    r4 = 0;
    sp_val = 0;
    while (r4 < 8) {
        r6 = r7 + r4;
        r0 = r7[r4];
        if (r0 != 0) {
            func_020e9b9c(r0);
            r6[0] = sp_val;
        }
        r4++;
    }
    if (r5 != 0) {
        func_020e9b9c(r5);
    }
}
