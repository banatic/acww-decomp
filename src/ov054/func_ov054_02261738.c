/* func_ov054_02261738 @ 0x02261738, 0x22 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov054_02260498(int);
extern void func_020a190c(void);
extern void func_ov054_02261cc4(void *p, int n);

struct func_ov054_02261738_data {
    char pad_00[0xb0];
    int unk_B0;
};

void func_ov054_02261738(struct func_ov054_02261738_data *p)
{
    if (func_ov054_02260498(p->unk_B0)) {
        func_020a190c();
        func_ov054_02261cc4(p, 9);
    }
}
