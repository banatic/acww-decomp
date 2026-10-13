/* func_02041140 @ 0x02041140, 0x52 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e29c(int, int);
extern int func_0203fbb0(void *, int, void *);
extern void MI_CpuCopy8(int, void *, int);

int func_02041140(int unused, int *out, int param)
{
    unsigned char buf1[8];
    unsigned char buf2[88];
    int i;
    int result;
    int count = 0;

    func_0209e29c(param, 1);
    for (i = 0; i < 5; i++) {
        MI_CpuCopy8(param, buf1, 8);
        result = func_0203fbb0(buf2, 7, buf1);
        if (result <= 0) {
            *out = 1;
            count++;
        } else {
            *out = 0;
        }
        func_0209e29c(param, 1);
        out++;
    }
    return count;
}
