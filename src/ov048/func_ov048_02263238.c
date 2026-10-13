/* func_ov048_02263238 @ 0x02263238, 0x4c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(unsigned int);
extern void func_ov004_02246f90(void);
extern void func_02095ab0(unsigned int *, unsigned int, int);
extern void func_02095eec(int, int);
extern unsigned int data_ov048_02263980[3];

int func_ov048_02263238(unsigned int p)
{
    unsigned int local[3];

    if (func_02014868(p + 0x618) == 0) {
        func_ov004_02246f90();
        local[0] = data_ov048_02263980[0];
        local[1] = data_ov048_02263980[1];
        local[2] = data_ov048_02263980[2];
        func_02095ab0(local, 0x400, 4);
        func_02095eec(1, 4);
        return 1;
    }
    return 0;
}
