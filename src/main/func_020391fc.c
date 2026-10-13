/* func_020391fc @ 0x020391fc, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct SomeObj {
    unsigned char pad_00[0x64];
    int count;
} SomeObj;

extern SomeObj *data_020ccf94;
extern int func_02073d90(SomeObj *obj);
extern int func_02073dd4(SomeObj *obj, int i);
extern int func_0203919c(int i);
extern const char data_021c675e[];
extern const char data_021c676a[];
extern void func_0203a2f0(char *dst, const char *src, int n);
extern void func_0203a2dc(char *dst);
extern void func_0203a3a4(char *dst, const char *src, int n);
extern void func_0203a38c(char *dst);
extern void func_0203a344(void *p);
extern void func_0203a330(void *p);
extern void func_0203a404(void *p);
extern void func_0203a3ec(void *p);
extern void func_02051984(void *a, void *b);
extern void func_020a8a70(void *a, void *b, int c, int d);
extern void func_020398e8(int i, void *a, void *b);

void func_020391fc(void)
{
    SomeObj *obj = data_020ccf94;
    int count = obj->count;
    int i, zero;
    struct {
        char m0[0xc];
        char m1[0x18];
        char m2[0x14];
        char m3[0x34];
    } tmp;

    if (!func_02073d90(obj)) {
        return;
    }

    i = 0;
    zero = i;

    for (; i < 4; i++) {
        if (i == count) {
            continue;
        }
        if (!func_02073dd4(obj, i)) {
            continue;
        }
        if (!func_0203919c(i)) {
            continue;
        }

        func_0203a2f0(tmp.m0, data_021c675e, 6);
        func_0203a3a4(tmp.m1, data_021c676a, 0x10);
        func_0203a344(tmp.m2);
        func_0203a404(tmp.m3);
        func_02051984(tmp.m2, tmp.m0);
        func_020a8a70(tmp.m3, tmp.m1, zero, zero);
        func_020398e8(i, tmp.m2, tmp.m3);
        func_0203a3ec(tmp.m3);
        func_0203a330(tmp.m2);
        func_0203a38c(tmp.m1);
        func_0203a2dc(tmp.m0);
    }
}
