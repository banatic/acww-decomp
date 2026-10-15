/* func_ov003_0221d980 @ 0x0221d980, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020565b0(void *);
extern void *func_020551e0(void *);
extern void *func_ov009_0226539c(void *);

extern unsigned char data_ov003_02238f28[];
extern unsigned char data_ov003_02238fec[];

void *func_ov003_0221d980(void *self)
{
    *(int *) self = (unsigned int) data_ov003_02238f28;
    *(int *) ((char *) self + 0xec) = (unsigned int) data_ov003_02238fec;
    func_020565b0((char *) self + 0x36c);
    func_020551e0((char *) self + 0x2b4);
    func_ov009_0226539c(self);
    return self;
}
