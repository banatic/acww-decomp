/* func_ov003_0221d230 @ 0x0221d230, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov009_0226552c(void *self);
extern char data_ov003_02238dbc;
extern char data_ov003_02238e80;

void *func_ov003_0221d230(void *self)
{
    func_ov009_0226552c(self);
    *(void **) self = &data_ov003_02238dbc;
    *(void **) ((char *) self + 0xec) = &data_ov003_02238e80;
    return self;
}
