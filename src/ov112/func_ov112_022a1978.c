/* func_ov112_022a1978 @ 0x022a1978, 0x74 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022a1978 {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
} UnkStruct_022a1978;

extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern void func_ov112_0229ff5c(UnkStruct_022a1978 *p);
extern void func_ov112_022a12a4(UnkStruct_022a1978 *p);
extern void func_ov112_022a19ec(UnkStruct_022a1978 *p);
extern void func_ov112_022a122c(UnkStruct_022a1978 *p);

int func_ov112_022a1978(UnkStruct_022a1978 *p)
{
    func_0206f58c();
    if (func_0206f56c() != 0) {
        switch (p->unk_8D) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 9:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 17:
            case 19:
                func_ov112_0229ff5c(p);
                return 1;
            case 7:
            case 8:
            case 10:
            case 16:
            case 18:
                break;
        }
    }
    func_ov112_022a12a4(p);
    func_ov112_022a19ec(p);
    func_ov112_022a122c(p);
    return 1;
}
