/* func_ov003_0221cf54 @ 0x0221cf54, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020565b0(void *p);
extern void *func_ov009_0226539c(void *p);
extern void func_020edf54(void *p);

extern unsigned char data_ov003_02238c54[];
extern unsigned char data_ov003_02238d18[];

void *func_ov003_0221cf54(void *arg)
{
    char *p = (char *) arg;
    *(unsigned int *) p = (unsigned int) (unsigned int) data_ov003_02238c54;
    p += 0xEC;
    *(unsigned int *) p = (unsigned int) (unsigned int) data_ov003_02238d18;
    func_020565b0((char *) arg + 0x2B4);
    func_ov009_0226539c(arg);
    func_020edf54(arg);
    return arg;
}
