/* func_0206dae0 @ 0x0206dae0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *this);

extern unsigned char data_020df240[];

void *func_0206dae0(void *this)
{
    *(void **) this = (void *) data_020df240;
    func_020a8c38(this);
    return this;
}
