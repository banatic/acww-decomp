/* func_ov053_02260448 @ 0x02260448, 0x2c bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov053_02260bfc(void *);
extern void func_0202ee5c(void *);
extern void func_020edf54(void *);

extern unsigned char data_ov053_02261b98[];

void *func_ov053_02260448(void *this)
{
    *(unsigned int *) this = (unsigned int) data_ov053_02261b98;
    func_ov053_02260bfc((char *) this + 0x658);
    func_0202ee5c(this);
    func_020edf54(this);
    return this;
}
