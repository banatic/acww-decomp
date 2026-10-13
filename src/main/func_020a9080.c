/* func_020a9080 @ 0x020a9080, 0xe2 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x24];
    int unk_24;
    unsigned char pad_28[4];
    int unk_2C;
} UnkStruct_020a9080;

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[16];
} Info_020a9080;

extern void func_020a8754(void *);
extern void func_020a8764(void *, int);
extern int func_020a83ec(void *);
extern void func_020a8328(void *, int *, int *, int *);
extern int func_02068114(void);
extern void func_020a93e8(UnkStruct_020a9080 *, int);
extern void func_020a9334(UnkStruct_020a9080 *, int);
extern void func_020a8e4c(int, int);
extern int func_02050c40(void);
extern int func_02050c38(void);
extern int func_02050c30(void);
extern int func_02050c48(void);
extern int func_02050c50(void);
extern int func_02050c18(void);
extern int func_02050c10(void);

void func_020a9080(UnkStruct_020a9080 *self, int param)
{
    int v0, v1, v2;
    Info_020a9080 info;
    int cmd, val, result;

    func_020a8754(&info);
    func_020a8764(&info, param);

    cmd = info.unk_00;
    val = info.unk_04;

    if (cmd == 2) {
        func_020a93e8(self, func_020a83ec(&info));
    } else if (cmd == 0xff) {
        if (val == 2) {
            func_020a8328(&info, &v0, &v1, &v2);
            if (func_02068114() == 0) {
                func_020a93e8(self, v0 * 2);
                func_020a9334(self, v2);
                self->unk_2C = v2 + ((v1 - v2) ^ 1);
            }
        }
    } else if (cmd == 0) {
        result = 0;
        if (val == 0) {
            result = func_02050c40();
        } else if (val == 1) {
            result = func_02050c38();
        } else if (val == 6) {
            result = func_02050c30();
        } else if (val == 7) {
            result = func_02050c48();
        } else if (val == 8) {
            result = func_02050c50();
        } else if (val == 9) {
            result = func_02050c18();
        } else if (val == 10) {
            result = func_02050c10();
        }
        if (result != 0) {
            func_020a9334(self, result);
        }
    }

    if (self->unk_24 != 0) {
        func_020a8e4c(self->unk_24, param);
    }
}
