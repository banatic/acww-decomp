/* func_ov003_0221eec4 @ 0x0221eec4, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_0226552c(void *);

extern unsigned char data_ov003_022398e8[];
extern unsigned char data_ov003_022399ac[];

void *func_ov003_0221eec4(void *this)
{
    void *p;
    func_ov009_0226552c(this);
    *(void **) this = (void *) data_ov003_022398e8;
    p = (char *) this + 0xec;
    *(void **) p = (void *) data_ov003_022399ac;
    return this;
}
