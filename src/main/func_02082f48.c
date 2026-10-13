/* func_02082f48 @ 0x02082f48, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020830d0(void *obj);
extern void *data_020e19f0;

void *func_02082f48(void *this)
{
    *(void **) this = &data_020e19f0;
    func_020830d0(this);
    return this;
}
