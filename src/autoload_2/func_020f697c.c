/* func_020f697c @ 0x020f697c, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void ENV_SetResourceSet(void *);
extern void func_020f6f80(void *, int);

typedef struct UnkStruct_020f697c {
    char pad_00[0x14];
    char sub14[0x24];
    signed char unk_38;
    signed char unk_39;
    signed char unk_3A;
    signed char unk_3B;
} UnkStruct_020f697c;

typedef struct UnkStruct_020f697c_2 {
    char pad_00[0x30];
    void *unk_30;
} UnkStruct_020f697c_2;

extern UnkStruct_020f697c_2 data_021fd1bc;

void func_020f697c(UnkStruct_020f697c *self)
{
    data_021fd1bc.unk_30 = self;
    ENV_SetResourceSet(self->sub14);
    ENV_SetResourceSet(self);
    func_020f6f80(self, 0);
    self->unk_38 = 0;
    self->unk_39 = -1;
    self->unk_3A = 0;
    self->unk_3B = 0;
}
