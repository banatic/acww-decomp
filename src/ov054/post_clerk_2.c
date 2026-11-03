/* post_clerk_2: 4 functions, module ov054
 * mwccarm 1.2/base -O4,s
 * func_ov054_02262028 @ 0x02262028, 0x4 bytes, Thumb
 * func_ov054_02261fd0 @ 0x02261fd0, 0x58 bytes, Thumb
 * func_ov054_02261fcc @ 0x02261fcc, 0x4 bytes, Thumb
 * func_ov054_02261fc8 @ 0x02261fc8, 0x4 bytes, Thumb
 */

struct G020ccf94 {
    unsigned char pad_00[0x64];
    void *unk_64;
};

extern int func_0201c0e0(void *);
extern int func_0201c040(void *, int *, int *);
extern int func_020a7278(void);
extern void func_0201c054(void *, int, void *, int);
extern void func_ov054_02262528(void *, int);
extern struct G020ccf94 *data_020ccf94;

int func_ov054_02262028(void)
{
    return 1;
}

int func_ov054_02261fd0(void *self)
{
    int a, b;
    if (!func_0201c0e0(self)) {
        goto ret;
    }
    a = 4;
    b = 4;
    if (!func_0201c040(self, &a, &b)) {
        goto ret;
    }
    if (a != 4) {
        goto ret;
    }
    if (!func_020a7278()) {
        goto ret;
    }
    func_0201c054(self, 1, data_020ccf94->unk_64, 4);
    func_ov054_02262528(self, 2);
ret:
    return 1;
}

int func_ov054_02261fcc(void)
{
    return 1;
}

int func_ov054_02261fc8(void)
{
    return 1;
}
