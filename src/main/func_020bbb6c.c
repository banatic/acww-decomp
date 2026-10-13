/* func_020bbb6c @ 0x020bbb6c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209def4(void *buf);
extern unsigned int _s32_div_f(unsigned int a, unsigned int b);

typedef struct {
    unsigned char pad_00[0x120c];
    unsigned int unk_120C;
    unsigned char pad_1210[0x314];
    unsigned int unk_1524;
    unsigned int unk_1528;
} UnkStruct_020bbb6c;

void func_020bbb6c(UnkStruct_020bbb6c *a, unsigned int *b, unsigned int *c)
{
    unsigned char buf[8];

    func_0209def4(buf);
    *b = ((unsigned int) buf[0] * 0x44445) >> 12;
    if (a->unk_1528 != a->unk_1524) {
        *c = _s32_div_f(a->unk_120C << 12, 0x20);
    } else {
        *c = 0;
    }
}
