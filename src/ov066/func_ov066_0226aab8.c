/* func_ov066_0226aab8 @ 0x0226aab8, 0x6c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct UnkStruct_0226aab8 {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned short unk_04;
} UnkStruct_0226aab8;

extern int func_ov066_02266e08(void);
extern void func_ov066_0226ab24(void *receiver);
extern void func_ov066_0226ab28(UnkStruct_0226aab8 *p);

void func_ov066_0226aab8(UnkStruct_0226aab8 *p)
{
    if (func_ov066_02266e08()) {
        return;
    }
    if (p->unk_02 != 0) {
        return;
    }
    if (p->unk_04 == 7) {
        return;
    }
    if (p->unk_04 != 9) {
        if (p->unk_04 != 0x15) {
            return;
        }
        func_ov066_0226ab28(p);
        return;
    }
    func_ov066_0226ab24((void *) p);
}
