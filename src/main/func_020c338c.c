/* func_020c338c @ 0x020c338c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e7e14;
extern void *func_0202eb20(void *);

void *func_020c338c(void *this)
{
    *(void **) this = &data_020e7e14;
    func_0202eb20(this);
    return this;
}
