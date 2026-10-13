/* func_02082e78 @ 0x02082e78, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083100(void *arg);
extern char data_020e1a7c;

void *func_02082e78(void *this)
{
    func_02083100(this);
    *(void **) this = (void *) &data_020e1a7c;
    return this;
}
