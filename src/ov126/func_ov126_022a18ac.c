/* func_ov126_022a18ac @ 0x022a18ac, 0xfc bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

// Two equality tests written as a two-case switch.

typedef struct UnkStruct_022a18ac {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_022a18ac;

extern UnkStruct_022a18ac *data_020ccf94;

extern void func_ov126_0229f7a8(void *, int);
extern unsigned int func_0206fca4(void);
extern void *func_020ee45c(void *);
extern void func_ov090_022993cc(void *, int);
extern int func_ov126_0229f7c8(void *, int);
extern void func_0206f51c(void);
extern int func_02073dd4(UnkStruct_022a18ac *, int);
extern int func_020ec1e8(void);
extern void func_ov002_02208090(void *, int);
extern void func_ov126_022a185c(void *);
extern void func_ov092_02299324(void *, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov126_022a16ac(void *);

void func_ov126_022a18ac(void *o)
{
    unsigned int st;
    void *h;
    int r;

    func_ov126_0229f7a8(o, 2);
    st = func_0206fca4();
    if (st >= 0x18 && st <= 0x1b) {
        h = func_020ee45c(o);
        switch (st) {
            case 0x18:
            case 0x1a:
                func_ov090_022993cc(h, 6);
                if (func_ov126_0229f7c8(o, 0x40) == 0) {
                    func_0206f51c();
                }
                break;
            case 0x19:
                if (func_ov126_0229f7c8(o, 0x40) != 0) {
                    func_ov090_022993cc(h, 0xc);
                } else {
                    func_ov090_022993cc(h, 6);
                    func_0206f51c();
                    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64)) {
                        r = func_020ec1e8();
                        switch (r) {
                            case 3:
                            case 4:
                                func_ov002_02208090(o, 4);
                                func_ov126_022a185c(o);
                                return;
                        }
                    }
                }
                break;
            case 0x1b:
                if (func_ov126_0229f7c8(o, 0x40) != 0) {
                    func_ov090_022993cc(h, 0xe);
                } else {
                    func_ov090_022993cc(h, 0xa);
                }
                break;
        }
    } else {
        func_ov092_02299324(func_020ee45c(o), 0x44, 1);
    }
    func_ov002_02207f04(o, 0xa, 0, 0, 0x30);
    func_ov126_022a16ac(o);
    func_ov002_02208090(o, 5);
}
