/* func_ov004_0221d590 @ 0x0221d590, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202de4c(void *argument0);
extern void *func_0202e5e0(void *argument0);
extern void func_020edf54(unsigned int argument0);
extern void *data_ov004_022537d8;
extern void *data_ov004_02253868;

void *func_ov004_0221d590(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02253868;
    *(void **) (self + 0x89c) = &data_ov004_022537d8;
    func_0202de4c(self + 0x89c);
    func_0202e5e0(self);
    func_020edf54((unsigned int) (self));
    return self;
}
