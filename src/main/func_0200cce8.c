/* func_0200cce8 @ 0x0200cce8, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;

extern void func_020984e8(void);
extern int func_02099784(void);
extern void func_020112f8(void *dst, void *src);
extern int func_020644cc(int);
extern void func_ov003_0220edcc(void *self, int a, int b);
extern void func_0200d4e8(void *self, int a, int b, int c);
extern int func_0200dc8c(void *self);
extern int func_0200dc48(void *self);
extern int func_020e8b4c(int a, signed short b);
extern void func_0200cc00(void *self, int a, int b, int c);
extern void func_02010538(void *self);

typedef struct self_t {
    unsigned char pad_00[0x98];
    unsigned int unk_98;
    unsigned char pad_9C[0x704 - 0x9c];
    unsigned int unk_704;
    unsigned char pad_708[0x7d4 - 0x708];
    int unk_7D4;
    unsigned char pad_7D8[0x8e8 - 0x7d8];
    unsigned char unk_8E8;
} UnkStruct_0200cce8;

void func_0200cce8(UnkStruct_0200cce8 *self, signed short *p)
{
    unsigned int cond = (data_020e54a8 == 0) ? 1 : 0;

    if (cond > 0) {
        if (self->unk_8E8 != 0) {
            goto other;
        }
        if (self->unk_98 != 0x6e2) {
            goto other;
        }

        func_020984e8();

        if (func_02099784() != 2) {
            unsigned short tmp[4];
            func_020112f8(tmp, self);
            if (tmp[0] != 0x13c3) {
                goto other;
            }
        }

        if (func_020644cc(0x17a) != 0) {
            goto other;
        }

        func_ov003_0220edcc(self, 6, -1);
        return;
    }

other:
    if (self->unk_7D4 <= 0) {
        func_0200d4e8(self, 3, 1, -1);
    }

    if (self->unk_704 == 2) {
        if (func_0200dc8c(self) > 0) {
            int m = func_0200dc48(self);
            if (func_020e8b4c(m, p[0]) > 0x3a4c) {
                func_0200cc00(self, m, 3, -1);
            }
        }
    }

    func_02010538(self);
}
