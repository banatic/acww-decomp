/* func_ov003_02228fd0 @ 0x02228fd0, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223c0d4;
void *func_02056578(void *p);
void *func_ov003_02228fd0(void *self)
{
    *(int *) self = (int) &data_ov003_0223c0d4;
    func_02056578(self);
    return self;
}
