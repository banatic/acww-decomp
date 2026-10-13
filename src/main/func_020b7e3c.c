/* func_020b7e3c @ 0x020b7e3c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Struct020b7e3c {
    char pad_00[0x1c];
    int unk_1C;
    int unk_20;
    int unk_24;
};
extern void func_020b75b4(struct Struct020b7e3c *p);
extern void func_020b7e9c(struct Struct020b7e3c *p, int flag);
struct Struct020b7e3c *func_020b7e3c(struct Struct020b7e3c *p)
{
    func_020b75b4(p);
    func_020b7e9c(p, 0);
    p->unk_1C = 0;
    p->unk_20 = 0;
    p->unk_24 = 0;
    return p;
}
