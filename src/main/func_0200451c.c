/* func_0200451c @ 0x0200451c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0200451c;
typedef void (*FuncPtr)(struct UnkStruct_0200451c *);
struct UnkStruct_0200451c {
    FuncPtr *vtbl;
};

void func_0200451c(struct UnkStruct_0200451c *s)
{
    s->vtbl[2](s);
}
