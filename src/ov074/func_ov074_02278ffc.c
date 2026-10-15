/* func_ov074_02278ffc @ 0x02278ffc, 0x18 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb70(void *);
extern int data_ov074_02279bd8;

void *func_ov074_02278ffc(void *self)
{
    func_0202eb70(self);
    *(void **) self = (void *) &data_ov074_02279bd8;
    return self;
}
