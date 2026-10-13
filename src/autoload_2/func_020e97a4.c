/* func_020e97a4 @ 0x020e97a4, 0x94 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void func_020e95fc(void *dst, void *src);
extern void func_020e9640(void *dst, void *src);
extern void func_020e9684(void *dst, void *src);
extern void MTX_Concat43(void *dst, void *a, void *b);

void func_020e97a4(void *a, void *b, void *c, void *d)
{
    char buf[0x30];
    if (d) {
        func_020e95fc(buf, d);
        MTX_Concat43(buf, a, a);
    }
    if (c) {
        func_020e9640(buf, c);
        MTX_Concat43(buf, a, a);
    }
    if (b) {
        func_020e9684(buf, b);
        MTX_Concat43(buf, a, a);
    }
}
