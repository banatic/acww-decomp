/* func_ov004_02233f9c @ 0x02233f9c, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055444(void *argument0);
extern void *func_020edf70(int argument0);
extern void *func_020ee660(void *argument0);
extern void *data_020da13c;
extern void *data_ov004_02255bd4;

void *func_ov004_02233f9c(void)
{
    // DECLS
    char *self;
    // ENDDECLS
    self = (char *) func_020edf70(0x184);
    if (self != 0) {
        func_020ee660(self);
        *(void **) (self) = &data_020da13c;
        *(void **) (self) = &data_ov004_02255bd4;
        func_02055444(self + 0x174);
    }
    return self;
}
