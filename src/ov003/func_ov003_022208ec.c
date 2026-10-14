/* func_ov003_022208ec @ 0x022208ec, 0x128 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02223b34(void *);
extern void func_02055438(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_02055764(void *);
extern void func_020ee62c(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_ov003_0223bc7c[];

void *func_ov003_022208ec(void *ptr)
{
    *(void **) ptr = (void *) data_ov003_0223bc7c;
    func_ov003_02223b34((char *) ptr + 0x4b20);
    func_02055438((char *) ptr + 0x4b10);
    func_02055438((char *) ptr + 0x4b00);
    func_02055438((char *) ptr + 0x4af0);
    func_02055438((char *) ptr + 0x4ae0);
    __cxa_vec_cleanup((char *) ptr + 0x49a8, 2, 0x9c, func_02055764);
    __cxa_vec_cleanup((char *) ptr + 0x4840, 2, 0x9c, func_02055764);
    __cxa_vec_cleanup((char *) ptr + 0x4708, 2, 0x9c, func_02055764);
    __cxa_vec_cleanup((char *) ptr + 0x43e8, 5, 0x9c, func_02055764);
    __cxa_vec_cleanup((char *) ptr + 0x3068, 0x20, 0x9c, func_02055764);
    __cxa_vec_cleanup((char *) ptr + 0x2df0, 4, 0x9c, func_02055764);
    __cxa_vec_cleanup((char *) ptr + 0x1590, 0x28, 0x9c, func_02055764);
    __cxa_vec_cleanup((char *) ptr + 0x11e8, 6, 0x9c, func_02055764);
    __cxa_vec_cleanup((char *) ptr + 0x1014, 3, 0x9c, func_02055764);
    __cxa_vec_cleanup((char *) ptr + 0x0c6c, 6, 0x9c, func_02055764);
    __cxa_vec_cleanup((char *) ptr + 0x0174, 0x12, 0x9c, func_02055764);
    *(void **) ptr = (void *) data_020da13c;
    func_020ee62c(ptr);
    return ptr;
}
