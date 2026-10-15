/* func_ov072_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov072_02279b08;
extern void *func_ov072_02278d98(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);

void *func_ov072_02278a28(void *this)
{
    *(void **) this = (void *) &data_ov072_02279b08;
    func_ov072_02278d98((char *) this + 0x658);
    func_0202ee5c(this);
    func_020edf54(this);
    return this;
}
