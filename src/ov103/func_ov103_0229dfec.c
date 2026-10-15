/* func_ov103_0229dfec @ 0x0229dfec, 0xbc bytes, Thumb, module ov103
 * mwccarm 1.2/base -O1,s
 */

extern void func_ov002_0220919c(void *);
extern int func_ov103_0229c2f4(void *self, int flag);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern void func_ov103_0229ca00(void *);
extern void func_ov094_0229a850(void *, int, void *);
extern void func_ov094_0229b738(void *, int, void *);
extern void func_ov094_02299d84(void *receiver, int value);
extern int func_ov002_02207f60(void *);
extern void func_0208f210(void *, int, int);

typedef struct VTable {
    unsigned int pad_00;
    unsigned int pad_04;
    int (*func)(void *);
} VTable;

typedef struct UnkStruct_0229dfec {
    VTable *vtable;
} UnkStruct_0229dfec;

int func_ov103_0229dfec(void *self)
{
    func_ov002_0220919c((char *) self + 0x22d8);
    if (func_ov103_0229c2f4(self, 1) == 0) {
        return 1;
    }

    ((UnkStruct_0229dfec *) ((char *) self + 0x218c))->vtable->func((char *) self + 0x218c);
    if (func_0206fe54() != 0) {
        func_ov002_02209eb8((char *) self + 0x2274);
    }

    func_ov103_0229ca00(self);
    if (func_ov103_0229c2f4(self, 2) != 0) {
        func_ov094_0229a850((char *) self + 0xcc, 0, *(void **) ((char *) self + 0x2b8c));
        func_ov094_0229b738((char *) self + 0xb2c, 0, *(void **) ((char *) self + 0x2b8c));
        func_ov094_02299d84((char *) self + 0xb54, (int) *(void **) ((char *) self + 0x2b8c));
    }

    if (func_ov103_0229c2f4(self, 0x80) != 0) {
        int r = func_ov002_02207f60(self);
        func_0208f210((char *) self + 0x2b10, 0, r);
        ((UnkStruct_0229dfec *) ((char *) self + 0x2b10))->vtable->func((char *) self + 0x2b10);
    }
    return 1;
}
