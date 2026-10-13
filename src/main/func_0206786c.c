/* func_0206786c @ 0x0206786c, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct VT {
    unsigned char pad_00[0x68];
    int (*unk_68)(void *);
} VT;
typedef struct UnkStruct_0206786c {
    VT *vt;
} UnkStruct_0206786c;

typedef struct UnkStruct_0206786c_2 {
    unsigned char pad_00[0x14a8];
    UnkStruct_0206786c *unk_14A8;
    unsigned char pad_14AC[0x1d2c - 0x14a8 - 4];
    unsigned char unk_1D2C[0x1e75 - 0x1d2c];
    unsigned char unk_1E75;
    unsigned char unk_1E76;
} UnkStruct_0206786c_2;

extern int func_020984e8(void);
extern void func_020a8c1c(void *);
extern int func_02099348(int, void *);
extern void func_0207ee78(int, void *);

int func_0206786c(UnkStruct_0206786c_2 *self)
{
    int ret;
    int x;
    UnkStruct_0206786c *o;
    int r;
    ret = 1;
    if (self->unk_1E75 == 0) {
        x = func_020984e8();
        func_020a8c1c(self->unk_1D2C);
        if (func_02099348(x, self->unk_1D2C) == 0) {
            o = self->unk_14A8;
            r = o->vt->unk_68(o);
            if (r != 0) {
                func_0207ee78(r, self->unk_1D2C);
                self->unk_1E76 = (unsigned char) ret;
            } else {
                ret = 0;
            }
        }
        self->unk_1E75 = 1;
    }
    return ret;
}
