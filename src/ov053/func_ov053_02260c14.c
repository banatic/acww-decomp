/* func_ov053_02260c14 @ 0x02260c14, 0x18 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *);
extern unsigned char data_ov053_02261b08;

void *func_ov053_02260c14(void *this)
{
    func_0202eb70(this);
    *(unsigned int *) this = (unsigned int) &data_ov053_02261b08;
    return this;
}
