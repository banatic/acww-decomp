/* func_ov094_0229aba4 @ 0x0229aba4, 0x14 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov094_0229a524(int parameter0, int parameter1);
extern int func_02088d9c(unsigned int *);

int func_ov094_0229aba4(int arg0, int arg1)
{
    return func_02088d9c((unsigned int *) func_ov094_0229a524(arg0, arg1)) + 0x80;
}
