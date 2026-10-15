/* func_020c1574 @ 0x020c1574, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020012dc(void *);
extern void func_020be550(void *);
extern void *func_020be554(void *);

void *func_020c1574(void *obj)
{
    __cxa_vec_cleanup((void *) ((void *) ((char *) obj + 0x302c)), 8, 0xc, (void (*)(void *)) func_020012dc);
    __cxa_vec_cleanup((void *) ((void *) ((char *) obj + 0x2f58)), 4, 0x14, (void (*)(void *)) func_020be550);
    __cxa_vec_cleanup((void *) (obj), 0x3c, 0x74, (((void (*)(void *)) func_020be554)));
    return obj;
}
