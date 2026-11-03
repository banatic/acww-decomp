/* map_code: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204bc14 @ 0x0204bc14, 0x14 bytes, Thumb
 * func_0204bbec @ 0x0204bbec, 0x28 bytes, Thumb
 * func_0204bbd4 @ 0x0204bbd4, 0x18 bytes, Thumb
 * func_0204bbbc @ 0x0204bbbc, 0x18 bytes, Thumb
 * func_0204bba8 @ 0x0204bba8, 0x14 bytes, Thumb
 * func_0204bb80 @ 0x0204bb80, 0x28 bytes, Thumb
 * func_0204bb68 @ 0x0204bb68, 0x18 bytes, Thumb
 * func_0204bb54 @ 0x0204bb54, 0x14 bytes, Thumb
 * func_0204bb2c @ 0x0204bb2c, 0x28 bytes, Thumb
 * func_0204bb14 @ 0x0204bb14, 0x18 bytes, Thumb
 * func_0204bb00 @ 0x0204bb00, 0x14 bytes, Thumb
 * func_0204bae8 @ 0x0204bae8, 0x18 bytes, Thumb
 */

extern int func_0204b42c(int);
extern int func_0204b48c(int, int, int);

int func_0204bc14(void *a)
{
    return func_0204b48c((int) a, 0x5000, 0x5021);
}

int func_0204bbec(int a)
{
    return (func_0204b42c(a) == 0x0000f030) || (func_0204bc14((void *) a) != 0);
}

extern unsigned short func_0204bbd4(unsigned int a)
{
    unsigned int v;
    if (a < 0x22) {
        v = a + 0x5000;
    } else {
        v = 0x5000;
    }
    return (unsigned short) v;
}

unsigned short func_0204bbbc(unsigned int x)
{
    unsigned int y;
    if (x < 8) {
        y = x + 0x5001;
    } else {
        y = 0x5001;
    }
    return (unsigned short) y;
}

int func_0204bba8(int a)
{
    return func_0204b48c(a, 0x500d, 0x5010);
}

int func_0204bb80(int arg0)
{
    int val;
    int val2;

    if (func_0204bba8(arg0) != 0) {
        val = func_0204b42c(arg0);
        val2 = val - 0x500d;
    } else {
        val2 = -1;
    }
    return val2;
}

unsigned short func_0204bb68(unsigned int x)
{
    if (x < 4) {
        x = x + 0x500d;
    } else {
        x = 0x500d;
    }
    return (unsigned short) x;
}

int func_0204bb54(int arg0)
{
    return func_0204b48c(arg0, 0xb001, 0xb003);
}

int func_0204bb2c(int arg0)
{
    int val;
    int val2;

    if (func_0204bb54(arg0) != 0) {
        val = func_0204b42c(arg0);
        val2 = val - 0xb001;
        return val2;
    }
    return -1;
}

unsigned short func_0204bb14(unsigned int r0)
{
    if (r0 < 3U) {
        r0 += 0xb001;
    } else {
        r0 = 0xb001;
    }
    return (unsigned short) (r0 & 0xffff);
}

int func_0204bb00(int a)
{
    return func_0204b48c(a, 0x5014, 0x501a);
}

unsigned short func_0204bae8(unsigned int param)
{
    if (param < 7) {
        param += 0x5014;
    } else {
        param = 0x5014;
    }
    return (unsigned short) param;
}
