/* func_02062e00 @ 0x02062e00, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020de614;
void func_020a887c(void *arg);

void *func_02062e00(void *arg)
{
    *(void **) arg = (void *) &data_020de614;
    func_020a887c(arg);
    return arg;
}
