/* item_group_5: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204c100 @ 0x0204c100, 0x1e bytes, Thumb
 * func_0204c0d8 @ 0x0204c0d8, 0x28 bytes, Thumb
 * func_0204c0b0 @ 0x0204c0b0, 0x28 bytes, Thumb
 * func_0204c090 @ 0x0204c090, 0x1e bytes, Thumb
 * func_0204c078 @ 0x0204c078, 0x18 bytes, Thumb
 * func_0204c064 @ 0x0204c064, 0x14 bytes, Thumb
 * func_0204c048 @ 0x0204c048, 0x1a bytes, Thumb
 */

extern int func_0204b42c(void *param);
extern void func_0204b3cc(int a, int b);

int func_0204c0b0(void *param);

int func_0204c100(void *argument0)
{
    int r0;
    int r1;

    r0 = func_0204c0b0((void *) argument0);
    r1 = -1;
    if (r0 != r1) {
        r1 = r0 >> 3;
        r1 = r1 & 3;
    }
    r0 = r1;
    return r0;
}

int func_0204c0d8(unsigned short *p)
{
    int flag = 0;
    if (*p >= 0x1188u && *p <= 0x11A7u) {
        flag = 1;
    }
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}

int func_0204c0b0(void *param)
{
    int result;
    int temp;

    if (func_0204c0d8((unsigned short *) param) != 0) {
        temp = func_0204b42c(param);
        result = temp - 0x1188;
    } else {
        result = -1;
    }
    return result;
}

int func_0204c090(void *argument0)
{
    int r0;
    int r1;

    r0 = func_0204c0b0((void *) argument0);
    r1 = -1;
    if (r0 != r1) {
        r0 = r0 & 7;
    } else {
        r0 = r1;
    }
    return r0;
}

unsigned short func_0204c078(unsigned int param)
{
    unsigned short result;
    unsigned int temp;

    if (param < 0x20) {
        temp = param + 0x1188;
        result = (unsigned short) (temp << 16 >> 16);
    } else {
        result = 0x1188;
    }
    return result;
}

int func_0204c064(int a, int b)
{
    return (int) func_0204c078(((a & 3) << 3) + (b & 7));
}

void func_0204c048(int a, int b, int c)
{
    int temp;

    temp = func_0204c064(b, c);
    func_0204b3cc(a, temp);
}
