/* field_actor_15: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02210140 @ 0x02210140, 0x14 bytes, Thumb
 * func_ov003_0221013c @ 0x0221013c, 0x2 bytes, Thumb
 * func_ov003_02210120 @ 0x02210120, 0x1a bytes, Thumb
 * func_ov003_02210114 @ 0x02210114, 0xc bytes, Thumb
 */

extern void func_020109fc(int, int, int, int);
extern void func_02010f5c(void *);
extern void func_02010d64(void *);
extern void *func_02010ca4(void *);

void func_ov003_02210140(int x, void *message, int previous)
{
    func_020109fc(x, 0, 3, 0);
}

void func_ov003_0221013c(void *receiver, int event) {}

void func_ov003_02210120(void *x)
{
    func_02010f5c(x);
    func_02010d64(x);
    func_02010ca4(x);
}

void func_ov003_02210114(void *r0, void *r1, unsigned char r2)
{
    unsigned char *dst = (unsigned char *) r0;
    unsigned int *src = (unsigned int *) r1;
    dst[0] = (unsigned char) src[0];
    dst[1] = (unsigned char) src[1];
    dst[2] = r2;
}
