/* func_020f5748 @ 0x020f5748, 0x184 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

// Sound/message dispatch. Three separate ifs with a shared label avoid a range check.
#pragma opt_propagation off
struct UnkStruct_020f5748 {
    unsigned char pad_00[0x3c];
    unsigned short unk_3C;
    unsigned char unk_3E;
};
struct UnkStruct_020f5748_2 {
    unsigned char pad_00[0x60];
    unsigned char unk_60;
};
struct UnkStruct_020f5748_3 {
    int pad_00;
};

extern struct UnkStruct_020f5748_2 data_021fd1bc;
extern struct UnkStruct_020f5748_3 data_021fd1fc;
extern void func_020eed68(struct UnkStruct_020f5748_3 *, int, int, int, int, int);
extern void NNS_SndPlayerSetVolume(struct UnkStruct_020f5748_3 *, int);
extern void func_020f564c(void *receiver);
extern int func_020f1d3c(struct UnkStruct_020f5748_2 *, int);
extern int func_020ef3ac(void *, int, int, int, int);

int func_020f5748(struct UnkStruct_020f5748 *self, int a, int p2, int p3)
{
    int b;
    struct UnkStruct_020f5748_3 *w;

    if (self->unk_3E == 0x63) {
        if (data_021fd1bc.unk_60 != 0) {
            w = &data_021fd1fc;
            func_020eed68(w, 10, -1, -1, a / 1000, a % 1000);
            NNS_SndPlayerSetVolume(w, 0x64);
            return 1;
        }
    }
    if (a == 0x838) {
        goto hit;
    }
    if (a == 0x839) {
        goto hit;
    }
    if (a != 0x83a) {
        goto skip;
    }
hit:
    func_020f564c(self);
skip:
    b = a;
    if (a == 0x7b || a == 0x7f) {
        b = b + func_020f1d3c(&data_021fd1bc, 4);
        if (b == self->unk_3C) {
            if (b == a) {
                b = b + 1;
            } else if (b == a + 3) {
                b = b - 1;
            }
        }
        self->unk_3C = (unsigned short) b;
    }
    if (self != 0) {
        self = (struct UnkStruct_020f5748 *) ((char *) self + 4);
    }
    return func_020ef3ac(self, a / 1000, b % 1000, p2, p3);
}
