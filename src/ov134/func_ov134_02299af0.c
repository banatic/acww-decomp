/* func_ov134_02299af0 @ 0x02299af0, 0x28 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_02299b3c(void *);
extern int func_020e895c(void *, int, int);

void func_ov134_02299af0(void *param0, int param1)
{
    int r1 = param1 - 8;
    if (r1 < 0x20) {
        r1 = 0x20;
    }
    if (r1 > 0xa0) {
        r1 = 0xa0;
    }
    func_020e895c((char *) param0 + 0x64, r1, 8);
    func_ov134_02299b3c(param0);
}
