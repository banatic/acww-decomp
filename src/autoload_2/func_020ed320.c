/* func_020ed320 @ 0x020ed320, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021fbf14;
extern int data_0213e6c0;
extern void MI_CpuCopy8(void *dst, const void *src, unsigned int size);

void func_020ed320(void *a, void *b, void *c, void *d)
{
    if (a != 0 && b != 0 && c == 0) {
        MI_CpuCopy8(a, d, data_021fbf14);
    }
    data_0213e6c0 = 1;
}
