/* func_02065e10 @ 0x02065e10, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051c08(const void *src, void *dst, int size);
extern void func_02051bf8(void *dst, int size);
extern int func_02065f58(void *self, void *buf);
extern void func_02065d0c(void *a, void *b, void *c, void *d);

void func_02065e10(void *obj, const unsigned short *p)
{
    unsigned char local[16];

    if (*p != 0) {
        func_02051c08(p, (unsigned char *) obj + 0xd8, 0x10);
    } else {
        func_02051bf8(&local[2], 6);
        func_02065f58(obj, &local[2]);
        local[0] = 0x24;
        func_02065d0c(local, (unsigned char *) obj + 0xd8, &local[1], &local[2]);
    }
}
