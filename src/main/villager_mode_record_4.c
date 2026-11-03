/* villager_mode_record_4: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209c53c @ 0x0209c53c, 0x10 bytes, Thumb
 * func_0209c538 @ 0x0209c538, 0x2 bytes, Thumb
 * func_0209c52c @ 0x0209c52c, 0xc bytes, Thumb
 * func_0209c51c @ 0x0209c51c, 0x10 bytes, Thumb
 * func_0209c4a8 @ 0x0209c4a8, 0x72 bytes, Thumb
 */

extern void MI_CpuFill8(void *arg0, int arg1, int arg2);
extern void MI_CpuCopy8(int a, int b, int c);
extern int func_020644cc(int);

void func_0209c52c(void *arg0);

int func_0209c53c(int arg)
{
    func_0209c52c((void *) arg);
    return arg;
}

void func_0209c538(void *object) {}

void func_0209c52c(void *arg0)
{
    MI_CpuFill8(arg0, 0, 8);
}

void func_0209c51c(int a, int b)
{
    MI_CpuCopy8(b, a, 8);
}

int func_0209c4a8(const unsigned char *data)
{
    unsigned char result = 8;
    unsigned short mask = 0;
    int prev = -1;
    int count = 0;
    int i, j;
    int rnd;

    for (i = 0; i < 8; i++) {
        unsigned char c = data[i];
        if (c > prev) {
            prev = c;
            mask = (1 << i);
            count = 1;
        } else if (prev == c) {
            mask |= (1 << i);
            count++;
        }
    }

    if (count > 0) {
        rnd = func_020644cc(count);
        for (j = 0; j < 8; j++) {
            if ((mask >> j) & 1) {
                if (rnd == 0) {
                    result = (unsigned char) j;
                    break;
                }
                rnd--;
            }
        }
    }
    return result;
}
