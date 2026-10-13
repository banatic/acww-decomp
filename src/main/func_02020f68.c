/* func_02020f68 @ 0x02020f68, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202d8f8(void *a, void *b, void *c, int d, int e);

typedef struct UnkStruct_02020f68 {
    unsigned char pad_830[0x830];
    int unk_830;
} UnkStruct_02020f68;

typedef struct UnkStruct_02020f68_2 {
    unsigned char pad_100[0x100];
    UnkStruct_02020f68 *inner;
    unsigned char pad_104[0x24];
    unsigned char unk_128;
    unsigned char pad_129[0x3];
    unsigned char unk_12C;
} UnkStruct_02020f68_2;

void func_02020f68(UnkStruct_02020f68_2 *param0)
{
    func_0202d8f8(param0, (void *) &param0->unk_12C, (void *) &param0->unk_128, param0->inner->unk_830, 0);
}
