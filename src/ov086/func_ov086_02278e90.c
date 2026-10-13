/* func_ov086_02278e90 @ 0x02278e90, 0x20 bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *);
extern void func_020edb3c(void *);

extern unsigned char data_ov086_022792fc[];

void *func_ov086_02278e90(void *obj)
{
    *((unsigned int *) obj) = (unsigned int) data_ov086_022792fc;
    func_0202eb20(obj);
    func_020edb3c(obj);
    return obj;
}
