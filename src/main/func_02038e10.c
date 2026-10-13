/* func_02038e10 @ 0x02038e10, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02039304(void *);
extern void func_0203977c(void *);
extern void func_0203909c(void *);
extern void __arm func_020ee62c(void *);
extern void __arm func_020edf54(void *);
extern char data_020da674[];
extern char data_020da13c[];

void *func_02038e10(void *this)
{
    *(unsigned int *) this = (unsigned int) data_020da674;
    func_02039304((char *) this + 0x358);
    func_0203977c((char *) this + 0x54);
    func_0203909c((char *) this + 0x50);
    *(unsigned int *) this = (unsigned int) data_020da13c;
    func_020ee62c(this);
    func_020edf54(this);
    return this;
}
