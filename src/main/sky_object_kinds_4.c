/* sky_object_kinds_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bfcbc @ 0x020bfcbc, 0x1c bytes, Thumb
 * func_020bfcb8 @ 0x020bfcb8, 0x2 bytes, Thumb
 * func_020bfcb0 @ 0x020bfcb0, 0x8 bytes, Thumb
 */

struct UnkStruct_020bfcbc {
    unsigned char pad_00[0x0c];
    unsigned int unk_0C;
    unsigned char pad_10[0x24];
    unsigned int unk_34;
    unsigned int unk_38;
    unsigned char pad_3C[0x1c];
    unsigned int unk_58;
};

extern void func_020bf590(void *);

void func_020bfcbc(struct UnkStruct_020bfcbc *s)
{
    s->unk_34 = 0x000b0000;
    s->unk_38 = 0x00067000;
    s->unk_0C = 0x15;
    s->unk_58 = 3;
}

void func_020bfcb8(void) {}

void func_020bfcb0(void *argument0)
{
    func_020bf590((void *) argument0);
}
