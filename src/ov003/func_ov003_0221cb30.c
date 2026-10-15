/* func_ov003_0221cb30 @ 0x0221cb30, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov009_0226552c(void *self);
extern void func_020565c8(void *sub);

extern unsigned char data_ov003_02238b10[];
extern unsigned char data_ov003_02238bd4[];

void *func_ov003_0221cb30(void *self)
{
    func_ov009_0226552c(self);
    *(void **) self = (void *) data_ov003_02238b10;
    *(void **) ((char *) self + 0xEC) = (void *) data_ov003_02238bd4;
    func_020565c8((char *) self + 0x2B8);
    return self;
}
