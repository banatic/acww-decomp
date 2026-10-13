/* func_ov111_022a0d9c @ 0x022a0d9c, 0x30 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov111_0229efd8(void *, int);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern void func_ov111_0229fe0c(void *);

int func_ov111_022a0d9c(void *arg)
{
    if (func_ov111_0229efd8(arg, 4) != 0) {
        if (func_0206fe54() != 0) {
            func_ov002_02209eb8((char *) arg + 0x3d38);
        }
        func_ov111_0229fe0c(arg);
    }
    return 1;
}
