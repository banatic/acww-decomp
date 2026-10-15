/* func_ov073_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov073_02278e9c(void *);
extern void *func_0202ee5c(void *);

extern unsigned char data_ov073_02279b00[];

void *func_ov073_02278a00(void *this)
{
    *(void **) this = (void *) data_ov073_02279b00;
    func_ov073_02278e9c((char *) this + 0x658);
    func_0202ee5c(this);
    return this;
}
