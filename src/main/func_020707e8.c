/* func_020707e8 @ 0x020707e8, 0x6a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020707e8 {
    unsigned char pad_00[2];
    unsigned short data[41];
};

struct StackLocal {
    unsigned char pad_00[0xc];
    struct UnkStruct_020707e8 inner;
};

extern void *func_020707d0(struct StackLocal *);
extern int func_020a87e0(struct StackLocal *, int);
extern int func_02051ca8(const unsigned short *, unsigned short);
extern void *func_020707b8(struct StackLocal *);

int func_020707e8(int arg0, const unsigned short *arg1, unsigned short arg2)
{
    struct StackLocal s;
    int len;
    int i;

    func_020707d0(&s);
    func_020a87e0(&s, arg0);

    len = func_02051ca8(arg1, arg2);
    if (len != func_02051ca8(s.inner.data, arg2)) {
        func_020707b8(&s);
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (arg1[i] != s.inner.data[i]) {
            func_020707b8(&s);
            return 0;
        }
    }

    func_020707b8(&s);
    return 1;
}
