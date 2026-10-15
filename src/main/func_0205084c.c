/* func_0205084c @ 0x0205084c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern void func_02077978(const void *src, int *out1, int *out2);
extern void func_0204ff00(unsigned int a, int b, int c, int d, int e);

void func_0205084c(const signed char *src, int arg1)
{
    int v1;
    int v2;
    char buf[5];
    signed char b;

    b = src[1];
    MI_CpuCopy8(src + 2, buf, 5);
    func_02077978(buf, &v1, &v2);
    func_0204ff00((unsigned char) arg1, 0, b, v1, v2);
}
