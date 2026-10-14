/* func_02061470 @ 0x02061470, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020530d4(void *p);
extern void func_020614e4(void);
extern void func_02061504(void);
extern void __cxa_vec_ctor(void *ptr, int a, int b, void (*cb)(void), void (*cb2)(void));

void *func_02061470(void *ptr)
{
    __cxa_vec_ctor(ptr, 2, 0x200, func_02061504, func_020614e4);
    func_020530d4((char *) ptr + 0x400);
    *(unsigned short *) ((char *) ptr + 0x448) = 0xfff1;
    *(unsigned short *) ((char *) ptr + 0x44a) = 0xfff1;
    *(unsigned short *) ((char *) ptr + 0x44c) = 0xfff1;
    return ptr;
}
