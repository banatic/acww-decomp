/* func_0202e430 @ 0x0202e430, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201cd2c(void *ptr);
extern void func_0201cc6c(void *ptr, int arg1, int arg2);

void func_0202e430(void *arg0, int arg1, int arg2)
{
    if (func_0201cd2c((void *) ((char *) arg0 + 0x83c))) {
        func_0201cc6c((void *) ((char *) arg0 + 0x83c), arg1, arg2);
    }
}
