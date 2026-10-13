/* func_020b4bb4 @ 0x020b4bb4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    int unk_24;
    char pad_28[0x10];
    int unk_38;
    int unk_3C;
} UnkStruct_020b4bb4;

extern void func_020a92d8(UnkStruct_020b4bb4 *);

int func_020b4bb4(UnkStruct_020b4bb4 *p)
{
    p->unk_24 = 3;
    p->unk_3C = 1;
    p->unk_38 = 0;
    func_020a92d8(p);
    p->unk_24 = 0;
    return p->unk_38;
}
