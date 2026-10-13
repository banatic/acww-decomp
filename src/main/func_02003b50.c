/* func_02003b50 @ 0x02003b50, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020039e4(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);

extern unsigned char data_020d72cc[];

void *func_02003b50(void *obj)
{
    *(unsigned int *) obj = (unsigned int) data_020d72cc;
    func_020039e4(obj);
    func_0208a1f4((char *) obj + 12);
    func_0208af00(obj);
    return obj;
}
