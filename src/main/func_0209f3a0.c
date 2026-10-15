/* func_0209f3a0 @ 0x0209f3a0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209f520(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);

struct Class {
    void *vtbl;
    unsigned char pad_04[0x50];
    unsigned char sub[1];
};

extern unsigned char data_020da13c[];
extern unsigned char data_020e3708[];

struct Class *func_0209f3a0(struct Class *this)
{
    this->vtbl = (void *) data_020e3708;
    func_0209f520(this->sub);
    this->vtbl = (void *) data_020da13c;
    func_020ee62c(this);
    func_020edf54(this);
    return this;
}
