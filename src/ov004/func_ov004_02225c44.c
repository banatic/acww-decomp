/* func_ov004_02225c44 @ 0x02225c44, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void *parameter0);
extern int data_ov004_02258200;

int func_ov004_02225c44(void *arg0)
{
    if (func_0202ec14((void *) arg0) == 0) {
        return 0;
    } else {
        data_ov004_02258200 = 0;
        return 1;
    }
}
