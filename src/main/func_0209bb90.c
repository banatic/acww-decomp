/* func_0209bb90 @ 0x0209bb90, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb];
    unsigned char unk_0B;
} UnkStruct_0209bb90;

void func_0209bb90(UnkStruct_0209bb90 *p, int val)
{
    p->unk_0B = (p->unk_0B & ~0x1f) | (val & 0x1f);
}
