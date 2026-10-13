/* func_020a8308 @ 0x020a8308, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a873c(int, unsigned char *);

unsigned char func_020a8308(int arg)
{
    unsigned char val;
    func_020a873c(arg, &val);
    if (val == 6) {
        val = 5;
    }
    return val;
}
