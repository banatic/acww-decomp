/* func_0202bd7c @ 0x0202bd7c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209c54c(int *, int);
extern int func_02015dd4(void *, int, char *, int, char *);

int func_0202bd7c(void *p1, int p2, int p3)
{
    int local = 0;
    char buf[2];
    int retval;

    retval = func_0209c54c(&local, p3);
    buf[0] = (char) local;
    buf[1] = '\0';
    return func_02015dd4(p1, p2, buf, retval, &buf[1]);
}
