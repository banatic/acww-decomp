/* func_ov004_0221ee98 @ 0x0221ee98, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202e8e4(void *argument0);
extern void func_02084f88(void *object);
extern void *func_020edf70(int argument0);
extern void func_ov004_0221ebf8(int *argument0);
extern void *data_ov004_022539cc;

void *func_ov004_0221ee98(void)
{
    // DECLS
    char *self;
    // ENDDECLS
    self = (char *) func_020edf70(0x8dc);
    if (self != 0) {
        func_0202e8e4(self);
        *(void **) (self) = &data_ov004_022539cc;
        func_ov004_0221ebf8((int *) (self + 0x8a0));
        func_02084f88(self + 0x8b4);
    }
    return self;
}
