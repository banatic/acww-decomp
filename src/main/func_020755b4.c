/* func_020755b4 @ 0x020755b4, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} unk_struct;

extern int func_02090040(int);
extern void func_02090174(int);
extern void MI_CpuCopy8(unsigned char *, int, int);
extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a242c(int, int, int);
extern unk_struct *data_020ccf94;

void func_020755b4(unsigned char *payload, unsigned int length, int player)
{
    if (length == 1) {
        if (*payload != 0) {
            func_02090174(func_02090040(4));
        }
    } else {
        MI_CpuCopy8(payload, func_02090040(4), 0x950);
    }
    if (func_020b65c4() != 0x2e) {
        return;
    }
    if (func_020a132c() == 0) {
        return;
    }
    func_020a242c(func_020a132c(), data_020ccf94->unk_64, 1);
}
