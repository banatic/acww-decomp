/* func_0200fbe0 @ 0x0200fbe0, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200fc90(void *);

int func_0200fbe0(void *argument0)
{
    int x;
    unsigned short v;

    x = func_0200fc90((void *) argument0);
    if (x <= 0) {
        return 0;
    }

    v = (unsigned short) (x + 0x1368);

    if (v <= 0x136a) {
        return 1;
    }
    if (v <= 0x1373) {
        return 2;
    }
    if (v <= 0x1375) {
        return 3;
    }
    if (v <= 0x1377) {
        return 4;
    }
    if (v <= 0x1379) {
        return 5;
    }
    if (v <= 0x137b) {
        return 6;
    }
    if (v == 0x137c) {
        return 7;
    }
    if (v == 0x137d) {
        return 8;
    }
    if (v <= 0x137f) {
        return 9;
    }
    if (v <= 0x13a7) {
        return 10;
    }

    return 0;
}
