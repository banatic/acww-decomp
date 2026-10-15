/* func_020ab6c8 @ 0x020ab6c8, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_020ab804(void *);
extern void *func_020ab7e8(void *);
extern void *func_020ab8dc(void *);
extern int func_020a82e8(void *);
extern void func_020ab5e4(void *);

extern unsigned char data_021f43ec;

void *func_020ab6c8(void *obj)
{
    __cxa_vec_ctor((void *) (obj), 5, 0x90, (((void (*)(void *)) func_020ab804)), (((void (*)(void *)) func_020ab7e8)));
    ((unsigned char *) obj)[0x2dc] = data_021f43ec;
    func_020ab8dc((char *) obj + 0x2f8);
    func_020a82e8((char *) obj + 0x354);
    func_020ab5e4(obj);
    return obj;
}
