/* func_020b15b8 @ 0x020b15b8, 0x144 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b1758(void);
extern unsigned char *func_020b1768(unsigned short a);
extern void func_020b1730(unsigned char a);
extern int func_020b16fc(int a);

void func_020b15b8(unsigned short *arr, int *out1, int *out2)
{
    int min;
    int i;
    unsigned char *p;
    int max;
    int zero;
    int k;
    unsigned char b0, b1;
    int r4;
    int r5;
    int r6;
    int val;
    int val2;
    int val3;
    int var1c;
    int val4;
    int var2c;

    func_020b1758();

    min = 0x20;
    i = 0;
    max = ~i;
    zero = i;

    for (; i < 0x10; i++) {
        if (arr[i] != 0xffff) {
            p = func_020b1768(arr[i]);
            k = zero;
            while (k < 4) {
                b0 = p[0];
                b1 = p[1];
                p += 2;
                if (b0 != 0xff) {
                    func_020b1730(b0);
                    if (min > b1) {
                        min = b1;
                    }
                    if (max < b1) {
                        max = b1;
                    }
                } else {
                    k = 4;
                }
                k++;
            }
        }
    }

    r4 = 0;
    goto loop2_check;
    do {
        r4++;
    loop2_check:
        if (r4 >= 0x40) {
            break;
        }
    } while (func_020b16fc(r4) == 0);

    r5 = (r4 - 1) & 0x3f;
    r6 = r4;
    val = 0;
    val2 = 0;
    val3 = 0;

    while (val == 0 && r5 != r6) {
        if (func_020b16fc(r5) != 0) {
            val2 = val3;
            r6 = r5;
        } else if (val2 != 0) {
            val = 1;
        } else {
            val2 = 1;
        }
        r5 = (r5 - 1) & 0x3f;
    }

    if (val != 0) {
        r5 = (r4 + 1) & 0x3f;
        var1c = 0;
        val4 = 0;
        var2c = 0;
        while (var1c == 0 && r5 != r4) {
            if (func_020b16fc(r5) != 0) {
                val4 = var2c;
                r4 = r5;
            } else if (val4 != 0) {
                var1c = 1;
            } else {
                val4 = 1;
            }
            r5 = (r5 + 1) & 0x3f;
        }
    } else {
        r4 = 0;
        r6 = r4;
    }

    if (r6 <= r4) {
        *out1 = (r6 + r4 + 1) << 2;
    } else {
        r6 += 0x41;
        *out1 = ((r6 + r4) << 2) & 0x1ff;
    }

    *out2 = ((min << 3) + ((max << 3) + 8)) >> 1;
}
