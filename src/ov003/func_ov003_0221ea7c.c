/* func_ov003_0221ea7c @ 0x0221ea7c, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov003_022395e8[];
extern unsigned char data_ov003_022396ac[];
extern void func_ov009_0226539c(void *);
extern void func_020edf54(void *);

void *func_ov003_0221ea7c(void *arg)
{
    *(void **) arg = data_ov003_022395e8;
    *((void **) ((char *) arg + 0xec)) = data_ov003_022396ac;
    func_ov009_0226539c(arg);
    func_020edf54(arg);
    return arg;
}
