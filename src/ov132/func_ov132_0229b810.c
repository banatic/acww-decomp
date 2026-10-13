/* func_ov132_0229b810 @ 0x0229b810, 0x3c bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void *);
extern void func_ov002_02209eb8(void *);
extern int func_ov132_0229ad70(void *, int);
extern void *func_ov002_02207f60(void *);
extern void func_ov002_0220ad18(void *, void *);

int func_ov132_0229b810(void *arg)
{
    void *res;
    if (func_0206fe54(arg)) {
        func_ov002_02209eb8((char *) arg + 0x94);
    }
    if (!func_ov132_0229ad70(arg, 1)) {
        return 0;
    }
    res = func_ov002_02207f60(arg);
    arg = (char *) arg + 0xf8;
    func_ov002_0220ad18(arg, res);
    return 1;
}
