/* func_ov054_02261fd0 @ 0x02261fd0, 0x58 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c0e0(void *);
extern int func_0201c040(void *, int *, int *);
extern int func_020a7278(int);
extern void func_0201c054(void *, int, void *, int);
extern void func_ov054_02262528(void *, int);

struct G020ccf94 {
    unsigned char pad_00[0x64];
    void *unk_64;
};
extern struct G020ccf94 *data_020ccf94;

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
    if (!func_020a7278(a)) {
        goto ret;
    }
    func_0201c054(self, 1, data_020ccf94->unk_64, 4);
    func_ov054_02262528(self, 2);
ret:
    return 1;
}
