/* func_020b9a18 @ 0x020b9a18, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b9a18 {
    virtual void vfunc1();
    virtual void vfunc2();
    unsigned char pad_04[8];
    unsigned char unk_0C;
    unsigned char pad_0D;
    unsigned char unk_0E;
    unsigned char unk_0F;
    char sub1[0x14];
    char sub2[0x14];
};

extern "C" void func_020b9c68(void);
extern "C" void func_020ba0f8(void *, int, int, int, int, int);
extern "C" unsigned char func_020ba0cc(void *);
extern "C" int func_020b98c4(void *);

extern "C" int func_020b9a18(UnkStruct_020b9a18 *p, int a, int b, int c, int d, int e, int f, int g)
{
    func_020b9c68();
    p->unk_0E = 8;
    func_020ba0f8(&p->sub1, a, c, d, d, e);
    p->unk_0F = func_020ba0cc(&p->sub1);
    func_020ba0f8(&p->sub2, b, c, f, f, g);
    p->unk_0F = (unsigned char) (func_020ba0cc(&p->sub2) + p->unk_0F);
    p->unk_0C = 4;
    if (func_020b98c4(p) != 0) {
        return 1;
    } else {
        p->vfunc2();
        return 0;
    }
}
