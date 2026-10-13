/* func_0209ff0c @ 0x0209ff0c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f3278;
extern int data_020e3800;
extern int data_020e3bb0;
extern int data_021f40a4;

extern int func_02088208(void *);
extern void func_02073100(void *);
extern int func_020eb188(void *, void *, int, int);

int func_0209ff0c(void)
{
    int val;

    if (func_02088208((void *) &data_021f3278) == 0) {
        val = data_020e3800;
        func_02073100((void *) &data_020e3800);
        if (func_020eb188((void *) &data_020e3bb0, (void *) &data_021f40a4, 0x238, val) == 0) {
            return 0;
        } else {
            return 1;
        }
    }
    return 0;
}
