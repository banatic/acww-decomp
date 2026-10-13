/* func_0209fd54 @ 0x0209fd54, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f3c14;
extern struct B data_021f40a4;
extern struct C data_021f3278;

extern int func_02050920(struct B *, int);
extern void func_02088214(struct B *, int);
extern void MI_CpuCopy8(struct B *, struct C *, int);
extern void MI_CpuFill8(struct B *, int, int);
extern void func_020881b8(struct B *, int);

void func_0209fd54(void)
{
    int result;
    struct C *pC;

    if (data_021f3c14 == 0) {
        return;
    }
    data_021f3c14 = 0;
    result = func_02050920(&data_021f40a4, 0x238);
    pC = &data_021f3278;
    if (result == 0) {
        func_02088214(&data_021f40a4, 1);
        MI_CpuCopy8(&data_021f40a4, pC, 0x238);
    }
    MI_CpuFill8(&data_021f40a4, 0, 0x238);
    func_020881b8(&data_021f40a4, 1);
}
