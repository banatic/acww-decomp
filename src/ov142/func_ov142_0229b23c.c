/* func_ov142_0229b23c @ 0x0229b23c, 0x3a bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

struct Obj0229b23c {
    unsigned char pad_00[0xc0];
    unsigned char unk_C0;
};

extern int func_ov142_02299668(struct Obj0229b23c *p, int n);
extern void func_ov142_02299648(struct Obj0229b23c *p, int n);
extern void func_ov142_0229b0d4(struct Obj0229b23c *p);
extern void func_ov002_02207fc0(struct Obj0229b23c *p);
extern void func_ov002_02208098(struct Obj0229b23c *p, int n);

void func_ov142_0229b23c(struct Obj0229b23c *p)
{
    if (func_ov142_02299668(p, 0x80)) {
        func_ov142_02299648(p, 0x80);
    } else {
        p->unk_C0 = 0;
    }
    func_ov142_0229b0d4(p);
    func_ov002_02207fc0(p);
    func_ov002_02208098(p, 4);
}
