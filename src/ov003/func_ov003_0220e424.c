/* func_ov003_0220e424 @ 0x0220e424, 0xac bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200fbe0(void *);
extern void func_0205eac4(void *, int);
extern void func_02010f5c(void *);
extern int func_020912d4(int, void *, int, int);
extern void func_02091278(int, void *, int, int);
extern void func_0200f2a0(void *, int, void *);

struct UnkStruct_0220e424 {
    unsigned int pad_00; // +0x00
    int val;             // +0x04
    int lower;           // +0x08
    int threshold;       // +0x0c
    unsigned int pad_10; // +0x10
    unsigned int pad_14; // +0x14
    int dest;            // +0x18
};

void func_ov003_0220e424(void *self)
{
    char *s = (char *) self;
    struct UnkStruct_0220e424 *sub = (struct UnkStruct_0220e424 *) (s + 0x7d4);
    int *p = &sub->val;

    if (sub->threshold >= 10) {
        *p += 0x1333;
    } else {
        *p -= 0x4cd;
    }

    if (*p > 0x2400) {
        *p = 0x2400;
    } else if (*p < sub->lower) {
        *p = sub->lower;
    }

    *(int *) (s + 0x2e0) = *p;

    if (func_0200fbe0(s) == 4) {
        func_0205eac4(s + 0x5a0, *p);
    }

    func_02010f5c(s);

    p = &sub->dest;
    if (*p == -1) {
        *p = func_020912d4(0x4c, s + 0x6e0, 0, 0);
    } else {
        func_02091278(*p, s + 0x6e0, 0, 0);
    }

    func_0200f2a0(s, 0x8a, s + 0x5c);
}
