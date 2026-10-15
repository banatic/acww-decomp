/* func_020b9e08 @ 0x020b9e08, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ba184(void *);
extern void func_020ba160(void *);

int func_020b9e08(void *arg0)
{
    unsigned char *p = (unsigned char *) arg0;
    if (p[0xe] == 3) {
        func_020ba184(p + 0x10);
        func_020ba160(p + 0x1c);
    }
    return 1;
}
