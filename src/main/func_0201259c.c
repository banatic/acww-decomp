/* func_0201259c @ 0x0201259c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02082d1c(void *);

struct UnkStruct_0201259c {
    unsigned short tag;
    unsigned int data;
};

struct UnkStruct_0201259c *func_0201259c(struct UnkStruct_0201259c *p)
{
    p->tag = 0xFFF1;
    func_02082d1c(&p->data);
    p->tag = 0xFFF1;
    return p;
}
