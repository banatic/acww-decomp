/* func_0209020c @ 0x0209020c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020ee62c(void *obj);

extern unsigned char data_020da13c[];
extern unsigned char data_020e2724[];
extern void *func_0209028c(void *);

void *func_0209020c(void *obj)
{
    *(void **) obj = (void *) data_020e2724;
    __cxa_vec_cleanup((void *) ((void *) ((char *) obj + 0x35c)), 4, 0x530, (((void (*)(void *)) func_0209028c)));
    *(void **) obj = (void *) data_020da13c;
    func_020ee62c(obj);
    return obj;
}
