/* func_0207ff0c @ 0x0207ff0c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207ffa0(const void *p, int idx);
extern void func_02061b1c(void *dst, const void *src, int count);

void func_0207ff0c(unsigned short *out, const void *p, int idx)
{
    unsigned short tmp;

    *out = 0xFFF1;
    if (func_0207ffa0(p, idx)) {
        *out = *(unsigned short *) ((const char *) p + idx * 2 + 0x78c);
        if (*out != 0xFFF1) {
            func_02061b1c(&tmp, out, 1);
            *out = tmp;
        }
    }
}
