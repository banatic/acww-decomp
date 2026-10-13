/* func_020b8d74 @ 0x020b8d74, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(int);
extern void func_020b88c0(int *);
extern int data_021f6c20;
extern int data_021f6b20;

void func_020b8d74(int param)
{
    int x = func_020b65c4(param);
    int flag = 0;

    if (!((unsigned char) (x + 0xf4) <= 2 || (unsigned char) (x + 0xd2) <= 1)) {
        flag = 1;
    }

    if (flag) {
        data_021f6c20 = param;
        func_020b88c0(&data_021f6b20);
    }
}
