/* func_ov003_022107ac @ 0x022107ac, 0x104 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void *data_021c80bc;
extern void func_020912d4(int a, void *b, void *c, int d);
extern int func_02073908(void *a, int b);
extern void func_ov003_022211bc(int a, int *b);
extern void func_ov003_02221150(int a, int *b);
extern unsigned short *func_0204f5a8(void *a, void *b, int c);
extern void func_0200f268(void *self, int a);
extern void func_0200f328(void *self, int a);
extern void func_0200f27c(void *self, int a);
extern void func_02010f5c(void *self);

typedef struct {
    int pad_00;
    int a;
    int b;
    int c;
} UnkStruct_022107ac;

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x2d8 - 0x90];
    unsigned int unk_2D8;
    char pad_2DC[0x704 - 0x2dc];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    UnkStruct_022107ac sub;
    char pad_7E4[0x800 - 0x7e4];
    int unk_800;
} UnkStruct_022107ac_2;

void func_ov003_022107ac(UnkStruct_022107ac_2 *self)
{
    if (self->unk_704 != 0x49) {
        short s;
        int w0[3];
        int w1[3];
        int w2[3];
        UnkStruct_022107ac *p;
        int v;
        unsigned short *res;
        int cond;

        p = &self->sub;
        w0[0] = p->a;
        w0[1] = p->b;
        w0[2] = p->c;
        s = self->unk_8E;
        v = (self->unk_2D8 << 4) >> 16;

        switch (v) {
            case 1:
                func_020912d4(9, w0, &s, 0);
                break;
            case 5:
                if (func_02073908(data_020ccf94, self->unk_800)) {
                    w1[0] = w0[0];
                    w1[1] = w0[1];
                    w1[2] = w0[2];
                    func_ov003_022211bc(self->unk_800, w1);
                } else {
                    res = func_0204f5a8(data_021c80bc, w0, 0);
                    cond = 0;
                    if (res[0] >= 0xfc && res[0] <= 0xfd) {
                        cond = 1;
                    }
                    if (cond) {
                        w2[0] = w0[0];
                        w2[1] = w0[1];
                        w2[2] = w0[2];
                        func_ov003_02221150(self->unk_800, w2);
                    }
                }
                func_0200f268(self, 0x1c);
                break;
            case 7:
                func_0200f328(self, 0x843);
                func_0200f27c(self, 9);
                break;
            case 0x15:
                func_020912d4(0xa, w0, 0, 0);
                break;
            default:
                break;
        }
    }
    func_02010f5c(self);
}
