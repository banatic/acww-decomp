/* func_ov052_022615d8 @ 0x022615d8, 0x100 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00, x1, x2;
} UnkStruct_022615d8;

extern int func_ov052_022604ec(void *self);
extern int func_ov052_022604a0(void *self);
extern int func_ov052_02260554(void *self);
extern UnkStruct_022615d8 *func_02095794(int);
extern int func_0201c378(void *self, int n);
extern void func_0201b458(UnkStruct_022615d8 *out, void *self, UnkStruct_022615d8 *in);
extern int func_02019e00(void *p);
extern int func_02019d0c(void *p, int r1, int r2, int r3, int s1, int s2, int s3, int s4, int s5, int s6, int s7);
extern void func_0201b044(void *p, UnkStruct_022615d8 *buf);
extern int func_020eaa6c(UnkStruct_022615d8 *buf, void *p);
extern void func_ov052_02261908(void *self, int flag);
extern unsigned short data_020c80f8;

int func_ov052_022615d8(void *self)
{
    UnkStruct_022615d8 src, buf;
    int t;

    if (func_ov052_022604ec(self)) {
        return 1;
    }
    if (func_ov052_022604a0(self)) {
        return 1;
    }
    if (func_ov052_02260554(self)) {
        return 1;
    }

    {
        UnkStruct_022615d8 *p = func_02095794(4);
        src.unk_00 = p->unk_00;
        src.x1 = p->x1;
        src.x2 = p->x2;
    }
    t = func_0201c378(self, 4);
    func_0201b458(&buf, self, &src);

    if (t > 0x4000) {
        if (func_02019e00((char *) self + 0x564) == 1) {
            func_02019d0c((char *) self + 0x564, 2, 1, 0, 0, 0x800, 0, 0, 0, data_020c80f8, 0);
        }
    } else {
        if (func_02019e00((char *) self + 0x564) == 2) {
            func_02019d0c((char *) self + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }

    func_0201b044((char *) self + 0x350, &buf);

    if (t <= 0x3000 || func_020eaa6c(&buf, (char *) self + 0x5c) != 0) {
        func_ov052_02261908(self, 1);
    }

    return 1;
}
