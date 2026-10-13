/* func_ov121_0229af00 @ 0x0229af00, 0x40 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_ov121_0229c228[];
extern unsigned short data_ov121_0229c218[];
extern void func_0206fdd4(void *, int, int, int, int, int);
extern void func_ov121_02299a4c(void *, int);

void func_ov121_0229af00(void *arg0, int arg1, int arg2)
{
    int idx;
    unsigned short x, y;

    idx = arg1 - 9;
    x = data_ov121_0229c228[idx];
    y = data_ov121_0229c218[idx];
    func_0206fdd4((char *) arg0 + 0x98c, y, x, y + 3, x + 3, arg2);
    func_ov121_02299a4c(arg0, 2);
}
