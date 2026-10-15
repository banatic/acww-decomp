/* func_ov003_0221ee54 @ 0x0221ee54, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_022398c4;
extern int func_020b65c4(void);
extern int func_02084cd0(void *a, int b, void *c);

int func_ov003_0221ee54(void *arg)
{
    int ret;
    ret = func_020b65c4();
    func_02084cd0(&data_ov003_022398c4, ret, (char *) arg + 0x5c);
    return 1;
}
