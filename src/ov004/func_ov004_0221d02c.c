/* func_ov004_0221d02c @ 0x0221d02c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0221d08c(void *parameter0);
extern int func_020819bc(void *object);

int func_ov004_0221d02c(void *arg0)
{
    int object;
    if ((object = func_ov004_0221d08c((void *) arg0)) != 0) {
        if (func_020819bc((void *) object) == 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}
