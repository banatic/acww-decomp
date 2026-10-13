/* func_ov127_02299a94 @ 0x02299a94, 0x28 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov127_02299abc(void *, int, int);

typedef struct {
    unsigned char pad_00[0x2824];
    unsigned short unk_2824;
    unsigned short unk_2826;
} unk_struct;

void func_ov127_02299a94(unk_struct *s, int a, int b)
{
    s->unk_2824 = (unsigned short) ((a - 0x80) & 0x1ff);
    s->unk_2826 = (unsigned short) (b - 0x60);
    func_ov127_02299abc(s, 0, 0);
}
