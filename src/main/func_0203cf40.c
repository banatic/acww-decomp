/* func_0203cf40 @ 0x0203cf40, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0203cf40(unsigned char *p)
{
    unsigned int i;
    for (i = 0; i < 0x100; i++) {
        p[i] = 0;
    }
    for (i = 0; i < 9; i++) {
        (p + i)[0x100] = 0;
    }
    for (i = 0; i < 9; i++) {
        (p + i)[0x109] = 0;
    }
    for (i = 0; i < 9; i++) {
        (p + i)[0x112] = 0;
    }
    for (i = 0; i < 8; i++) {
        (p + i)[0x11b] = 0;
    }
}
