/* func_ov004_02224b0c @ 0x02224b0c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void *parameter0);
extern int data_ov004_022580dc;

int func_ov004_02224b0c(void *arg0)
{
    if (func_0202ec14((void *) arg0) == 0) {
        return 0;
    } else {
        data_ov004_022580dc = 0;
        return 1;
    }
}
