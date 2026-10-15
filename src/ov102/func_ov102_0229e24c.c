/* func_ov102_0229e24c @ 0x0229e24c, 0x50 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24d0];
    int val;
} UnkStruct_0229e24c;

extern int func_ov002_02207f3c(UnkStruct_0229e24c *p, int a);
extern void func_020027f0(int a);
extern unsigned char *func_ov002_022080a0(UnkStruct_0229e24c *p, unsigned char value);
extern void func_ov102_0229c288(UnkStruct_0229e24c *p, int a);
extern void func_ov002_02207e80(UnkStruct_0229e24c *p, int a, int b, int c);
extern int func_ov002_02207f60(UnkStruct_0229e24c *p);

void func_ov102_0229e24c(UnkStruct_0229e24c *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        (func_ov002_022080a0(p, 5), (int) ((char *) (p) + 0x8f));
        func_ov102_0229c288(p, 1);
        func_ov102_0229c288(p, 2);
    } else {
        func_ov002_02207e80(p, 6, 0, 0);
    }
    p->val = func_ov002_02207f60(p);
}
