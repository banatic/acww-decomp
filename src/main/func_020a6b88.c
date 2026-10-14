/* func_020a6b88 @ 0x020a6b88, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *dst, int a, int b, void (*c)(void), void (*d)(void));
extern void func_020a6998(void *obj);
extern void func_020a7754(void);
extern void func_020a7758(void);
extern void func_020a7718(void);
extern void func_020a771c(void);
extern void func_020a76e4(void);
extern void func_020a76e8(void);
extern void func_020a77c8(void);
extern void func_020a77cc(void);

void *func_020a6b88(void *obj)
{
    __cxa_vec_ctor(obj, 4, 3, func_020a7758, func_020a7754);
    __cxa_vec_ctor((char *) obj + 0xc, 4, 8, func_020a771c, func_020a7718);
    __cxa_vec_ctor((char *) obj + 0x2c, 4, 4, func_020a76e8, func_020a76e4);
    __cxa_vec_ctor((char *) obj + 0x3c, 4, 8, func_020a77cc, func_020a77c8);
    func_020a6998(obj);
    return obj;
}
