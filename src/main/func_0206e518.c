/* func_0206e518 @ 0x0206e518, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e98f4(unsigned int a, unsigned int b);
extern void func_02077b70(int *p, int n);
extern int func_0210172c(int a);
extern void func_02077b9c(int *p);
extern void func_020e9898(int a);

extern int data_021d11c4;
extern unsigned char data_020df29c;
extern int SDK_OVERLAY_ov065_ID;

int func_0206e518(void)
{
    int a;
    int b;

    a = func_020e98f4(0x700, 0x20);
    func_02077b70(&data_021d11c4, (int) &SDK_OVERLAY_ov065_ID);
    b = func_0210172c(a);
    data_020df29c = (unsigned char) b;
    func_02077b9c(&data_021d11c4);
    func_020e9898(a);
    return b;
}
