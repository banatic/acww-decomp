/* func_02039cb4 @ 0x02039cb4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d368(int id, int index);

void func_02039cb4(int *self)
{
    int *p;
    int v;

    self[0x29] = 2;
    *((unsigned char *) self + 0xb4) = 1;

    if (self[3] == 0) {
        v = func_0209d368(0x137, 2) + 0x258;
    } else {
        v = func_0209d368(0x12d, 2) + 0x258;
    }

    self[0x2a] = v;
}