/* func_020aab48 @ 0x020aab48, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2c];
    int unk_2C;
    unsigned char unk_30;
} UnkStruct_020aab48;

extern int func_020a7e50(void);
extern int func_020a7e44(void);
extern int func_020aa9fc(UnkStruct_020aab48 *p);
extern void func_020aa880(UnkStruct_020aab48 *p);
extern void func_020aa9c0(UnkStruct_020aab48 *p);
extern int func_020a7f5c(void);
extern int func_020a7f34(void);
extern int func_020a7f84(void);
extern void RtcSendPxiCommand(int cmd);

void func_020aab48(UnkStruct_020aab48 *p)
{
    int a;
    int b;

    if (func_020a7e50()) {
        if (p->unk_2C == 0) {
            if (func_020aa9fc(p)) {
                func_020aa880(p);
            }
        } else if (p->unk_2C == 1) {
            if (p->unk_30) {
                func_020aa9c0(p);
            }
        }
    } else if (func_020a7e44()) {
        if (p->unk_2C == 0) {
            if (!p->unk_30) {
                a = func_020a7f5c();
                b = func_020a7f34();
                if (a || b) {
                    if (a) {
                        RtcSendPxiCommand(0xb);
                    }
                    func_020aa880(p);
                }
            }
        } else if (p->unk_2C == 1) {
            if (func_020a7f84()) {
                RtcSendPxiCommand(0xb);
                func_020aa9c0(p);
            }
        }
    }
}
