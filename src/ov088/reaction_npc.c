/* reaction_npc: 4 functions, module ov088
 * mwccarm 1.2/base -O4,s
 * func_ov088_02278a6c @ 0x02278a6c, 0x20 bytes, Thumb
 * func_ov088_02278a54 @ 0x02278a54, 0x18 bytes, Thumb
 * func_ov088_02278a28 @ 0x02278a28, 0x2c bytes, Thumb
 * func_ov088_02278a00 @ 0x02278a00, 0x28 bytes, Thumb
 */

struct Main {
    void *vtbl;
    char pad_04[0x654];
    char sub[1];
};

extern int func_02013a14(void *p);
extern void func_0203fa2c(int, int);
extern void func_0204093c(int);
extern unsigned char data_ov088_02279cec;
extern void *func_ov088_02278cf8(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);

int func_ov088_02278a6c(void *arg)
{
    int flag = ((unsigned char *) arg)[0x739];
    if (flag) {
        return func_02013a14(arg);
    } else {
        return -1;
    }
}

void func_ov088_02278a54(int a1, int a2, int a3)
{
    func_0203fa2c(a2, a3);
    func_0204093c(0x43);
}

struct Main *func_ov088_02278a28(struct Main *this)
{
    this->vtbl = &data_ov088_02279cec;
    func_ov088_02278cf8(this->sub);
    func_0202ee5c(this);
    func_020edf54(this);
    return this;
}

void *func_ov088_02278a00(void *this)
{
    *(void **) this = &data_ov088_02279cec;
    func_ov088_02278cf8((char *) this + 0x658);
    func_0202ee5c(this);
    return this;
}
