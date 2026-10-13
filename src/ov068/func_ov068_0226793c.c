/* func_ov068_0226793c @ 0x0226793c, 0x26 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x20];
    int unk_20;
} UnkStruct_0226793c;
extern void func_ov068_0226cce8(UnkStruct_0226793c *s, int a, int flag);
extern void func_0203eddc(int a);
extern void func_0203e0a8(int a, int flag);

void func_ov068_0226793c(UnkStruct_0226793c *s, int a)
{
    if (s->unk_20 == 0) {
        func_ov068_0226cce8(s, a, 0);
        func_0203eddc(a);
    } else {
        func_0203e0a8(a, 0);
    }
}
