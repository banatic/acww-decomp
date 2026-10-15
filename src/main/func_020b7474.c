/* func_020b7474 @ 0x020b7474, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off

extern unsigned char data_020e54a8;
extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223cd58(int, int);

int func_020b7474(int arg)
{
    int cond = (data_020e54a8 == 1);
    if (cond) {
        return func_ov004_0223cd58((int) func_ov004_0223ce84(), arg);
    }
    return 0;
}
