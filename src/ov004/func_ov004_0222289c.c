/* func_ov004_0222289c @ 0x0222289c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202e1dc(void *parameter0);
extern int data_ov004_02257f7c;

int func_ov004_0222289c(void *arg0)
{
    if (func_0202e1dc((void *) arg0) == 0) {
        return 0;
    } else {
        data_ov004_02257f7c = 0;
        return 1;
    }
}
