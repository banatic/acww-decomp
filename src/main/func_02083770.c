/* func_02083770 @ 0x02083770, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083ca8(void *obj, int param);
extern void func_02138d6c(void *obj, int a, int b, void (*cb1)(void), void (*cb2)(void));
extern void func_020837d0(void);
extern void func_020837e8(void);
extern unsigned char data_020e1ae4;

void *func_02083770(void *obj)
{
    func_02083ca8(obj, 5);
    *(unsigned int *) obj = (unsigned int) &data_020e1ae4;
    func_02138d6c((char *) obj + 8, 5, 2, func_020837e8, func_020837d0);
    return obj;
}
