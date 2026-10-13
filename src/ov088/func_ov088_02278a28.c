/* func_ov088_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov088_02279cec;
extern void func_ov088_02278cf8(void *);
extern void func_0202ee5c(void *);
extern void func_020edf54(void *);

struct Main {
    void *vtbl;
    char pad_04[0x654];
    char sub[1];
};

struct Main *func_ov088_02278a28(struct Main *this)
{
    this->vtbl = &data_ov088_02279cec;
    func_ov088_02278cf8(this->sub);
    func_0202ee5c(this);
    func_020edf54(this);
    return this;
}
