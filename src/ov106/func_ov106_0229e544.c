/* func_ov106_0229e544 @ 0x0229e544, 0x138 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229e544 {
    char pad_00[0xac];
    void *unk_AC;
    void *unk_B0;
    char pad_B4[3];
    unsigned char unk_B7;
} UnkStruct_0229e544;

extern int func_0206f56c(void);
extern void func_ov106_0229cd60(UnkStruct_0229e544 *, int);
extern void func_ov106_0229c378(UnkStruct_0229e544 *);
extern int func_ov002_02207d24(void *, int);
extern void func_ov106_0229ce38(UnkStruct_0229e544 *);
extern void func_ov106_0229d00c(UnkStruct_0229e544 *);
extern int func_ov106_0229d2e4(UnkStruct_0229e544 *, void *, void *, int);
extern int func_ov106_0229d3a0(UnkStruct_0229e544 *, int);
extern int func_ov106_0229d390(UnkStruct_0229e544 *, int);
extern void func_ov106_0229d518(UnkStruct_0229e544 *, int, int);
extern int func_ov106_0229d090(UnkStruct_0229e544 *, int);
extern int func_ov106_0229d0d0(UnkStruct_0229e544 *, int);
extern int func_ov106_0229d29c(UnkStruct_0229e544 *, int);
extern void func_ov106_0229d4e4(UnkStruct_0229e544 *, int, void *);
extern void func_ov106_0229cfd0(UnkStruct_0229e544 *, int);
extern void func_ov106_0229d73c(UnkStruct_0229e544 *);
extern void func_ov094_022999d8(void);

extern unsigned char data_021fbdd8;

void func_ov106_0229e544(UnkStruct_0229e544 *param)
{
    void *r6;
    int r4;

    if (func_0206f56c()) {
        func_ov106_0229cd60(param, param->unk_B7);
        func_ov106_0229c378(param);
        func_ov002_02207d24((char *) param + 0x21b8, 0);
        return;
    }

    func_ov106_0229ce38(param);
    func_ov106_0229d00c(param);
    r6 = (void *) ((char *) param->unk_AC + 8);
    r4 = func_ov106_0229d2e4(param, r6, (char *) param->unk_B0 + 0x18, 0);

    if (r4 == 0x20) {
        goto label20;
    }
    if (data_021fbdd8 != 0) {
        goto gflag_nonzero;
    }

    if (func_ov106_0229d3a0(param, param->unk_B7) != 0 && func_ov106_0229d390(param, r4) != 0) {
        func_ov106_0229d518(param, param->unk_B7, 4);
        return;
    }

    if (func_ov106_0229d390(param, param->unk_B7) != 0 && func_ov106_0229d3a0(param, r4) != 0 &&
        func_ov106_0229d090(param, r4) == 0) {
        func_ov106_0229d518(param, param->unk_B7, 4);
        return;
    }

    if (func_ov106_0229d0d0(param, r4) != 0 || func_ov106_0229d29c(param, r4) == 0) {
        func_ov106_0229d4e4(param, param->unk_B7, r6);
    } else {
        func_ov094_022999d8();
        func_ov106_0229d73c(param);
    }
    goto end;

gflag_nonzero:
    if (func_ov106_0229d3a0(param, param->unk_B7) != 0 && func_ov106_0229d390(param, r4) != 0) {
        goto end;
    }
    func_ov106_0229cfd0(param, r4);
    goto end;

label20:
    if (data_021fbdd8 == 0) {
        func_ov106_0229d4e4(param, param->unk_B7, r6);
    }
end:
    return;
}
