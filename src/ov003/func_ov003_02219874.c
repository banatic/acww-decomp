/* func_ov003_02219874 @ 0x02219874, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02219874 {
    char pad_00[0x7f0];
    int a;
    char pad_7F4[8];
    int b;
};

extern struct UnkStruct_02219874 *func_02096718(int);
extern int func_02008258(struct UnkStruct_02219874 *, int);
extern int func_ov003_02218fac(struct UnkStruct_02219874 *, int, int, int);

int func_ov003_02219874(void)
{
    struct UnkStruct_02219874 *p = func_02096718(4);
    if (p) {
        p->b = func_02008258(p, p->a);
        return func_ov003_02218fac(p, 3, 5, -1);
    } else {
        return 0;
    }
}
