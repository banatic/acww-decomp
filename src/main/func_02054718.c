/* func_02054718 @ 0x02054718, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02054a98(unsigned int a, unsigned int b);
extern void func_02054a34(unsigned int a, unsigned int b);

void func_02054718(unsigned int a, unsigned int start, unsigned int end)
{
    unsigned int i;
    for (i = start; i <= end; i++) {
        func_02054a98(a, i);
        func_02054a34(a, i);
    }
}
