/* func_0202c2c4 @ 0x0202c2c4, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern signed char data_020c892c[];
extern int data_020c8b40;
extern int func_020644cc(int);
extern void func_02015de4(void *self, unsigned short *p, int a, int b);

void *func_0202c2c4(void *self, int param)
{
    int idx;
    unsigned short val;

    idx = param;
    if (param == -1) {
        idx = data_020c892c[func_020644cc(2)];
    }
    if (idx == -1) {
        goto done;
    }
    val = ((unsigned int) idx < 0x38) ? (unsigned short) (idx + 0x12b0) : 0x12b0;
    func_02015de4(self, &val, 0, 7);
done:
    return &data_020c8b40;
}
