/* func_ov003_0221b75c @ 0x0221b75c, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtbl;
    char pad_04[0x40];
    unsigned char flag;
} Object;

extern char data_ov003_02238280;
extern void func_02089c58(Object *this);

Object *func_ov003_0221b75c(Object *this)
{
    this->vtbl = &data_ov003_02238280;
    this->flag = 0;
    func_02089c58(this);
    return this;
}
