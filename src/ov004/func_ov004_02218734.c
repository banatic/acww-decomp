/* func_ov004_02218734 @ 0x02218734, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(int);
extern int func_ov004_0221876c(void *);
extern void *data_020ccf94;

int func_ov004_02218734(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_02073d90(*(int *) ((char *) &data_020ccf94)) == 0x0 && func_ov004_0221876c(self) != 0x0 &&
        *(int *) (self + 0x858) != 0x0) {
        return 0x1;
    } else {
        return 0x0;
    }
}
