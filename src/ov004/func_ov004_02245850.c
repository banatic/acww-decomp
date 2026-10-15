/* func_ov004_02245850 @ 0x02245850, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a182c(void);
extern void func_ov004_02245cf4(void *self, int i);

void func_ov004_02245850(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020a182c();
    if (v1 != 0x0) {
        func_ov004_02245cf4(self, 0x6);
        return;
    }
    return;
}
