/* func_0208b56c @ 0x0208b56c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208bb8c(void *p);
extern void *func_0208c1ac(void *p);
extern void *func_0208d2e8(void *p);
extern void *func_0208def4(void *p);
extern void func_020edb3c(void *p);

extern unsigned char data_020e21d4[];

void *func_0208b56c(void *obj)
{
    *(void **) obj = (void *) data_020e21d4;
    func_0208bb8c((char *) obj + 0x2c4);
    func_0208c1ac((char *) obj + 0x1c4);
    func_0208d2e8((char *) obj + 0xe0);
    func_0208def4((char *) obj + 0x8);
    func_020edb3c(obj);
    return obj;
}
