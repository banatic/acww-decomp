/* actor_entries: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082c00 @ 0x02082c00, 0xc bytes, Thumb
 * func_02082bfc @ 0x02082bfc, 0x2 bytes, Thumb
 * func_02082bf0 @ 0x02082bf0, 0xc bytes, Thumb
 * func_02082bec @ 0x02082bec, 0x2 bytes, Thumb
 * func_02082bc0 @ 0x02082bc0, 0x2c bytes, Thumb
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

void func_02082c00(unsigned short *r0)
{
    r0[2] = 0x0000fff1;
}

void func_02082bfc(void *object) {}

void func_02082bf0(unsigned short *r0)
{
    *((unsigned short *) ((char *) r0 + 4)) = 0x0000fff1;
}

void func_02082bec(void *object) {}

void *func_02082bc0(void *arg)
{
    __cxa_vec_cleanup((void *) ((char *) arg + 0x40), 4, 8, (void (*)(void *)) func_02082bec);
    __cxa_vec_cleanup((void *) (arg), 8, 8, (void (*)(void *)) func_02082bfc);
    return arg;
}
