/* func_02053728 @ 0x02053728, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(int arg);
extern void func_0204bc64(int arg);
extern int func_02053748(void);

int func_02053728(int arg)
{
    if (func_0204bcdc(arg) != 0) {
        func_0204bc64(arg);
        return func_02053748();
    } else {
        return 0;
    }
}
