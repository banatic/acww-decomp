/* func_ov004_022226d4 @ 0x022226d4, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207b410(unsigned int argument0);
extern int func_020984e8(void);
extern int func_02099870(int argument0);
extern void func_0209a664(int arg0, int arg1);
extern void *data_021e5a2c;

void func_ov004_022226d4(void)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_0207b410((unsigned int) (&data_021e5a2c));
    func_0209a664(v1, func_02099870(func_020984e8()));
}
