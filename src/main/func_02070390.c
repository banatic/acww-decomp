/* func_02070390 @ 0x02070390, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205cb00(int, int);
extern void func_020700b8(void);
extern void func_0206ef70(void);
extern void func_02051d40(void);

extern int data_021cfccc[3];
extern int data_021cfcb4[3];
extern struct {
    char a;
    char b;
} data_020df328;
extern int data_021cfc84;
extern short data_021cfc6c;
extern int data_021cfc8c;
extern int data_021cfc74;

int func_02070390(int param)
{
    func_0205cb00(0x8c00, 0);
    data_021cfccc[2] = 0;
    data_021cfccc[1] = 0;
    data_021cfccc[0] = 0;
    data_021cfcb4[2] = 0;
    data_021cfcb4[1] = 0;
    data_021cfcb4[0] = 0;
    data_020df328.b = 0x2e;
    data_020df328.a = 1;
    data_021cfc84 = param;
    data_021cfc6c = 0;
    func_020700b8();
    func_0206ef70();
    data_021cfc8c = 0;
    func_02051d40();
    data_021cfc74 = 0;
    return 1;
}
