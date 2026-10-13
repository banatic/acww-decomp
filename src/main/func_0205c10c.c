/* func_0205c10c @ 0x0205c10c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020c9fcc;
extern unsigned int data_021c9b34;
extern __arm unsigned int func_020ea0e0(unsigned int, int);

void func_0205c10c(int param)
{
    unsigned int size = 0;
    size = size + ((((data_020c9fcc + 3) & ~3u) + 0x4b) & ~3u);
    data_021c9b34 = func_020ea0e0(size, param);
}
