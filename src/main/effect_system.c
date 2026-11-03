/* effect_system: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02090248 @ 0x02090248, 0x44 bytes, Thumb
 * func_0209020c @ 0x0209020c, 0x3c bytes, Thumb
 */

extern void *func_0209028c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020ee62c(void *ptr);
extern void func_020edf54(void *ptr);
extern unsigned char data_020da13c[];
extern unsigned char data_020e2724[];

void *func_02090248(void *p)
{
    *((int *) p) = (int) ((int *) data_020e2724);
    __cxa_vec_cleanup((void *) ((char *) p + 0x35c), 4, 0x530, (((void (*)(void *)) func_0209028c)));
    *((int *) p) = (int) ((int *) data_020da13c);
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}

void *func_0209020c(void *obj)
{
    *(void **) obj = (void *) data_020e2724;
    __cxa_vec_cleanup((void *) ((void *) ((char *) obj + 0x35c)), 4, 0x530, (((void (*)(void *)) func_0209028c)));
    *(void **) obj = (void *) data_020da13c;
    func_020ee62c(obj);
    return obj;
}
