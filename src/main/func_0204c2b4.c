/* func_0204c2b4 @ 0x0204c2b4, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02061e2c(int *buf, int arg);
extern int func_0204bcf8(int *buf);
extern int func_02062408(int *buf);
extern void func_020051b0(int *buf);
extern int func_0204bcdc(int *buf);
extern int func_02053728(int *buf);

int func_0204c2b4(int arg)
{
    int buf[2];
    func_02061e2c(buf, arg);
    if (func_0204bcf8(buf) == 1) {
        int r4 = func_02062408(buf);
        func_020051b0(buf);
        return r4;
    } else {
        if (func_0204bcdc(buf) != 0) {
            int r4 = func_02053728(buf);
            func_020051b0(buf);
            return r4;
        } else {
            func_020051b0(buf);
            return 0;
        }
    }
}
