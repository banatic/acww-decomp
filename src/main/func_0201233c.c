/* func_0201233c @ 0x0201233c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201233c {
    unsigned short tag;
};

extern void func_0201235c(struct UnkStruct_0201233c *p, struct UnkStruct_0201233c *q, int a, int b);

void func_0201233c(struct UnkStruct_0201233c *p, int a, int b)
{
    if (p->tag == 0xFFF1) {
        return;
    }
    func_0201235c(p, p, a, b);
}
