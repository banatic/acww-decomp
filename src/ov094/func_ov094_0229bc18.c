/* func_ov094_0229bc18 @ 0x0229bc18, 0x18 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *);
extern char data_ov094_0229c114;

void *func_ov094_0229bc18(void *self)
{
    *(void **) self = (void *) &data_ov094_0229c114;
    func_020edb3c(self);
    return self;
}
