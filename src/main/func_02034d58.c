/* func_02034d58 @ 0x02034d58, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02035494(void *);
extern void func_020ee62c(void *);
extern int data_020da334;
extern int data_020da13c;

void *func_02034d58(void *this)
{
    *(int **) this = &data_020da334;
    func_02035494((char *) this + 0x50);
    *(int **) this = &data_020da13c;
    func_020ee62c(this);
    return this;
}
