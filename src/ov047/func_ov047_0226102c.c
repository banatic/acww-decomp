/* func_ov047_0226102c @ 0x0226102c, 0x28 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209f150(void *p, int n);
extern int data_021dc7a8;

void func_ov047_0226102c(int *p)
{
    if (func_0209f150(&data_021dc7a8, 12)) {
        p[52] = 0x46;
    } else {
        p[52] = 0x45;
    }
}
