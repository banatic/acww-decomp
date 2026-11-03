/* vram_frame: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b96f8 @ 0x020b96f8, 0xbc bytes, Thumb
 * func_020b962c @ 0x020b962c, 0xcc bytes, Thumb
 * func_020b95f4 @ 0x020b95f4, 0x38 bytes, Thumb
 * func_020b95b4 @ 0x020b95b4, 0x40 bytes, Thumb
 * func_020b958c @ 0x020b958c, 0x28 bytes, Thumb
 */

extern unsigned int data_021f6c90;
extern unsigned int data_021f6c80;
extern unsigned int data_021f6c8c;
extern unsigned int data_021f6c7c;
extern unsigned int data_021f6c84;
extern unsigned int data_021f6c74;
extern unsigned int data_021f6c88;
extern unsigned int data_021f6c78;
extern void func_020b9478(void);
extern void OS_Terminate(void);
extern unsigned int data_021f6c70;
extern unsigned int data_021f6c94;

void func_020b96f8(unsigned int *out1, unsigned int *out2, unsigned int size)
{
    if (data_021f6c90 + size <= data_021f6c80 && data_021f6c8c + (size >> 1) <= data_021f6c7c) {
        *out1 = data_021f6c90;
        *out2 = data_021f6c8c;
        data_021f6c90 += size;
        data_021f6c8c += (size >> 1);
    } else if (data_021f6c84 + size <= data_021f6c74 && data_021f6c84 + size <= 0x60000 &&
               data_021f6c88 + (size >> 1) <= data_021f6c78) {
        *out1 = data_021f6c84;
        *out2 = data_021f6c88;
        data_021f6c84 += size;
        data_021f6c88 += (size >> 1);
    } else {
        func_020b9478();
        OS_Terminate();
        *out1 = 0;
        *out2 = 0x20000;
    }
}

void func_020b962c(unsigned int *out, unsigned int n)
{
    unsigned int a, b;

    a = data_021f6c74 - data_021f6c84;
    b = data_021f6c78 - data_021f6c88;
    if (a >= n) {
        if (b >= n && (b - n) * 2 > (a - n)) {
            *out = data_021f6c78 - n;
            data_021f6c78 = *out;
        } else {
            *out = data_021f6c74 - n;
            data_021f6c74 = *out;
        }
    } else if (b >= n) {
        *out = data_021f6c78 - n;
        data_021f6c78 = *out;
    } else {
        a = data_021f6c80 - data_021f6c90;
        b = data_021f6c7c - data_021f6c8c;
        if (a >= n) {
            if (b >= n && (b - n) * 2 > (a - n)) {
                *out = data_021f6c7c - n;
                data_021f6c7c = *out;
            } else {
                *out = data_021f6c80 - n;
                data_021f6c80 = *out;
            }
        } else if (b >= n) {
            *out = data_021f6c7c - n;
            data_021f6c7c = *out;
        } else {
            func_020b9478();
            OS_Terminate();
            *out = 0;
        }
    }
}

unsigned int func_020b95f4(unsigned int size)
{
    unsigned int old = data_021f6c70;
    unsigned int aligned = (size + 0xF) & 0xFFF0;
    unsigned int new = old + aligned;

    data_021f6c70 = new;
    if (new >= data_021f6c94) {
        data_021f6c70 = old;
        OS_Terminate();
        return 0;
    } else {
        return old;
    }
}

unsigned int func_020b95b4(unsigned int a, unsigned int b)
{
    unsigned int x, y;

    if (b) {
        func_020b96f8(&x, &y, a);
    } else {
        func_020b962c(&x, a);
    }

    return (b << 31) | (((a >> 4) << 16) | ((x >> 3) & 0xffff));
}

unsigned int func_020b958c(unsigned int p)
{
    unsigned int v;
    p = (p + 7) & ~7;
    v = func_020b95f4(p);
    return ((p >> 3) << 16) | ((v >> 3) & 0xffff);
}
