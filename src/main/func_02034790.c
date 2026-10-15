/* func_02034790 @ 0x02034790, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02031608(void *);
extern void *func_02034804(void *);
extern void func_020326bc(void *);
extern void func_02032438(void *);
extern void *func_02032f78(void *);
extern int func_02033c2c(void *);
extern void *func_02033878(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

void *func_02034790(void *arg)
{
    __cxa_vec_cleanup((void *) ((char *) arg + 0x1a94), 0x31, 0x18, (void (*)(void *)) func_02031608);
    func_020326bc((char *) arg + 0x1a91);
    func_02032438((char *) arg + 0x1a90);
    func_02032f78((char *) arg + 0x184c);
    func_02033c2c((char *) arg + 0xe48);
    func_02033878((char *) arg + 0x9c4);
    __cxa_vec_cleanup((void *) ((char *) arg + 4), 8, 0x138, (((void (*)(void *)) func_02034804)));
    return arg;
}
