/* number_text_3: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b4930 @ 0x020b4930, 0x1e bytes, Thumb
 * func_020b48ec @ 0x020b48ec, 0x44 bytes, Thumb
 * func_020b48b4 @ 0x020b48b4, 0x36 bytes, Thumb
 * func_020b488c @ 0x020b488c, 0x28 bytes, Thumb
 * func_020b4864 @ 0x020b4864, 0x28 bytes, Thumb
 */

extern int func_020b4950_unk(unsigned char *, unsigned char *, int);

void func_020b4930(signed char *arr, int end, int start, int offset)
{
    if (offset != 0) {
        int i = end - offset - 1;
        signed char *dest = arr + offset;
        while (i >= start) {
            dest[i] = arr[i];
            i--;
        }
    }
}

void func_020b48ec(char *out, int arg1, int num, int digits)
{
    int i;
    int limit;

    if (num == 0) {
        out[0] = 0;
        out[1] = '0';
    } else {
        i = 1;
        limit = digits * 2;
        while (i < limit && num != 0) {
            int q = num / 10;
            out[i] = (char) (0x30 + (num - q * 10));
            num = q;
            i += 2;
        }
    }
}

void func_020b48b4(unsigned char *p, unsigned char *q, int n)
{
    int ret;
    int diff;
    int i;

    ret = func_020b4950_unk(p, q, n);
    diff = 2 * n - ret;
    func_020b4930((signed char *) p, (int) q, 0, diff);
    for (i = diff - 1; i >= 0; i -= 2) {
        p[i] = 0x20;
        p[i - 1] = 0;
    }
}

void func_020b488c(unsigned char *buf, int a, int count)
{
    int i;
    i = func_020b4950_unk(buf, (unsigned char *) a, count);
    count = count << 1;
    while (i < count) {
        buf[i] = 0;
        buf[i + 1] = 32;
        i += 2;
    }
}

void func_020b4864(char *p, int b, int c)
{
    int i;
    int end;
    i = func_020b4950_unk((unsigned char *) ((int) p), (unsigned char *) b, c);
    end = c * 2;
    for (; i < end; i += 2) {
        p[i] = 0;
        p[i + 1] = 0x30;
    }
}
