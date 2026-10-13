/* func_ov123_02299e84 @ 0x02299e84, 0x24 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ccc(void *p);

void func_ov123_02299e84(void *p)
{
    int i = 0;
    char *base = (char *) p + 0x124;
    for (; i < 3; i++) {
        func_020b9ccc(base + i * 0x38);
    }
}
