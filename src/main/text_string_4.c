/* text_string_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02051c14 @ 0x02051c14, 0x76 bytes, Thumb
 * func_02051c08 @ 0x02051c08, 0xc bytes, Thumb
 * func_02051bf8 @ 0x02051bf8, 0x10 bytes, Thumb
 * func_02051bb4 @ 0x02051bb4, 0x44 bytes, Thumb
 */

extern int func_02051ce0(const unsigned short *a, int b, int e);
extern int func_02051d30(unsigned short value);
extern void MI_CpuCopy8(int a, int b, int c);
extern void MI_CpuFill8(int a, int b, int c);
extern int func_02051ca8(const unsigned short *a, int b);

int func_02051c14(const unsigned short *a, int b, int c, int *d, int e)
{
    int i;
    int sum = 0;
    int count = func_02051ce0(a, b, e);

    for (i = 0; i < count; i++) {
        sum += func_02051d30(a[i]);
        if (sum > c) {
            *d = i;
            return 1;
        }
    }
    *d = count;
    if (count == b) {
        return a[count - 1] == 10 ? 3 : 2;
    }
    if (count == 0) {
        return 0;
    }
    return a[count - 1] == 10 ? 3 : 0;
}

void func_02051c08(int a, int b, int c)
{
    MI_CpuCopy8(a, b, c << 1);
}

void func_02051bf8(int a, int b)
{
    MI_CpuFill8(a, 0, b << 1);
}

int func_02051bb4(const unsigned short *a, const unsigned short *b, int c)
{
    int len1;
    int len2;
    int i;

    len1 = func_02051ca8(a, c);
    len2 = func_02051ca8(b, c);
    if (len1 != len2) {
        return 0;
    }
    for (i = 0; i < len1; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}
