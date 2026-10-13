/* func_02021c4c @ 0x02021c4c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02021ea8(void *, void *, void *, void *);
extern void func_020820f8(void *);
extern void func_02081bc4(void *, void *);
extern void func_02068404(void *, int, void *);
extern int func_02081d64(void *);
extern void func_02015e70(void *, int, int);
extern void func_020820e0(void *);
extern void func_02021cac(void);

struct UnkStruct_02021c4c {
    char pad_00[0x830];
    void *value;
};
struct UnkStruct_02021c4c_2 {
    char pad_00[0x100];
    struct UnkStruct_02021c4c *b;
};
struct UnkStruct_02021c4c_3 {
    char pad_00[0x40];
    void *unk_40;
};

void *func_02021c4c(struct UnkStruct_02021c4c_2 *arg, void *p1, void *p2)
{
    void *r5;
    char buf[0x2c];

    r5 = func_02021ea8(arg->b->value, p1, p2, func_02021cac);
    if (r5) {
        func_020820f8(buf);
        func_02081bc4(r5, buf);
        func_02068404(((struct UnkStruct_02021c4c_3 *) arg)->unk_40, 1, buf);
        func_02015e70(arg, func_02081d64(r5), 9);
        func_020820e0(buf);
    }
    return r5;
}
