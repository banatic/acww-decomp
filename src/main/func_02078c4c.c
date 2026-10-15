/* func_02078c4c @ 0x02078c4c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0205c300(int);
extern void func_02078bfc(unsigned int param);
extern int func_020e9abc(unsigned int param);
extern unsigned int data_021c9ac0;

extern unsigned char data_021d1310[];

void func_02078c4c(int argument0)
{
    func_0205c300((int) argument0);
    func_02078bfc((unsigned int) data_021d1310);
    if (data_021c9ac0) {
        func_020e9abc(data_021c9ac0);
    }
}
