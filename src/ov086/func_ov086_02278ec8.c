/* func_ov086_02278ec8 @ 0x02278ec8, 0x18 bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *p);

extern unsigned char data_ov086_022792fc[];

void *func_ov086_02278ec8(void *p)
{
    func_0202eb70(p);
    *(unsigned int *) p = (unsigned int) data_ov086_022792fc;
    return p;
}
