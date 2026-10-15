/* func_ov052_0226170c @ 0x0226170c, 0xc8 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov052_022604ec(void *arg0);
extern int func_ov052_022604a0(void *self);
extern int func_ov052_02260554(void *self);
extern void *func_02095794(int kind);
extern int func_0201c378(void *self, int kind);
extern int func_0201c2c8(void *self, int kind);
extern int func_020e8b4c(int value, int arg);
extern void func_0201b458(void *dst, void *self, void *src);
extern int func_020eaa2c(void *dst, void *self);
extern void func_ov052_02261908(void *self, int kind);
extern void func_0201aff4(void *self, int arg);
extern int func_02019e00(void *self);
extern int func_02019de8(void *self);

int func_ov052_0226170c(void *self)
{
    int r6, r4;
    int tmp[3];
    int local[3];

    if (func_ov052_022604ec((void *) self)) {
        return 1;
    }
    if (func_ov052_022604a0(self)) {
        return 1;
    }
    if (func_ov052_02260554(self)) {
        return 1;
    }

    {
        void *p = func_02095794(4);
        tmp[0] = *(int *) p;
        tmp[1] = *(int *) ((char *) p + 4);
        tmp[2] = *(int *) ((char *) p + 8);
    }

    r6 = func_0201c378(self, 4);
    r4 = func_0201c2c8(self, 4);

    func_020e8b4c(*(short *) ((char *) self + 0x8e), r4);

    func_0201b458(&local[0], self, &tmp[0]);

    if (r6 > 0x3000) {
        if (func_020eaa2c(&local[0], (char *) self + 0x5c)) {
            func_ov052_02261908(self, 3);
            return 1;
        }
    }

    (func_0201aff4((char *) self + 0x350, r4), (int) ((char *) self + 0x350));
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564)) {
            func_ov052_02261908(self, 1);
        }
    }
    return 1;
}
