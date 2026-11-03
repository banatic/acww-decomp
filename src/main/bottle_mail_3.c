/* bottle_mail_3: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02097f28 @ 0x02097f28, 0x10 bytes, Thumb
 * func_02097f18 @ 0x02097f18, 0x10 bytes, Thumb
 * func_02097f14 @ 0x02097f14, 0x2 bytes, Thumb
 * func_02097f00 @ 0x02097f00, 0x14 bytes, Thumb
 * func_02097edc @ 0x02097edc, 0x24 bytes, Thumb
 * func_02097eb0 @ 0x02097eb0, 0x2c bytes, Thumb
 * func_02097e94 @ 0x02097e94, 0x1c bytes, Thumb
 * func_02097e38 @ 0x02097e38, 0x5a bytes, Thumb
 */

extern void func_02066694(unsigned int param);
extern void func_02066688(int);
extern void func_02066650(void *arg);
extern int func_020644cc(int size);

void func_02097e94(unsigned char *param0);

unsigned int func_02097f28(unsigned int param)
{
    func_02066694(param);
    return param;
}

int func_02097f18(int arg)
{
    func_02066688(arg);
    return arg;
}

void *func_02097f14(void *buffer)
{
    return buffer;
}

void func_02097f00(void *arg)
{
    func_02066650(arg);
    func_02097e94((unsigned char *) arg);
}

void func_02097edc(unsigned char *base, int bit)
{
    unsigned char *ptr;
    int byte_index;
    int bit_mask;

    ptr = base + 0x100;
    byte_index = bit >> 3;
    bit_mask = 1 << (bit & 7);
    ptr[byte_index] |= bit_mask;
}

int func_02097eb0(unsigned char *base, int index)
{
    int bit = index & 7;
    int mask = 1 << bit;
    int result = 1;
    if ((*(base + (index >> 3) + 0x100) & mask) == 0) {
        result = 0;
    }
    return result;
}

void func_02097e94(unsigned char *param0)
{
    int i;
    unsigned char *ptr;

    for (i = 0; i < 5; i++) {
        ptr = param0 + i;
        ptr[0x100] = 0;
    }
}

int func_02097e38(void *param)
{
    int i;
    int count;
    int rem;

    count = 0;
    for (i = 0; i < 0x28; i++) {
        if (func_02097eb0((unsigned char *) param, i) == 0) {
            count++;
        }
    }

    if (count == 0) {
        func_02097e94((unsigned char *) param);
        count = 0x28;
    }

    rem = func_020644cc(count);

    for (i = 0; i < 0x28; i++) {
        if (func_02097eb0((unsigned char *) param, i) == 0) {
            if (rem > 0) {
                rem--;
            } else {
                return i;
            }
        }
    }

    return 0;
}
