/* func_ov004_022454dc @ 0x022454dc, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee660(void *);
extern int data_020da13c;
extern int data_ov004_0225672c;

void *func_ov004_022454dc(void *self)
{
    func_020ee660(self);
    *(void **) self = (void *) &data_020da13c;
    *(void **) self = (void *) &data_ov004_0225672c;
    return self;
}
