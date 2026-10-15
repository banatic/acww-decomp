/* func_02077dd4 @ 0x02077dd4, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eb628(int, void *, int, int);
extern void MI_CpuCopy8(const void *, void *, unsigned int);

int func_02077dd4(void *out, const unsigned char *s, int a2)
{
    unsigned long long v;
    unsigned long long i;
    unsigned char buf[0xc];
    v = 0;
    for (i = 0; i < 12; i++) {
        v = v * 10 + (unsigned int) s[i];
    }
    if (func_020eb628(a2, buf, (int) v, (int) (v >> 32)) == 0) {
        return 0;
    }
    MI_CpuCopy8(buf, out, 0xc);
    return 1;
}
