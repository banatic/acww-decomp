/* item_code_2: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204bd5c @ 0x0204bd5c, 0x28 bytes, Thumb
 * func_0204bd40 @ 0x0204bd40, 0x1c bytes, Thumb
 * func_0204bd20 @ 0x0204bd20, 0x20 bytes, Thumb
 * func_0204bd08 @ 0x0204bd08, 0x18 bytes, Thumb
 * func_0204bcf8 @ 0x0204bcf8, 0x10 bytes, Thumb
 * func_0204bcdc @ 0x0204bcdc, 0x1c bytes, Thumb
 * func_0204bcd4 @ 0x0204bcd4, 0x8 bytes, Thumb
 * func_0204bcb4 @ 0x0204bcb4, 0x20 bytes, Thumb
 * func_0204bc90 @ 0x0204bc90, 0x22 bytes, Thumb
 * func_0204bc7c @ 0x0204bc7c, 0x12 bytes, Thumb
 * func_0204bc64 @ 0x0204bc64, 0x18 bytes, Thumb
 * func_0204bc50 @ 0x0204bc50, 0x14 bytes, Thumb
 * func_0204bc28 @ 0x0204bc28, 0x26 bytes, Thumb
 */

extern int func_0204b268(int arg);
extern int func_0204b42c(unsigned short *);
extern unsigned int abs_00003000;

int func_0204bcf8(unsigned short *ptr);

int func_0204bd5c(int arg)
{
    if (func_0204b268(arg) != 0) {
        return (func_0204b42c((unsigned short *) arg) - 0x1000) >> 2;
    } else {
        return -1;
    }
}

int func_0204bd40(unsigned short *argument0)
{
    int r0;
    int r1;

    r0 = func_0204b42c((unsigned short *) argument0);
    r1 = r0 - 0x1000;
    r1 &= 3;
    r0 = r1 + 1;
    return r0;
}

unsigned short func_0204bd20(unsigned int param0, unsigned int param1)
{
    unsigned int r2;
    unsigned int r1;
    unsigned int r0;

    if (param0 < 0x40) {
        r2 = param0 * 4 + 0x1000;
    } else {
        r2 = 0x1000;
    }

    r1 = param1 - 1;
    r0 = 3;
    r1 = r1 & r0;
    r0 = r1 + r2;
    r0 = r0 << 16;
    r0 = r0 >> 16;
    return (unsigned short) r0;
}

int func_0204bd08(unsigned short *argument0)
{
    int result;
    if (func_0204bcf8((unsigned short *) argument0) == 1) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_0204bcf8(unsigned short *ptr)
{
    return (*ptr & 0xF000) >> 12;
}

int func_0204bcdc(void *p)
{
    switch (func_0204bcf8(p)) {
        case 3:
        case 4:
            return 1;
    }
    return 0;
}

void func_0204bcd4(void *argument0)
{
    func_0204bcdc((void *) argument0);
}

int func_0204bcb4(unsigned short *argument0)
{
    int result;
    int value;

    value = func_0204b42c((unsigned short *) argument0);
    if (value == 0x0000f031) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_0204bc90(int arg)
{
    return func_0204bcb4((unsigned short *) arg) != 0 || func_0204bcdc((void *) arg) != 0;
}

int func_0204bc7c(unsigned short *argument0)
{
    int result;
    result = func_0204b42c((unsigned short *) argument0);
    return result & 3;
}

int func_0204bc64(unsigned short *argument0)
{
    int result;
    result = func_0204b42c((unsigned short *) argument0);
    result -= 0x3000;
    return result >> 2;
}

unsigned short func_0204bc50(int x, int y)
{
    return (unsigned short) ((x << 2) + (unsigned int) &abs_00003000 + y);
}

void func_0204bc28(short *dest, int arg1)
{
    if (func_0204bcdc((void *) dest) != 0) {
        *dest = (short) func_0204bc50(func_0204bc64((unsigned short *) dest), arg1);
    }
}
