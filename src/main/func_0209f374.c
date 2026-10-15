/* func_0209f374 @ 0x0209f374, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e3708;
extern int data_020da13c;
extern void *func_0209f520(void *);
extern void func_020ee62c(void *) __attribute__((arm));

void *func_0209f374(void *this)
{
    *(int **) this = &data_020e3708;
    func_0209f520((void *) ((unsigned int) this + 0x54));
    *(int **) this = &data_020da13c;
    func_020ee62c(this);
    return this;
}
