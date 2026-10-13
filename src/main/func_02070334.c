/* func_02070334 @ 0x02070334, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021cfcb4[3];
extern unsigned int data_021cfccc[3];
extern unsigned int data_021cfca0;
extern unsigned int data_021cfc84;
extern unsigned char data_020df328[2];
extern void func_020701a8(void);
extern void func_0206ef34(void);
extern void func_0205cae4(void);
extern void func_02065c68(void *);

int func_02070334(void)
{
    data_021cfcb4[0] |= data_021cfccc[0];
    data_021cfcb4[1] |= data_021cfccc[1];
    data_021cfcb4[2] |= data_021cfccc[2];
    func_020701a8();
    func_0206ef34();
    func_0205cae4();
    func_02065c68(&data_021cfca0);
    data_020df328[1] = 0x2e;
    data_020df328[0] = 0;
    data_021cfc84 = 0;
    return 1;
}
