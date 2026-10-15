/* func_020b9f30 @ 0x020b9f30, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ed8(void *a);
extern void func_020ba1a8(void *a, int b, int c, int d);
extern unsigned char func_020ba128(void *a);
extern int func_020b9978(void *a);
extern void func_020ba004(void *a);

struct UnkStruct_020b9f30 {
    int pad_00;
};

struct UnkStruct_020b9f30_2 {
    unsigned char pad_00[0xc];
    unsigned char a;
    unsigned char pad_0D;
    unsigned char b;
    unsigned char c;
    struct UnkStruct_020b9f30 sub;
};

int func_020b9f30(struct UnkStruct_020b9f30_2 *p0, int p1, int p2, int p3, unsigned char arg4)
{
    func_020b9ed8(p0);
    p0->b = 2;
    func_020ba1a8(&p0->sub, p2, p1, p3);
    p0->c = func_020ba128(&p0->sub);
    p0->a = arg4;
    if (func_020b9978(p0)) {
        return 1;
    } else {
        func_020ba004(p0);
        return 0;
    }
}
