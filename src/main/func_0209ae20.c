/* func_0209ae20 @ 0x0209ae20, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209b594(void);
extern void func_0209b5b8(void);
extern void func_02003780(void);
extern void func_02003750(void);
extern void func_0209bd80(void *);
extern void func_0209af44(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void), void (*)(void));

void *func_0209ae20(void *obj)
{
    __cxa_vec_ctor(obj, 2, 0x30, func_0209b5b8, func_0209b594);
    __cxa_vec_ctor((char *) obj + 0x60, 3, 0x10, func_02003780, func_02003750);
    func_0209bd80((char *) obj + 0x94);
    func_0209af44((char *) obj + 0xa4);
    return obj;
}
