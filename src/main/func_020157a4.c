/* func_020157a4 @ 0x020157a4, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x6c];
    int unk_6C;
    int unk_70;
    unsigned char pad_74[0x14];
    unsigned char unk_88;
} UnkStruct_020157a4;
void func_020157a4(UnkStruct_020157a4 *p, int a, int b, int c)
{
    p->unk_6C = a;
    p->unk_70 = b;
    p->unk_88 = (unsigned char) c;
}
