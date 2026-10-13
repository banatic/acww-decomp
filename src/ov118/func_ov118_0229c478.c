/* func_ov118_0229c478 @ 0x0229c478, 0x98 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern int func_0206fe60(void);
extern int func_ov090_022990e0(void);
extern int func_ov118_0229c438(void *self, int arg);

typedef struct {
    unsigned char pad_00[2];
    unsigned short val;
} GStruct;
extern GStruct data_021fbe40;

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
} SelfType;

int func_ov118_0229c478(SelfType *self)
{
    int r4;
    unsigned short w;

    func_0206f58c();
    if (func_0206f56c() != 0) {
        return func_ov118_0229c438(self, 7);
    }

    if (self->unk_8D != 0 && self->unk_8D != 3 && self->unk_8D != 10) {
        return 0;
    }

    r4 = -1;
    if (func_0206fe60()) {
        r4 = func_ov090_022990e0();
    } else {
        w = data_021fbe40.val;
        if ((w & 0x400) || (w & 0x2)) {
            r4 = 7;
        } else if (w & 0x800) {
            r4 = 0;
        } else if (w & 0x4) {
            r4 = 4;
        }
    }

    return func_ov118_0229c438(self, r4);
}
