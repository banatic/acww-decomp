/* func_ov003_0221cd7c @ 0x0221cd7c, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_022632c8(void *ptr, unsigned int byte);
extern void func_020033e4(void *p, int arg);

void func_ov003_0221cd7c(unsigned char *p, int arg)
{
    unsigned int i;
    unsigned char *ptr;

    if (arg == 2) {
        if (!(p[0x235] & 1)) {
            for (i = 0; i < 6; i++) {
                ptr = *(unsigned char **) (p + i * 4 + 0x2d8);
                if (ptr && ptr[0x2d8] != 0) {
                    func_ov009_022632c8(ptr, ptr[0x2d8]);
                }
            }
        }
    }
    func_020033e4(p, arg);
}
