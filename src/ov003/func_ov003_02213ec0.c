/* func_ov003_02213ec0 @ 0x02213ec0, 0xb4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f28(void *, int);
extern int func_ov003_0220c934(void *);
extern void func_0200f27c(void *, int);
extern void func_0200f328(void *, int);
extern void func_0205eae0(void *, int, int, int);
extern int func_0200fa1c(void *, void *, void *, void *, void *);
extern int func_020310d0(void *, void *, int);
extern char data_ov003_02238114[];

int func_ov003_02213ec0(char *self)
{
    int len;
    char buf[12];

    if (func_02056f28(self + 0x2d0, 4) == 0) {
        goto fail;
    }
    if (func_ov003_0220c934(self) == 0) {
        goto else_block;
    }

    func_0200f27c(self, 9);
    func_0200f328(self, 0x846);
    *(int *) (self + 0x2e0) = 0;
    func_0205eae0(self + 0x5a0, 4, 3, 1);
    return 1;

else_block:
    func_0200fa1c(buf, self, self + 0x5c, self + 0x8e, data_ov003_02238114);
    if (func_020310d0(buf, &len, 0x19) < 0x400) {
        goto fail;
    }

    func_0200f27c(self, 9);
    func_0200f328(self, 0x846);
    *(int *) (self + 0x2e0) = 0;
    func_0205eae0(self + 0x5a0, 4, 3, 1);
    return 1;

fail:
    return 0;
}
