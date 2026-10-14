/* func_ov003_022275bc @ 0x022275bc, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

void __cxa_vec_cleanup(void *p, int n, int sz, void (*dtor)(void *));
void func_ov003_022275d8(void *p);
void *func_ov003_022275bc(void *self)
{
    __cxa_vec_cleanup(self, 0x14, 0xa4, func_ov003_022275d8);
    return self;
}
