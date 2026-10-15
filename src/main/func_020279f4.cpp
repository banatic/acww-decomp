/* func_020279f4 @ 0x020279f4, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
struct D_020d94d8_t {
    int a;
    int b;
};
extern D_020d94d8_t data_020d94d8;
extern unsigned char data_021c2b84[];
extern unsigned char data_021c2b6c[];
extern unsigned char data_021e5a2c[];

extern int func_0202d9c4(void *);
extern int func_0209bc40(int);
extern int func_02014e2c(void *);
extern void func_0202dbf0(void *, D_020d94d8_t);
extern int func_020984e8(void);
extern int func_02099734(int);
extern void *func_0202d754(int);
extern int func_02065ec0(void *);
extern void func_02066650(void *);
extern void func_0202da88(void *, void *);
extern int func_02068484(void *, void *, int);
extern int func_0209b4cc(void *, int);
extern int func_0208150c(void *);
extern void func_0207bae8(void *, int, int, int);
}

class UnkStruct_020279f4 {
  public:
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb0 - 0x44];
    void (UnkStruct_020279f4::*pmf)(void *);
    char pad_B8[0x100 - 0xb8];
    void *unk_100;
    char pad_104[0x160 - 0x104];
    void *unk_160;
    void Method(void *);
};

extern "C" void func_020279f4(UnkStruct_020279f4 *self)
{
    unsigned char buf[12];
    int v = func_0209bc40(func_0202d9c4(self));
    switch (v) {
        case 10:
            func_02014e2c(self);
            func_0202dbf0(self, data_020d94d8);
            break;
        case 19: {
            void *x = func_0202d754(func_02099734(func_020984e8()));
            if (x != 0) {
                if (func_02065ec0(x) == 7) {
                    func_0202da88(self, data_021c2b84);
                } else {
                    func_02066650(x);
                    func_0202da88(self, data_021c2b6c);
                }
                if (self->pmf) {
                    (self->*self->pmf)((void *) &buf[4]);
                }
                buf[0] = buf[8];
                func_02068484(self->unk_40, buf, *(int *) &buf[4]);
            }
            break;
        }
        default:
            break;
    }
    int w = func_0209b4cc(self->unk_160, 0);
    int z = func_0208150c(*(void **) ((char *) self->unk_100 + 0x830));
    func_0207bae8(data_021e5a2c, w, z, 10);
}
