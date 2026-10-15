/* func_ov083_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov083_0227928c;
extern void *func_ov083_02278d64(void *ptr);
extern void *func_0202ee5c(void *ptr);

void *func_ov083_02278a00(void *target)
{
    *(int **) target = &data_ov083_0227928c;
    func_ov083_02278d64((char *) target + 0x65c);
    func_0202ee5c(target);
    return target;
}
