/* func_020aaabc @ 0x020aaabc, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x30];
    unsigned char unk_30;
} UnkStruct_020aaabc;

extern int func_020a7e50(void);
extern int func_020aaa38(void);
extern int func_020a7e44(void);
extern int func_020aaa20(UnkStruct_020aaabc *);
extern void func_020a7e7c(void);
extern int func_020aaa74(UnkStruct_020aaabc *);
extern int func_020aaa54(UnkStruct_020aaabc *);
extern void func_020a7e88(void);

void func_020aaabc(UnkStruct_020aaabc *self)
{
    unsigned char b;
    int flag;
    int res;

    b = self->unk_30;
    if (b) {
        flag = 0;
        res = func_020a7e50();
        if (res) {
            asm { add r0, self, #0 }
            if (func_020aaa38())
            {
                flag = 1;
            }
        } else {
            if (func_020a7e44() && func_020aaa20(self)) {
                flag = 1;
            }
        }
        if (flag) {
            self->unk_30 = 0;
            func_020a7e7c();
        }
    } else {
        flag = 0;
        res = func_020a7e50();
        if (res) {
            if (func_020aaa74(self)) {
                flag = 1;
            }
        } else {
            if (func_020a7e44() && func_020aaa54(self)) {
                flag = 1;
            }
        }
        if (flag) {
            self->unk_30 = 1;
            func_020a7e88();
        }
    }
}
