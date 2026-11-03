/* house_record_3: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02061504 @ 0x02061504, 0x2c bytes, Thumb
 * func_020614e4 @ 0x020614e4, 0x20 bytes, Thumb
 * func_020614c8 @ 0x020614c8, 0x1c bytes, Thumb
 * func_020614c4 @ 0x020614c4, 0x2 bytes, Thumb
 * func_02061470 @ 0x02061470, 0x54 bytes, Thumb
 * func_02061444 @ 0x02061444, 0x2c bytes, Thumb
 */

extern void func_020051b0(void *);
extern void func_02034ce0(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern char *func_020530d4(void *p);
extern void *func_020530b0(void *);

int func_02061504(int arg)
{
    __cxa_vec_ctor((void *) (arg), 0x100, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);
    return arg;
}

void *func_020614e4(void *arg1)
{
    __cxa_vec_cleanup((void *) (arg1), 0x100, 2, (void (*)(void *)) func_020051b0);
    return arg1;
}

void func_020614c8(unsigned short *ptr)
{
    int i = 0;
    do {
        *ptr++ = 0xfff1;
        i++;
    } while (i < 256);
}

void *func_020614c4(void *buffer)
{
    return buffer;
}

void *func_02061470(void *ptr)
{
    __cxa_vec_ctor((void *) (ptr), 2, 0x200, (((void (*)(void *)) (int (*)(void *)) func_02061504)), (((void (*)(void *)) func_020614e4)));
    func_020530d4((char *) ptr + 0x400);
    *(unsigned short *) ((char *) ptr + 0x448) = 0xfff1;
    *(unsigned short *) ((char *) ptr + 0x44a) = 0xfff1;
    *(unsigned short *) ((char *) ptr + 0x44c) = 0xfff1;
    return ptr;
}

void *func_02061444(void *param)
{
    func_020530b0((char *) param + 0x400);
    __cxa_vec_cleanup((void *) (param), 2, 0x200, (((void (*)(void *)) func_020614e4)));
    return param;
}
