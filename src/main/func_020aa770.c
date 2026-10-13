/* func_020aa770 @ 0x020aa770, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ab36c(void *);
extern void func_020ac2c8(void *);
extern void func_020aa7fc(void *);
extern int data_020e406c;

void *func_020aa770(void *this)
{
    *((int **) this) = &data_020e406c;
    func_020ab36c((char *) this + 0x84);
    func_020ac2c8((char *) this + 0xc);
    func_020aa7fc(this);
    return this;
}
