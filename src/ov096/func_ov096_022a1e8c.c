/* func_ov096_022a1e8c @ 0x022a1e8c, 0xd8 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220919c(char *p);
extern int func_ov096_0229c2fc(char *p, int a);
extern int func_0206fe54(int a);
extern void func_ov002_02209eb8(char *p);
extern void func_ov096_0229eab4(char *p);
extern void func_ov094_0229a850(char *p, int a, void *b);
extern void func_ov094_0229a768(char *p, int a, void *b);
extern void func_ov094_0229b738(char *p, int a, void *b);
extern void func_ov094_02299d84(char *p, void *b);
extern int func_ov002_02207f60(char *p);
extern void func_0208f210(char *p, int a, int b);

struct UnkStruct_022a1e8c;
struct VTable {
    int unk_00;
    int unk_04;
    int (*method)(struct UnkStruct_022a1e8c *);
};
struct UnkStruct_022a1e8c {
    struct VTable *vt;
};

int func_ov096_022a1e8c(char *self)
{
    func_ov002_0220919c(self + 0x2564);
    if (func_ov096_0229c2fc(self, 1) == 0) {
        return 1;
    }
    if (func_0206fe54(
            ((struct UnkStruct_022a1e8c *) (self + 0x2418))->vt->method((struct UnkStruct_022a1e8c *) (self + 0x2418))) != 0) {
        func_ov002_02209eb8(self + 0x2500);
    }
    func_ov096_0229eab4(self);
    if (func_ov096_0229c2fc(self, 2) != 0) {
        func_ov094_0229a850(self + 0x358, 0, *(void **) (self + 0x98));
        func_ov094_0229a768(self + 0x358, 0, *(void **) (self + 0x98));
        func_ov094_0229b738(self + 0xdb8, 0, *(void **) (self + 0x98));
        func_ov094_02299d84(self + 0xde0, *(void **) (self + 0x98));
    }
    if (func_ov096_0229c2fc(self, 0x100) != 0) {
        func_0208f210(self + 0x2d9c, 0, func_ov002_02207f60(self));
        ((struct UnkStruct_022a1e8c *) (self + 0x2d9c))->vt->method((struct UnkStruct_022a1e8c *) (self + 0x2d9c));
    }
    return 1;
}
