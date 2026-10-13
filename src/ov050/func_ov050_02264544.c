/* func_ov050_02264544 @ 0x02264544, 0xf4 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov050_022606b4(char *self);
extern int func_ov050_022605c0(char *self);
extern int func_ov050_02260528(char *self);
extern int func_ov050_02260718(char *self);
extern int *func_02095794(int a);
extern int func_0201c378(char *self, int a);
extern int func_0201c2c8(char *self, int a);
extern void func_020e8b4c(short s, int a);
extern int func_ov050_02260498(char *self);
extern void func_0201b458(void *dst, char *src, int *data);
extern int func_020960f8(int a, int b);
extern int func_020eaa2c(void *a, char *b);
extern void func_ov050_02264834(char *self, int a);
extern void func_0201aff4(void *a, int b);
extern int func_02019e00(void *a);
extern int func_02019de8(void *a);

int func_ov050_02264544(char *self)
{
    int *p;
    int arr[3];
    int r4, r6, r7;
    struct {
        int a, b, c, d;
    } ls;

    if (func_ov050_022606b4(self) != 0) {
        return 1;
    }
    if (func_ov050_022605c0(self) != 0) {
        return 1;
    }
    if (func_ov050_02260528(self) != 0) {
        return 1;
    }
    if (func_ov050_02260718(self) != 0) {
        return 1;
    }

    p = func_02095794(4);
    arr[0] = p[0];
    arr[1] = p[1];
    arr[2] = p[2];

    r6 = func_0201c378(self, 4);
    r4 = func_0201c2c8(self, 4);
    func_020e8b4c(*(short *) (self + 0x8e), r4);
    r7 = func_ov050_02260498(self);
    func_0201b458(&ls, self, arr);

    if (func_020960f8(0x8b, 4) != 0 || func_020960f8(0x8c, 4) != 0) {
        return 1;
    }

    if (r6 > r7) {
        if (func_020eaa2c(&ls, self + 0x5c) != 0) {
            func_ov050_02264834(self, 3);
            return 1;
        }
    }

    func_0201aff4((void *) (self + 0x350), r4);
    if (func_02019e00((void *) (self + 0x564)) == 3) {
        if (func_02019de8((void *) (self + 0x564)) != 0) {
            func_ov050_02264834(self, 1);
        }
    }
    return 1;
}
