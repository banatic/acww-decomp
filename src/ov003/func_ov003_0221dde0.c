/* func_ov003_0221dde0 @ 0x0221dde0, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov009_0226552c(void *this);
extern int data_ov003_02239254;
extern int data_ov003_02239318;

void *func_ov003_0221dde0(void *this)
{
    func_ov009_0226552c(this);
    *(void **) this = (void *) &data_ov003_02239254;
    *(void **) ((char *) this + 0xec) = (void *) &data_ov003_02239318;
    return this;
}
