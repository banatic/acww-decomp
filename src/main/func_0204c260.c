/* func_0204c260 @ 0x0204c260, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02061e2c(void *, void *);
extern int func_0204bcf8(void *);
extern int func_0206233c(void *);
extern int func_0204bcdc(void *);
extern int func_020536c8(void *);
extern void func_020051b0(void *);

int func_0204c260(void *param)
{
    char local[8];
    func_02061e2c(local, param);
    if (func_0204bcf8(local) == 1) {
        int ret = func_0206233c(local);
        func_020051b0(local);
        return ret;
    } else if (func_0204bcdc(local) != 0) {
        int ret = func_020536c8(local);
        func_020051b0(local);
        return ret;
    } else {
        func_020051b0(local);
        return 1;
    }
}
