/* func_ov070_02279538 @ 0x02279538, 0x18 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099670(int);
extern void func_02088b50(unsigned char *object, unsigned char value);

void func_ov070_02279538(void *self, unsigned char value)
{
    unsigned char *object = (unsigned char *) func_02099670(func_020984e8());
    func_02088b50(object, value);
}
