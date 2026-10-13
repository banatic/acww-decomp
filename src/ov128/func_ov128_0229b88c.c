/* func_ov128_0229b88c @ 0x0229b88c, 0x30 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2d5c];
    int a;
    int b;
} UnkStruct_0229b88c;

extern void func_ov128_0229b8d4(UnkStruct_0229b88c *p);

void func_ov128_0229b88c(UnkStruct_0229b88c *p)
{
    if (p->a != -1 && p->b != p->a) {
        p->b = p->a;
        func_ov128_0229b8d4(p);
    }
}
