/* func_02069d8c @ 0x02069d8c, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef int (*SubMethod)(void *);
struct SubVtbl {
    SubMethod func0;
    SubMethod func1;
    SubMethod func2;
    SubMethod func3;
};
struct UnkStruct_02069d8c {
    struct SubVtbl *vtbl;
};
struct Big {
    unsigned char pad_00[0x1a58];
    char unk_1A58;
    unsigned char pad1[0x7];
    int unk_1A60;
    unsigned char pad_1A64[0x3c0];
    struct UnkStruct_02069d8c sub;
};
struct UnkStruct_02069d8c_2 {
    unsigned char pad_00[0x24];
    struct Big *unk_24;
    unsigned char pad1[0x34];
    int unk_5C;
};

extern unsigned char data_020df154;
extern int func_02067728(struct Big *);
extern void func_0206bb9c(void);
extern int func_020a82f8(int);
extern void func_020a9334(struct UnkStruct_02069d8c_2 *, int);
extern void func_020a7994(void *, int);

void func_02069d8c(struct UnkStruct_02069d8c_2 *self)
{
    if (func_02067728(self->unk_24) == 0) {
        asm {
            mov r0, self
            ldr r1, =0xdd0
            ldr r2, =data_020df154
            bl func_0206bb9c
        }
    }
    func_020a9334(self, func_020a82f8(self->unk_5C));
    func_020a9334(self, ((struct UnkStruct_02069d8c *) ((char *) self->unk_24 + 0x1e24))
                            ->vtbl->func3((struct UnkStruct_02069d8c *) ((char *) self->unk_24 + 0x1e24)));
    func_020a9334(self, func_020a82f8(2));
    func_020a7994((char *) self->unk_24 + 0x1a58,
                  ((struct UnkStruct_02069d8c *) ((char *) self->unk_24 + 0x1e24))
                      ->vtbl->func3((struct UnkStruct_02069d8c *) ((char *) self->unk_24 + 0x1e24)));
    self->unk_24->unk_1A60 = 1;
}
