/* func_020b35c0 @ 0x020b35c0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057a50(int arg1, const char *arg2);
extern char data_020e50fc[];

void func_020b35c0(unsigned char *out, int arg)
{
    *out = (unsigned char) func_02057a50(arg, data_020e50fc);
}
