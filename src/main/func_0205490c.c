/* func_0205490c @ 0x0205490c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcc10(void *p0, void *p1);
extern int func_020549fc(void *p0, unsigned char b);
extern int func_02054944(void *p0, void *p1);
extern int func_02054d14(void *p0, void *p1);

int func_0205490c(void *arg0, void *arg1)
{
    int ret;
    unsigned char b;
    ret = func_01ffcc10(arg0, arg1);
    if (ret != 0) {
        return ret;
    }
    b = ((unsigned char *) (*(void **) arg1))[1];
    if (func_020549fc(arg0, b) != 0) {
        return func_02054944(arg0, arg1);
    } else {
        return func_02054d14(arg0, arg1);
    }
}
