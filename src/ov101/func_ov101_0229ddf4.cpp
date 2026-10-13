/* func_ov101_0229ddf4 @ 0x0229ddf4, 0xa0 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220919c(void *);
extern "C" int func_0206fe54(int);
extern "C" void func_ov002_02209eb8(void *);
extern "C" int func_ov101_0229c2ac(void *, int);
extern "C" void func_ov002_0220ad18(void *, void *);
extern "C" void func_ov094_0229a850(void *, int, int);
extern "C" void func_ov094_0229b738(void *, int, int);
extern "C" void func_ov094_02299d84(void *, int);

extern "C" int func_ov101_0229ddf4(unsigned char *self)
{
    func_ov002_0220919c(self + 0x2300);
    if (func_ov101_0229c2ac(self, 1) == 0) {
        return 1;
    }

    if (func_0206fe54((*(int (**)(void *))((char *) *(void **) (self + 0x21b4) + 8))(self + 0x21b4)) != 0) {
        func_ov002_02209eb8(self + 0x229c);
    }

    if (func_ov101_0229c2ac(self, 2) != 0) {
        func_ov002_0220ad18(self + 0x2810, *(void **) (self + 0x98));
        int n = *(int *) (self + 0x98) - 0x10;
        func_ov094_0229a850(self + 0xf4, 0, n);
        func_ov094_0229b738(self + 0xb54, 0, n);
        func_ov094_02299d84(self + 0xb7c, n);
    }
    return 1;
}
