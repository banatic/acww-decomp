/* func_ov106_0229ea08 @ 0x0229ea08, 0xd4 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229af40(void *a, int b);
extern void func_ov094_0229bbd8(void *a, int b);
extern void func_ov094_0229a2b0(void *a, int b);
extern void func_ov002_02209e18(void *a);
extern void func_ov002_02209984(void *a, int b, int c, int d);
extern void func_0206e2ec(void *a, int b);
extern void func_02066650(void *a);
extern int func_020984e8(void);
extern unsigned char *func_020989b4(int object);
extern unsigned char *func_02098090(unsigned char *a, int b);
extern int func_02066830(void *a, unsigned char *b);
extern void func_ov106_0229c354(void *a, int b);

void func_ov106_0229ea08(unsigned char *self)
{
    int i;
    unsigned char *p;

    *(int *) (self + 0x94) = 0;
    func_ov094_0229af40(self + 0xf8, 2);
    func_ov094_0229bbd8(self + 0xb58, 1);
    func_ov094_0229a2b0(self + 0xb80, 6);
    self[0xb6] = 0x20;
    func_ov002_02209e18(self + 0x2288);
    self[0xb4] = 0;
    self[0xb8] = 0xb;
    func_ov002_02209984(self + 0x2304, 3, 0, 0);
    func_0206e2ec(self + 0x2814, 3);
    for (i = 0; i < 10; i++) {
        func_02066650(self + 0x2bb4 + i * 0x100);
    }
    p = func_02098090(func_020989b4(func_020984e8()), 0);
    for (i = 0; i < 10; i++) {
        func_02066830(self + 0x2bb4 + i * 0x100, p);
        p += 0x100;
    }
    func_ov106_0229c354(self, 0x4000);
    self[0xbf] = 0;
}
