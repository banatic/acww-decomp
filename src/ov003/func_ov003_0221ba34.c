/* func_ov003_0221ba34 @ 0x0221ba34, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_0226552c(void *);
extern char data_ov003_02238434;
extern char data_ov003_022384f8;

void *func_ov003_0221ba34(void *this)
{
    func_ov009_0226552c(this);
    *(void **) this = &data_ov003_02238434;
    *(void **) ((char *) this + 0xec) = &data_ov003_022384f8;
    return this;
}
