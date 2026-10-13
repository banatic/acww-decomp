/* func_ov090_02299058 @ 0x02299058, 0x20 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ccc(void *p);

void func_ov090_02299058(void *self)
{
    int i;
    char *base;
    i = 0;
    base = (char *) self + 0x9c;
    for (; i < 3; i++) {
        func_020b9ccc(base + i * 56);
    }
}
