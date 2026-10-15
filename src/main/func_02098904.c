/* func_02098904 @ 0x02098904, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02099ad0(void *);
extern void *func_02099bc8(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

void *func_02098904(void *ptr)
{
    __cxa_vec_ctor((void *) (ptr), 4, 0x249c, (((void (*)(void *)) func_02099bc8)), (((void (*)(void *)) func_02099ad0)));
    return ptr;
}
