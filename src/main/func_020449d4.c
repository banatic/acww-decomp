/* func_020449d4 @ 0x020449d4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f794(void *dst, int a, int b);
extern int func_02090c2c(int id, void *buf, int c, void *d);
extern int data_020e25d4;

void func_020449d4(unsigned short *kind, int *data)
{
    int id;
    char buf[16];

    switch (*kind) {
        case 0x1f:
            id = 0x77;
            break;
        case 0x20:
            id = 0x78;
            break;
        default:
            id = 0x76;
            break;
    }

    func_0204f794(buf, data[0], data[1]);
    func_02090c2c(id, buf, 0, &data_020e25d4);
}
