/* func_02003b24 @ 0x02003b24, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020039e4(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *);

extern unsigned char data_020d72cc[];

void *func_02003b24(void *this)
{
    *(unsigned int *) this = (unsigned int) data_020d72cc;
    func_020039e4(this);
    func_0208a1f4((char *) this + 0xc);
    func_0208af00(this);
    func_020edb3c(this);
    return this;
}
