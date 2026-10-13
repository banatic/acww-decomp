/* func_ov113_0229a958 @ 0x0229a958, 0xdc bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov113_02299da4(unsigned char *self, int a);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *p);
extern void func_02088df8(int a0, void *a1, int a2, void *a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10,
                          int a11);
extern int func_ov002_02207f54(unsigned char *self);
extern void func_ov113_0229aa34(unsigned char *self, int a, void *b);
extern unsigned char data_ov113_0229ac60[];
extern unsigned char data_ov113_0229ac80[];

int func_ov113_0229a958(unsigned char *self)
{
    int r4;
    void *r6;
    int mode1;
    int mode2;

    if (func_ov113_02299da4(self, 8) == 0) {
        return 1;
    }
    if (func_0206fe54() != 0) {
        func_ov002_02209eb8(self + 0x2b20);
    }

    r4 = 0x80;
    r6 = (void *) ((char *) *(char **) (self + 0x94) + 0x60);
    mode1 = 0xa;
    mode2 = 0xa;
    if (func_ov113_02299da4(self, 2) != 0) {
        mode1 = 0xb;
    } else if (func_ov113_02299da4(self, 4) != 0) {
        mode2 = 0xb;
    }

    func_02088df8(0, data_ov113_0229ac60, 0x80, r6, mode1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(0, data_ov113_0229ac80, 0x80, r6, mode2, 1, 0x1000, 0x1000, 0, -1, 0, 0);

    r4 += self[0x9e];
    if (func_ov113_02299da4(self, 0x100) != 0) {
        r4 += func_ov002_02207f54(self);
    }

    func_ov113_0229aa34(self, r4, r6);
    return 1;
}
