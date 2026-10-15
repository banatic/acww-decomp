/* func_ov126_022a054c @ 0x022a054c, 0xc8 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022a054c UnkStruct_022a054c;
struct UnkStruct_022a054c {
    unsigned char pad_00[0xa6];
    unsigned char unk_A6;
    unsigned char pad_A7;
    unsigned char unk_A8;
    unsigned char pad_A9[0xaf - 0xa8 - 1];
    unsigned char unk_AF;
    unsigned char pad_B0[0x19c - 0xb0];
    unsigned char unk_19C;
    unsigned char pad_19D[0x4248 - 0x19d];
    unsigned char unk_4248;
    unsigned char pad_4249[0x4268 - 0x4249];
    unsigned short arr[1];
};

extern int func_ov126_0229f7c8(UnkStruct_022a054c *self, int n);
extern void func_ov095_0229b394(void *p);
extern void func_ov095_0229b3ec(void *p);
extern int func_ov126_022a0740(UnkStruct_022a054c *self);
extern void func_ov126_022a06d8(UnkStruct_022a054c *self);
extern int func_02051c8c_unk(void *p, int n);
extern int func_ov095_0229bcec(void *p1, void *p2, unsigned short v, void *p3, unsigned char a, unsigned char b, int c, int d);
extern void func_ov126_022a0110(void);
extern void func_ov095_022999e8(void);
extern void func_ov126_022a0924(UnkStruct_022a054c *self, unsigned char b);
extern void func_ov126_022a08c4(UnkStruct_022a054c *self);
extern void func_ov126_022a0168(UnkStruct_022a054c *self);
extern void func_ov095_0229b388(void *p);

void func_ov126_022a054c(UnkStruct_022a054c *self)
{
    unsigned char local_byte;
    int count;
    int i;

    if (func_ov126_0229f7c8(self, 8) == 0) {
        return;
    }

    func_ov095_0229b394((char *) self + 0x19c);
    func_ov095_0229b3ec((char *) self + 0x19c);
    if (func_ov126_022a0740(self) != 0) {
        func_ov126_022a06d8(self);
    }

    count = func_02051c8c_unk(self->arr, 0x10);
    local_byte = self->unk_A8;

    for (i = 0; i < count; i++) {
        if (func_ov095_0229bcec((char *) self + 0x19c, (char *) self + 0x4248, self->arr[i], &local_byte, self->unk_A6,
                                self->unk_AF, 0, 0) == 0) {
            if (i == 0) {
                // clang-format off
                asm {
                    mov r0, self
                }
                // clang-format on
                func_ov126_022a0110();
            }
            i = count;
        }
    }

    // clang-format off
    asm {
        ldr r0, =0x19c
        add r0, self, r0
    }
    // clang-format on
    func_ov095_022999e8();
    func_ov126_022a0924(self, local_byte);
    func_ov126_022a08c4(self);
    func_ov126_022a0168(self);
    func_ov095_0229b388((char *) self + 0x19c);
}
