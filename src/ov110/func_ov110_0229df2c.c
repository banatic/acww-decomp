/* func_ov110_0229df2c @ 0x0229df2c, 0x130 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229df2c UnkStruct_0229df2c;

extern int func_ov110_0229e7ac(void *receiver);
extern int func_ov110_0229cce8(UnkStruct_0229df2c *, int);
extern void func_ov110_0229cbe0(UnkStruct_0229df2c *);
extern int func_ov002_02207d24(void *, int);
extern void func_ov110_0229c3b8(UnkStruct_0229df2c *, int);
extern void func_ov110_0229cde0(UnkStruct_0229df2c *);
extern void func_ov110_0229cfd4(UnkStruct_0229df2c *);
extern int func_ov110_0229d504(UnkStruct_0229df2c *, void *, void *, int);
extern int func_ov110_0229c2c8(UnkStruct_0229df2c *, int);
extern int func_ov110_0229d5d4(UnkStruct_0229df2c *, int);
extern int func_ov110_0229d5e4(UnkStruct_0229df2c *, int);
extern int func_ov110_0229d0b8(UnkStruct_0229df2c *, int);
extern int func_ov110_0229d13c(UnkStruct_0229df2c *, int);
extern int func_ov110_0229d680(UnkStruct_0229df2c *, int, void *);
extern int func_ov110_0229d4a8(UnkStruct_0229df2c *, int);
extern void func_ov094_022999d8(void);
extern void func_ov110_0229d840(UnkStruct_0229df2c *);
extern void func_ov110_0229cf98(UnkStruct_0229df2c *, int);
extern unsigned char data_021fbdd8;

void func_ov110_0229df2c(UnkStruct_0229df2c *p)
{
    int r4;
    void *r6;
    void *ptr;

    if (func_ov110_0229e7ac(p) != 0) {
        func_ov110_0229cce8(p, *(unsigned char *) ((char *) p + 0xf4));
        func_ov110_0229cbe0(p);
        func_ov002_02207d24((char *) p + 0x21f8, 0);
        func_ov110_0229c3b8(p, 0);
        return;
    }

    func_ov110_0229cde0(p);
    func_ov110_0229cfd4(p);
    r6 = (char *) (*(char **) ((char *) p + 0xac)) + 8;
    ptr = (char *) (*(char **) ((char *) p + 0xa8)) + 8;
    r4 = func_ov110_0229d504(p, ptr, r6, 0);

    if (func_ov110_0229c2c8(p, 0x200) == 0) {
        goto common;
    }

    if ((func_ov110_0229d5d4(p, r4) != 0) && (func_ov110_0229d5e4(p, *(unsigned char *) ((char *) p + 0xf4)) != 0)) {
        goto dfca;
    }
    if ((func_ov110_0229d5e4(p, r4) != 0) && (func_ov110_0229d5d4(p, *(unsigned char *) ((char *) p + 0xf4)) != 0)) {
        goto dfca;
    }
    goto common;

dfca:
    if (func_ov110_0229d0b8(p, r4) == 0xfff1) {
        goto common;
    }
    r4 = 0x1f;

common:
    if (r4 == 0x1f) {
        goto e030;
    }
    if (data_021fbdd8 != 0) {
        goto e026;
    }
    if (func_ov110_0229d13c(p, r4) != 0) {
        func_ov110_0229d680(p, *(unsigned char *) ((char *) p + 0xf4), r6);
        return;
    }
    if (func_ov110_0229d4a8(p, r4) != 0) {
        goto e01a;
    }
    func_ov110_0229d680(p, *(unsigned char *) ((char *) p + 0xf4), r6);
    return;

e01a:
    func_ov094_022999d8();
    func_ov110_0229d840(p);
    return;

e026:
    func_ov110_0229cf98(p, r4);
    return;

e030:
    if (data_021fbdd8 != 0) {
        return;
    }
    func_ov110_0229d680(p, *(unsigned char *) ((char *) p + 0xf4), r6);
    return;
}
