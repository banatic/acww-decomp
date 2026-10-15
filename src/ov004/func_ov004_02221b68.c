/* func_ov004_02221b68 @ 0x02221b68, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202e8e4(void *argument0);
extern void *func_020edf70(int argument0);
extern void *func_ov004_022219ac(void *argument0);
extern void *data_ov004_02253fd4;

void *func_ov004_02221b68(void)
{
    // DECLS
    char *self;
    // ENDDECLS
    self = (char *) func_020edf70(0xa44);
    if (self != 0) {
        func_0202e8e4(self);
        *(void **) (self) = &data_ov004_02253fd4;
        func_ov004_022219ac(self + 0x89c);
    }
    return self;
}
