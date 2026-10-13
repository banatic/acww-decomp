/* func_ov003_0221c3b8 @ 0x0221c3b8, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_0226552c(void *ptr);
extern char data_ov003_022387a8[];
extern char data_ov003_0223886c[];

void *func_ov003_0221c3b8(void *self)
{
    func_ov009_0226552c(self);
    *(void **) self = data_ov003_022387a8;
    *(void **) ((char *) self + 0xec) = data_ov003_0223886c;
    return self;
}
