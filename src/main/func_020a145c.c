/* func_020a145c @ 0x020a145c, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021dc7a8;
extern int data_021ee418;
extern int data_021f37f4;
extern int data_021c8188;
extern int data_020d1c20[3];

extern int func_0209015c(int);
extern int func_020508fc(int, int, int);
extern void func_02090168(int, int);
extern int func_0208ffe8(int);
extern void func_0208fff4(int, int);
extern int func_02050af8(int, int, int, int);

int func_020a145c(void)
{
    volatile char pad[4];
    unsigned int a, b, d1, d2;
    d1 = (unsigned int) &data_021ee418 - (unsigned int) &data_021dc7a8;
    d2 = (unsigned int) &data_021f37f4 - (unsigned int) &data_021dc7a8;
    func_02090168((int) &data_021ee418, func_020508fc((int) &data_021ee418, 0x950, func_0209015c((int) &data_021ee418)));
    func_0208fff4((int) &data_021f37f4, func_020508fc((int) &data_021f37f4, 0x104, func_0208ffe8((int) &data_021f37f4)));
    a = data_020d1c20[0];
    if (func_02050af8((int) &data_021c8188, a + d1, (int) &data_021ee418, 0x950) == 1) {
        return 1;
    }
    b = data_020d1c20[1];
    if (func_02050af8((int) &data_021c8188, b + d1, (int) &data_021ee418, 0x950) == 1) {
        return 1;
    }
    if (func_02050af8((int) &data_021c8188, a + d2, (int) &data_021f37f4, 0x104) == 1) {
        return 1;
    }
    if (func_02050af8((int) &data_021c8188, b + d2, (int) &data_021f37f4, 0x104) == 1) {
        return 1;
    }
    return 0;
}
