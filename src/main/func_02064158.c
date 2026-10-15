/* func_02064158 @ 0x02064158, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020de67c;
extern void *func_020a887c(void *);

void *func_02064158(void *arg)
{
    *(void **) arg = (void *) &data_020de67c;
    func_020a887c(arg);
    return arg;
}
