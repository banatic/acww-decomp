/* item_group: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204b238 @ 0x0204b238, 0x28 bytes, Thumb
 * func_0204b230 @ 0x0204b230, 0x8 bytes, Thumb
 * func_0204b208 @ 0x0204b208, 0x28 bytes, Thumb
 * func_0204b200 @ 0x0204b200, 0x8 bytes, Thumb
 * func_0204b1d8 @ 0x0204b1d8, 0x28 bytes, Thumb
 * func_0204b1d0 @ 0x0204b1d0, 0x8 bytes, Thumb
 * func_0204b1b8 @ 0x0204b1b8, 0x18 bytes, Thumb
 * func_0204b1a0 @ 0x0204b1a0, 0x18 bytes, Thumb
 * func_0204b188 @ 0x0204b188, 0x18 bytes, Thumb
 */

int func_0204b238(unsigned short *p)
{
    int result;
    result = 0;
    if (*p >= 0x1380 && *p <= 0x139f) {
        result = 1;
    }
    if (result) {
        return 1;
    }
    return 0;
}

void func_0204b230(unsigned short *argument0)
{
    func_0204b238((unsigned short *) argument0);
}

int func_0204b208(unsigned short *p)
{
    int flag = 0;
    unsigned int val = *p;
    if (val >= 0x1100 && val <= 0x1143) {
        flag = 1;
    }
    if (flag) {
        return 1;
    }
    return 0;
}

void func_0204b200(unsigned short *argument0)
{
    func_0204b208((unsigned short *) argument0);
}

int func_0204b1d8(unsigned short *ptr)
{
    int result = 0;
    if (*ptr >= 0x13a8 && *ptr <= 0x13c7) {
        result = 1;
    }
    if (result) {
        return 1;
    }
    return 0;
}

void func_0204b1d0(unsigned short *argument0)
{
    func_0204b1d8((unsigned short *) argument0);
}

unsigned short func_0204b1b8(unsigned int param)
{
    unsigned short result;

    if (param < 0x20) {
        result = (unsigned short) (param + 0x1380);
    } else {
        result = 0x1380;
    }

    return result;
}

unsigned short func_0204b1a0(unsigned short arg0)
{
    unsigned short val;

    if (arg0 < 0x44) {
        val = (unsigned short) (arg0 + 0x1100);
    } else {
        val = 0x1100;
    }
    return val;
}

unsigned short func_0204b188(unsigned int a)
{
    if (a < 0x20) {
        return (unsigned short) (a + 0x13a8);
    }
    return 0x13a8;
}
