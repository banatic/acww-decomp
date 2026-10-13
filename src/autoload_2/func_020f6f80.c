/* func_020f6f80 @ 0x020f6f80, 0x8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    unsigned short unk_08;
} UnkStruct_020f6f80;
void func_020f6f80(UnkStruct_020f6f80 *p, unsigned short v)
{
    p->unk_08 = v;
}
