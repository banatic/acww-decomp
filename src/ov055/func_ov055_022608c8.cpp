/* func_ov055_022608c8 @ 0x022608c8, 0x44 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

struct ClassA;
typedef void (ClassA::*Handler)();

struct PMFData {
    Handler handler;
    int adj;
    int pad_0C;
};

extern unsigned char data_ov055_02260f14[];
extern PMFData data_ov055_02260f0c[];

extern "C" void func_ov055_022608c8(ClassA *self)
{
    char *p = (char *) self;
    p += 0xb4;
    int idx = *(int *) p;
    int offset = idx * 12;
    if (data_ov055_02260f14[offset] == 0) {
        return;
    }
    PMFData *e = (PMFData *) ((char *) data_ov055_02260f0c + offset);
    if (e->handler == 0) {
        return;
    }
    (self->*e->handler)();
}
