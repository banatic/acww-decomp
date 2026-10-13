/* func_ov090_02299608 @ 0x02299608, 0x80 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern int data_ov090_02299964;
extern void func_ov090_02299058(class UnkStruct_02299608 *self);
}

class UnkStruct_02299608 {
  public:
    void f();
};

typedef void (UnkStruct_02299608::*pmf_t)();

extern "C" {
extern pmf_t data_ov090_0229996c[];
extern const pmf_t data_ov090_022997e8;
extern const pmf_t data_ov090_02299810;
extern const pmf_t data_ov090_02299808;
}

extern "C" int func_ov090_02299608(UnkStruct_02299608 *self)
{
    int flag = data_ov090_02299964;
    if (!(flag & 1)) {
        data_ov090_0229996c[0] = data_ov090_022997e8;
        data_ov090_0229996c[1] = data_ov090_02299810;
        data_ov090_0229996c[2] = data_ov090_02299808;
        data_ov090_02299964 |= 1;
    }
    func_ov090_02299058(self);
    unsigned char idx = *((unsigned char *) self + 0x8c);
    (self->*data_ov090_0229996c[idx])();
    return 1;
}
