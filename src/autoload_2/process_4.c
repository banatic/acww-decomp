/* process_4: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020ee4d4 @ 0x020ee4d4, 0x4 bytes, ARM
 * func_020ee4cc @ 0x020ee4cc, 0x8 bytes, ARM
 */

typedef struct UnkStruct_020ee4cc {
    unsigned char pad_00[0x4c];
    int unk_4C;
} UnkStruct_020ee4cc;

void func_020ee4d4(void *object) {}

void func_020ee4cc(UnkStruct_020ee4cc *self, int v)
{
    self->unk_4C = v;
}
