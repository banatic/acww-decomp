/* func_ov121_0229b8c0 @ 0x0229b8c0, 0x88 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002d14(int, int, int, int, int, int);
extern void func_02002c6c(int, int, int, int, int, int);
extern void func_02064af4(int, int, int);
extern int func_ov121_0229adac(int, int);
extern void func_ov121_0229af00(int, int, int);
extern void func_ov121_02299a4c(int, int);
extern unsigned int data_021fbe94;
extern int data_ov121_0229c438;
extern int data_ov121_0229c450;
extern int data_ov121_0229c468;

void func_ov121_0229b8c0(int param)
{
    unsigned int tmp = data_021fbe94;
    unsigned char i;
    int seven = 7;

    func_02002d14((int) &data_ov121_0229c438, tmp, 6, 1, 1, 7);
    func_02002c6c((int) &data_ov121_0229c450, tmp, 6, 0x10, 0x10, 0xc5);
    func_02064af4((int) &data_ov121_0229c468, param + 0x98c, 0x800);

    i = 9;
    do {
        if (func_ov121_0229adac(param, i) != 0) {
            func_ov121_0229af00(param, i, seven);
        }
        i++;
    } while (i <= 15);

    func_ov121_02299a4c(param, 2);
}
