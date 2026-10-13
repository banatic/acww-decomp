/* func_02012394 @ 0x02012394, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020123b4(void *p, void *q, int a, int b);

void func_02012394(unsigned short *p, int a, int b)
{
    if (*p != 0xFFF1) {
        func_020123b4(p, p, a, b);
    }
}
