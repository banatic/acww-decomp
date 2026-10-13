/* func_020f1ecc @ 0x020f1ecc, 0x8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020f1ecc {
    unsigned char pad_00[0x44];
    int mode;
} UnkStruct_020f1ecc;
void func_020f1ecc(UnkStruct_020f1ecc *self, int v)
{
    self->mode = v;
}
