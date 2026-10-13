/* func_ov051_0226131c @ 0x0226131c, 0x48 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *);
extern void func_ov051_0226122c(void *, int);
extern void func_0203e334(void);
extern void *data_ov051_02261b80;

int func_ov051_0226131c(void *param)
{
    if (func_0202ec58(param) == 0) {
        return 0;
    }
    data_ov051_02261b80 = param;
    func_ov051_0226122c(param, 0);
    *(int *) ((char *) param + 0x4e8) |= 2;
    func_0203e334();
    *(short *) ((char *) param + 0x718) = 0x29;
    return 1;
}
