/* pockets_screen_23: 4 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_022a1fa4 @ 0x022a1fa4, 0xe0 bytes, Thumb
 * func_ov096_022a1f84 @ 0x022a1f84, 0x20 bytes, Thumb
 * func_ov096_022a1f64 @ 0x022a1f64, 0x20 bytes, Thumb
 * func_ov096_022a1e8c @ 0x022a1e8c, 0xd8 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_022a1e8c;

struct VTable {
    int unk_00;
    int unk_04;
    int (*method)(struct UnkStruct_022a1e8c *);
};

struct UnkStruct_022a1e8c {
    struct VTable *vt;
};

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *object);
extern void *func_020b9af4(void *p);
extern void *func_ov094_0229b000(void *p);
extern void func_ov094_0229bc3c(void *p);
extern void *func_ov094_0229a2ec(void *p);
extern void *func_ov002_02207e40(void *p);
extern void func_ov002_02209e44(void *p);
extern void *func_ov002_02209ccc(void *p);
extern void *func_ov002_02209b14(void *p);
extern void *func_ov002_0220ba24(void *p);
extern void *func_0206e388(void *p);
extern void *func_ov002_0220b47c(void *p);
extern void func_02066694(void *p);
extern char data_ov096_022a23e8[];
extern void func_ov096_022a1488(void *p);
extern void func_ov002_02208090(void *p, int x);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern __arm int func_020ee45c(int a);
extern unsigned char func_ov090_0229936c(void *argument0);
extern void func_ov096_022a1448(int a);
extern void func_0206f848(int a);
extern void func_ov002_0220919c(char *p);
extern int func_ov096_0229c2fc(char *p, int a);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(char *p);
extern void func_ov096_0229eab4(char *p);
extern void func_ov094_0229a850(char *p, int a, void *b);
extern void func_ov094_0229a768(char *p, int a, void *b);
extern void func_ov094_0229b738(char *p, int a, void *b);
extern void func_ov094_02299d84(void *receiver, int value);
extern int func_ov002_02207f60(char *p);
extern void func_0208f210(char *p, int a, int b);

void *func_ov096_022a1fa4(void)
{
    u8 *base;
    u8 *p, *end;

    base = func_ov002_02207f80(0x3028);
    if (base != 0) {
        func_ov002_0220830c((void *) (base));
        *(u32 *) base = (u32) data_ov096_022a23e8;

        p = base + 0x2e8;
        end = base + 0x358;
        do {
            func_020b9af4(p);
            p += 0x38;
        } while (p != end);

        func_ov094_0229b000(end);
        func_ov094_0229bc3c(base + 0x0db8);
        func_ov094_0229a2ec(base + 0x0de0);
        func_ov002_02207e40(base + 0x2418);
        func_ov002_02209e44(base + 0x24e8);
        func_ov002_02209ccc(base + 0x2500);
        func_ov002_02209b14(base + 0x2564);
        func_ov002_0220ba24(base + 0x2958);
        func_0206e388(base + 0x2a74);
        func_ov002_0220b47c(base + 0x2d9c);

        *(u32 *) (base + 0x2e20) = 0;
        *(u32 *) (base + 0x2e24) = 0;
        func_02066694(base + 0x2e28);
        func_02066694(base + 0x2f28);
    }
    return base;
}

int func_ov096_022a1f84(void *p)
{
    func_ov096_022a1488(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0((void *) (p), 1);
    return 1;
}

int func_ov096_022a1f64(int a)
{

    func_ov090_0229936c((void *) func_020ee45c(a));
    func_ov096_022a1448(a);
    func_0206f848(0);
    return 1;
}

int func_ov096_022a1e8c(char *self)
{
    func_ov002_0220919c(self + 0x2564);
    if (func_ov096_0229c2fc(self, 1) == 0) {
        return 1;
    }
    if (((void) (((struct UnkStruct_022a1e8c *) (self + 0x2418))->vt->method((struct UnkStruct_022a1e8c *) (self + 0x2418))),
         func_0206fe54()) != 0) {
        func_ov002_02209eb8(self + 0x2500);
    }
    func_ov096_0229eab4(self);
    if (func_ov096_0229c2fc(self, 2) != 0) {
        func_ov094_0229a850(self + 0x358, 0, *(void **) (self + 0x98));
        func_ov094_0229a768(self + 0x358, 0, *(void **) (self + 0x98));
        func_ov094_0229b738(self + 0xdb8, 0, *(void **) (self + 0x98));
        func_ov094_02299d84(self + 0xde0, (int) *(void **) (self + 0x98));
    }
    if (func_ov096_0229c2fc(self, 0x100) != 0) {
        func_0208f210(self + 0x2d9c, 0, func_ov002_02207f60(self));
        ((struct UnkStruct_022a1e8c *) (self + 0x2d9c))->vt->method((struct UnkStruct_022a1e8c *) (self + 0x2d9c));
    }
    return 1;
}
