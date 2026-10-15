/* func_020281f0 @ 0x020281f0, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern int func_020984e8(void);
extern void *func_02099734(int);
extern int func_0202d9c4(void *);
extern int func_0209bc40(int);
extern void *func_0202d754(void *);
extern int func_02065ec0(unsigned char *);
extern void func_0202da88(void *, const char *);
extern void func_02066650(void *);
extern int func_02068484(void *, char *, int);
}

struct UnkStruct_020281f0;

struct UnkStruct_020281f0 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x6c];
    void (UnkStruct_020281f0::*pmf)(void *);
};

extern unsigned char data_021c2a7c[];
extern unsigned char data_021c2a94[];

extern "C" void func_020281f0(UnkStruct_020281f0 *obj)
{
    unsigned char c;
    struct {
        int a;
        unsigned char b;
    } inner;

    void *r5 = func_02099734(func_020984e8());
    if (func_0209bc40(func_0202d9c4(obj)) == 0x13) {
        r5 = func_0202d754(r5);
        if (r5 != 0) {
            if (func_02065ec0((unsigned char *) r5) == 7) {
                func_0202da88(obj, (const char *) data_021c2a7c);
            } else {
                func_0202da88(obj, (const char *) data_021c2a94);
            }
            func_02066650(r5);
        }
    }

    if (obj->pmf) {
        (obj->*(obj->pmf))(&inner);
    }

    c = inner.b;
    func_02068484(obj->unk_40, (char *) &c, inner.a);
}
