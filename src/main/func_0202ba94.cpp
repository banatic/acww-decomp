/* func_0202ba94 @ 0x0202ba94, 0x20c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

struct UnkStruct_0202ba94 {
    char pad_00[0x830];
    void *unk_830;
};
struct SS {
    unsigned char a;
    unsigned char unk_01[3];
    int b;
    unsigned char c;
    unsigned char p2[3];
    int x;
    int y;
};

class UnkStruct_0202ba94_2 {
  public:
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb0 - 0x44];
    void (UnkStruct_0202ba94_2::*cb)(int *);
    char pad_B8[0x100 - 0xb8];
    UnkStruct_0202ba94 *unk_100;
    char pad_104[0x160 - 0x104];
    void *unk_160;
};

extern int data_021e5a2c;
extern int data_021c2a64;
extern int data_021c2aac;
extern int data_021c3094;
extern int data_021c1d54;

extern "C" {
void *func_020984e8(void);
void *func_02099640(void *);
unsigned int func_0207b86c(void *, void *, void *);
void func_0209e474(int *);
int func_0209bc94(unsigned int);
void *func_0209bbf8(unsigned int);
void *func_0209ad9c(void *, void *);
void *func_0209b4d4(void *);
int func_0209bba0(void *);
void *func_0209bc20(void *);
int func_0209e3ac(void *, void *, int);
void func_0202da88(UnkStruct_0202ba94_2 *, void *);
void func_0202d9d0(UnkStruct_0202ba94_2 *, void *);
int func_0209bc40(void *);
void *func_02099734(void *);
void *func_0209bb70(void *);
int func_0202d794(void *, void *);
void *func_0202d754(void *);
int func_02065ec0(void *);
void func_02066650(void *);
int func_0209bd44(void *);
void *func_0208150c(void *);
int func_0209aebc(void *, void *);
int func_0202d9c4(UnkStruct_0202ba94_2 *);
void func_02068484(void *, SS *, int);
void func_0202ba94(UnkStruct_0202ba94_2 *self);
}

extern "C" void func_0202ba94(UnkStruct_0202ba94_2 *self)
{
    void *p;
    unsigned int v;
    SS s;
    void *d;
    void *c;
    void *a;
    void *e;

    a = func_020984e8();
    c = self->unk_100->unk_830;
    d = func_02099640(a);
    v = func_0207b86c(&data_021e5a2c, c, a);
    if (v < 0x16) {
        s.x = 0;
        s.y = 0;
        func_0209e474(&s.x);
        switch (func_0209bc94(v)) {
            case 0:
                break;
            case 1:
                self->unk_160 = func_0209ad9c(d, func_0209bbf8(v));
                if (self->unk_160 != 0) {
                    if (func_0209bba0(func_0209b4d4(self->unk_160)) == 0) {
                        if (func_0209e3ac(func_0209bc20(func_0209b4d4(self->unk_160)), &s.x, 0x3f) == -1) {
                            func_0202da88(self, &data_021c2a64);
                            func_0202d9d0(self, func_0209b4d4(self->unk_160));
                        } else {
                            switch (func_0209bc40(func_0209b4d4(self->unk_160))) {
                                case 0xa:
                                    d = func_02099734(a);
                                    if (func_0202d794(d, func_0209bb70(func_0209b4d4(self->unk_160))) == -1) {
                                        func_0202da88(self, &data_021c2aac);
                                        func_0202d9d0(self, func_0209b4d4(self->unk_160));
                                    }
                                    break;
                                case 0x13:
                                    d = func_0202d754(func_02099734(a));
                                    if (d != 0) {
                                        if (func_02065ec0(d) == 8) {
                                            func_02066650(d);
                                            func_0202da88(self, &data_021c2aac);
                                            func_0202d9d0(self, func_0209b4d4(self->unk_160));
                                        }
                                    }
                                    break;
                            }
                        }
                    }
                }
                break;
            case 3:
                d = (char *) d + 0xa4;
                e = (char *) d + 0x10;
                p = d;
                p = (char *) d + 0x1c;
                if (func_0209bd44(e) != 0) {
                    if (func_0209bc40(e) == 0x15) {
                        if (func_0209bba0(e) == 0) {
                            if (func_0209aebc(d, func_0208150c(c)) != 0) {
                                if (func_0209e3ac(&s.x, p, 0x3f) == 1) {
                                    func_0202da88(self, &data_021c3094);
                                    func_0202d9d0(self, e);
                                }
                            }
                        }
                    }
                }
                break;
        }
    }
    if (func_0202d9c4(self) == 0) {
        func_0202da88(self, &data_021c1d54);
    }
    if (self->cb != 0) {
        (self->*(self->cb))(&s.b);
    }
    s.a = s.c;
    func_02068484(self->unk_40, &s, s.b);
}
