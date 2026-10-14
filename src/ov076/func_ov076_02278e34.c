/* func_ov076_02278e34 @ 0x02278e34, 0x24 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201612c(void *p);

struct Pair {
    unsigned int a;
    unsigned int b;
};

struct UnkStruct_02278e34 {
    char pad_00[0xBC];
    struct Pair pair;
};

extern struct Pair __ptmf_null;

void func_ov076_02278e34(struct UnkStruct_02278e34 *p)
{
    func_0201612c(p);
    p->pair = __ptmf_null;
}
