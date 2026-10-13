/* func_ov088_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov088_02279cec;
extern void func_ov088_02278cf8(void *ptr);
extern void func_0202ee5c(void *ptr);

void *func_ov088_02278a00(void *this)
{
    *(void **) this = &data_ov088_02279cec;
    func_ov088_02278cf8((char *) this + 0x658);
    func_0202ee5c(this);
    return this;
}
