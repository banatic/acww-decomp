/* func_ov003_02216948 @ 0x02216948, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02010f5c(void);
extern int func_02056f28(void *p, int n);
extern void func_ov003_02216780(void *p);

void func_ov003_02216948(void *p)
{
    func_02010f5c();
    if (func_02056f28((char *) p + 0x2d0, 8)) {
        func_ov003_02216780(p);
    }
}
