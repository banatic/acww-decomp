/* func_0206e114 @ 0x0206e114, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x44];
    unsigned short arr44[10];
    unsigned char pad_58[0xf8 - 0x58];
    unsigned char unk_F8;
} Arg1T;

typedef struct {
    unsigned char pad_00[0x320];
    int unk_320;
} SelfT;

extern void func_0206db74(void);
extern void func_0206db50(SelfT *self, unsigned char v, unsigned char n);
extern void func_020a88ec(void *listObj);
extern void func_020a8874(void *listObj, unsigned short *arr, int n);
extern void func_0206dbc0(SelfT *self, void *listObj);
extern void func_020a887c(void *listObj);
extern int data_020df270;

void func_0206e114(SelfT *self, Arg1T *arg1, unsigned short *outArg)
{
    unsigned short out[0x28];
    unsigned char localB[0x64];
    unsigned short *o;
    int i, j;

    func_0206db74();

    o = outArg ? outArg : out;

    i = 0;
    j = 0;
    for (; i < arg1->unk_F8; i++, j++) {
        o[i] = arg1->arr44[j];
    }

    {
        int k;
        for (k = 0; k < self->unk_320; i++, k++) {
            o[i] = *(unsigned short *) ((char *) self + 0x2b8 + k * 2);
        }
    }

    for (; i < 0x28; i++, j++) {
        if (j < 10) {
            o[i] = arg1->arr44[j];
        } else {
            unsigned short zero = 0;
            o[i] = zero;
        }
    }

    if (self->unk_320 > 0) {
        func_0206db50(self, arg1->unk_F8, (unsigned char) self->unk_320);
    }

    func_020a88ec(&localB[0]);
    *(void **) &localB[0] = &data_020df270;
    func_020a8874(&localB[0], o, 0x28);
    func_0206dbc0(self, &localB[0]);
    *(void **) &localB[0] = &data_020df270;
    func_020a887c(&localB[0]);
}
