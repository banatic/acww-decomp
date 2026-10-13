/* func_ov111_0229fcb0 @ 0x0229fcb0, 0x58 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    unsigned int unk_64;
} GStruct;

extern GStruct *data_020ccf94;

extern unsigned int func_020984e8(unsigned char *self);
extern void func_02094fd4(unsigned char *buf);
extern unsigned int func_02099870(unsigned int v);
extern void func_02095074(unsigned int a, unsigned char *buf);
extern void func_020b4424(unsigned char *p);
extern void func_020398e8(unsigned int a, unsigned char *b, unsigned char *c);
extern void func_ov111_0229f994(unsigned char *self);
extern void func_ov111_0229fd08(unsigned char *self);
extern void func_02094fbc(unsigned char *buf);

void func_ov111_0229fcb0(unsigned char *self)
{
    unsigned char buf[0x24];
    unsigned int v = func_020984e8(self);

    func_02094fd4(buf);
    func_02095074(func_02099870(v), buf);
    func_020b4424(self + 0x3cd4);
    func_020398e8(data_020ccf94->unk_64, buf, self + 0x3cd4);
    func_ov111_0229f994(self);
    func_ov111_0229fd08(self);
    func_02094fbc(buf);
}
