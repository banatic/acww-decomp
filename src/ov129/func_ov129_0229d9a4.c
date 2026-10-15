/* func_ov129_0229d9a4 @ 0x0229d9a4, 0xa0 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern int func_ov129_0229b7ec(void *, int);
extern void func_ov002_0220ad18(void *, unsigned int);
extern void func_ov127_02299dc0(void *, int);
extern void func_ov127_02299de8(void *, unsigned int, int);
extern int func_ov127_02299d64(void *, int);

int func_ov129_0229d9a4(char *self)
{
    if (func_0206fe54()) {
        func_ov002_02209eb8(self + 0x3a0);
    }
    if (func_ov129_0229b7ec(self, 8)) {
        func_ov002_0220ad18(self + 0x1d4, *(unsigned int *) (self + 0xa0));
    }
    if (func_0206fe54()) {
        if (func_ov129_0229b7ec(self, 0x10)) {
            func_ov127_02299dc0(self + 0x734, 0);
        }
    }
    if (func_ov129_0229b7ec(self, 1)) {
        func_ov127_02299de8(self + 0x734, *(unsigned int *) (self + 0x9c), 5);
    }
    if (*(unsigned char *) (self + 0xb3) != 0xff) {
        if (func_ov129_0229b7ec(self, 0x80)) {
            func_ov127_02299d64(self + 0x734, *(unsigned char *) (self + 0xb3));
        }
    }
    return 1;
}
