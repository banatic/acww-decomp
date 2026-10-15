/* func_02041a00 @ 0x02041a00, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020db71c[];
extern char data_020da13c[];
extern void *func_020669e0(void *ptr);
extern void func_020ee62c(void *ptr);
extern void func_020edf54(void *ptr);

void *func_02041a00(void *arg)
{
    char *this = arg;

    *(void **) this = data_020db71c;
    func_020669e0(this + 0x54);
    *(void **) this = data_020da13c;
    func_020ee62c(this);
    func_020edf54(this);

    return this;
}
