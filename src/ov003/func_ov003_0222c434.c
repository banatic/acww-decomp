/* func_ov003_0222c434 @ 0x0222c434, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223c0d4;
void func_02056578(void *self);
void func_020edb3c(void *self);

void *func_ov003_0222c434(void *self)
{
    *(int *) self = (int) &data_ov003_0223c0d4;
    func_02056578(self);
    func_020edb3c(self);
    return self;
}
