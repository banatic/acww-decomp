/* func_0204cdc8 @ 0x0204cdc8, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(void *dst);
extern int func_0209dd9c(void *src, void *dst);

void func_0204cdc8(void *arg0)
{
    unsigned char buf[4];
    int result;
    unsigned char *p;
    unsigned char *q;

    p = (unsigned char *) arg0;
    func_0209df64(buf);
    result = func_0209dd9c(buf, p);
    if (result == 0) {
        q = buf;
        p[0] = q[0];
        p[1] = q[1];
        p[2] = q[2];
        p[3] = q[3];
    }
}
