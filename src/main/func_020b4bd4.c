/* func_020b4bd4 @ 0x020b4bd4, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020b4bd4 {
    unsigned char pad_00[0x24];
    unsigned int unk_24;
    unsigned char pad_28[0x14];
    unsigned int unk_3C;
} UnkStruct_020b4bd4;

extern void func_020a92d8(UnkStruct_020b4bd4 *p, int flag);

void func_020b4bd4(UnkStruct_020b4bd4 *p)
{
    p->unk_24 = 1;
    p->unk_3C = 1;
    func_020a92d8(p, 0);
    p->unk_24 = 0;
}
