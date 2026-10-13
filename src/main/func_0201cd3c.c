/* func_0201cd3c @ 0x0201cd3c, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201cd2c(void *ptr);
extern void func_020044a0(void *ptr);

int func_0201cd3c(void *ptr)
{
    if (func_0201cd2c(ptr) != 0) {
        func_020044a0(ptr);
    }
    ((char *) ptr)[0x59] = 0;
    return 0;
}
