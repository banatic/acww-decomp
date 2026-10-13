/* func_ov003_0221dc1c @ 0x0221dc1c, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984d4(void);
extern int func_020988d8(void);

int func_ov003_0221dc1c(void)
{
    int result;

    func_020984d4();
    result = func_020988d8();

    if (result != 0) {
        return 0;
    } else {
        return 1;
    }
}
