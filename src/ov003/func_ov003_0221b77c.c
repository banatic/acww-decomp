/* func_ov003_0221b77c @ 0x0221b77c, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02089ca4(void *self);
extern char data_ov003_02238280;

void *func_ov003_0221b77c(void *this)
{
    func_02089ca4(this);
    *(void **) this = &data_ov003_02238280;
    ((unsigned char *) this)[0x44] = 0;
    return this;
}
