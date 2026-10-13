/* func_02057b60 @ 0x02057b60, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f5948(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020dd33c[];

void *func_02057b60(void *this)
{
    *(void **) this = (void *) data_020dd33c;
    func_020f5948((char *) this + 0xDC);
    *(void **) this = (void *) data_020da13c;
    func_020ee62c(this);
    func_020edf54(this);
    return this;
}
