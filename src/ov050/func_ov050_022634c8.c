/* func_ov050_022634c8 @ 0x022634c8, 0x170 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O1,s
 */

extern char data_021dc7a8[];
extern char data_021ebcd4[];
extern int func_02060d3c(void *p);
extern int func_02060e78(void *p);
extern int func_02060cbc(void *p);
extern int func_0209f150(void *p, int k);
extern int func_02060e88(void *p);
extern void func_0209f100(void *p, int k);
extern void func_0209f128(void *p, int k);

int func_ov050_022634c8(void)
{
    char *g;
    char *h;
    int a, b, c;

    g = data_021dc7a8;
    h = data_021ebcd4;
    a = func_02060d3c(h);
    b = func_02060e78(h);
    c = func_02060cbc(h);
    if (func_0209f150(data_021dc7a8, 0xe) != 0) {
        return 0;
    }
    if (a == 0 && b == 0 && func_02060e88(g + 0xf52c) == 0) {
        return 0x41;
    }
    if (b == 1 && c != 0) {
        func_0209f100(data_021dc7a8, 0xd);
        return 0x49;
    }
    if (a == 0 && b == 1 && func_02060e88(g + 0xf52c) == 0) {
        return 0x4a;
    }
    if (b == 2 && c != 0) {
        func_0209f100(data_021dc7a8, 0xd);
        return 0x4b;
    }
    if (a == 0 && b == 2 && func_02060e88(g + 0xf52c) == 0) {
        return 0x4c;
    }
    if (b == 3 && c != 0) {
        func_0209f100(data_021dc7a8, 0xd);
        return 0x4d;
    }
    if (a == 0 && b == 3 && func_02060e88(g + 0xf52c) == 0) {
        return 0x4e;
    }
    if (b == 4 && c != 0) {
        func_0209f100(data_021dc7a8, 0xd);
        return 0x4f;
    }
    if (a == 0 && b == 4 && func_02060e88(g + 0xf52c) == 0) {
        return 0x50;
    }
    if (b == 5 && c != 0) {
        func_0209f100(data_021dc7a8, 0xd);
        return 0x51;
    }
    if (a == 0 && b == 5 && func_02060e88(g + 0xf52c) == 0) {
        return 0x52;
    }
    if (b == 6 && c != 0) {
        func_0209f100(data_021dc7a8, 0xd);
        return 0x53;
    }
    if (a == 0 && b == 6 && func_02060e88(g + 0xf52c) == 0) {
        func_0209f128(data_021dc7a8, 0xe);
        return 0x54;
    }
    return 0;
}
