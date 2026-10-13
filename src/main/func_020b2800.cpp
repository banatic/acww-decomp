/* func_020b2800 @ 0x020b2800, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020b2800 {
  public:
    virtual void v00() = 0;
    virtual void v01() = 0;
    virtual void v02() = 0;
    virtual void v03() = 0;
    virtual void v04() = 0;
    virtual void v05() = 0;
    virtual void v06() = 0;
    virtual void v07() = 0;
    virtual void v08() = 0;
    virtual void v09() = 0;
    virtual void v10() = 0;
    virtual void v11() = 0;
    virtual void v12() = 0;
    virtual void v13() = 0;
    virtual void v14() = 0;
    virtual void v15() = 0;
    virtual void v16() = 0;
    virtual void v17() = 0;
    virtual void v18() = 0;
    virtual void v19() = 0;
    virtual void v20() = 0;
    virtual void v21() = 0;
    virtual void v22() = 0;
    virtual void v23() = 0;
    virtual void v24() = 0;
    virtual void v25() = 0;
    virtual void v26() = 0;
    virtual int check(unsigned int) = 0;
};

extern "C" {
typedef struct GObj GObj;
extern unsigned char data_020e54a8;
extern GObj *data_020ccf94;
extern int func_02073d90(GObj *);
extern void func_02073820(GObj *);
extern void func_020737f0(GObj *, void *, int);
extern void func_02073770(GObj *, int, int);
extern unsigned short *func_ov009_02262fcc(UnkStruct_020b2800 *self);

int func_020b2800(UnkStruct_020b2800 *self, unsigned int param)
{
    unsigned int ok = (data_020e54a8 == 0) ? 1 : 0;
    if (ok > 0 && self->check(param) != 0) {
        if (func_02073d90(data_020ccf94) != 0) {
            unsigned short *p = func_ov009_02262fcc(self);
            unsigned short temp;
            temp = (unsigned short) ((temp & ~0x3f) | (*p & 0x3f));
            temp = (unsigned short) ((temp & ~0xfc0) | ((param & 0x3f) << 6));
            temp = (unsigned short) (temp & 0xffff0fff);
            GObj *obj = data_020ccf94;
            func_02073820(obj);
            func_020737f0(obj, &temp, 2);
            func_02073770(obj, 0x22, 4);
        }
        return 1;
    }
    return 0;
}
}
