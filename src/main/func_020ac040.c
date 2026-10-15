/* func_020ac040 @ 0x020ac040, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3fe4;
extern void *func_020acb70(void *);
extern void *func_0208f4e0(void *);
extern void *func_020ac9ec(void *);
extern void *func_020ac954(void *);
extern void func_020edb3c(void *);

void *func_020ac040(void *param)
{
    *(void **) param = &data_020e3fe4;
    func_020acb70((void *) ((unsigned int) param + 0xe4));
    func_0208f4e0((void *) ((unsigned int) param + 0x6c));
    func_020ac9ec((void *) ((unsigned int) param + 0x20));
    func_020ac954(param);
    func_020edb3c(param);
    return param;
}
