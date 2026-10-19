/* func_020390b4 @ 0x020390b4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void *func_02094fd4(int *);
extern void *func_0203a404(int *);
extern int func_02099870(int);
extern void *func_02095074(int, int *);
extern int func_020b4980(int *, unsigned char *, int);
extern void func_020398e8(int, int *, int *);
extern void func_0200467c(int);
extern void *func_0203a3ec(int *);
extern void *func_02094fbc(int *);

extern int data_021c6730;
extern int *data_020ccf94;

void func_020390b4(void)
{
    unsigned char local3;
    int local1[8];
    int local2[13];
    int result;

    result = func_020984e8();
    if (data_021c6730 > 0) {
        return;
    }
    if (result == 0) {
        return;
    }

    func_02094fd4(local1);
    func_0203a404(local2);
    func_02095074(func_02099870(result), local1);
    local3 = 0xEF;
    func_020b4980(local2, &local3, 0);
    func_020398e8(data_020ccf94[0x19], local1, local2);
    func_0200467c(0x32);
    data_021c6730 = 0x1e;
    func_0203a3ec(local2);
    func_02094fbc(local1);
}
