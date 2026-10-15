/* func_020838c4 @ 0x020838c4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083ca8(void *, int);
extern void *func_02083910(void *);
extern void *func_02083928(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

extern unsigned char data_020e1b1c[];

void *func_020838c4(void *param)
{
    func_02083ca8(param, 4);
    *(void **) param = (void *) data_020e1b1c;
    __cxa_vec_ctor((void *) ((void *) ((char *) param + 8)), 4, 8, (((void (*)(void *)) func_02083928)),
                   (((void (*)(void *)) func_02083910)));
    return param;
}
