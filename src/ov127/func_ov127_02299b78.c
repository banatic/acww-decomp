/* func_ov127_02299b78 @ 0x02299b78, 0x44 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov127_02299cd8(void *, unsigned char, void *, int);
extern void *data_ov127_0229a0fc[];

int func_ov127_02299b78(unsigned char *r0)
{
    if (r0[0x2836] != 0) {
        r0[0x2836]--;
        func_ov127_02299cd8(r0, r0[0x2835], data_ov127_0229a0fc[r0[0x2836]], 0);
    }
    if (r0[0x2836] == 0) {
        return 1;
    } else {
        return 0;
    }
}
