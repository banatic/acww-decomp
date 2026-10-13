/* func_020b4a78 @ 0x020b4a78, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x28];
    int unk_28;
    int unk_2C;
} UnkStruct_020b4a78;
void func_020b4a78(UnkStruct_020b4a78 *p, int v)
{
    p->unk_2C = v;
    p->unk_28 = p->unk_28 - 1;
}
