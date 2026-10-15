/* func_ov003_0221cfc0 @ 0x0221cfc0, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov009_0226552c(void *);
extern void func_020565c8(void *);

extern unsigned char data_ov003_02238c54[];
extern unsigned char data_ov003_02238d18[];

void *func_ov003_0221cfc0(void *this)
{
    func_ov009_0226552c(this);
    *(unsigned int *) this = (unsigned int) data_ov003_02238c54;
    *(unsigned int *) ((char *) this + 0xec) = (unsigned int) data_ov003_02238d18;
    func_020565c8((char *) this + 0x2b4);
    *((signed char *) ((char *) this + 0x2d4)) = -1;
    return this;
}
