/* func_ov104_0229e63c @ 0x0229e63c, 0xd8 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229e63c {
    char pad_00[0xa8];
    char *unk_A8;
    char *unk_AC;
    char pad_B0[0xb7 - 0xb0];
    unsigned char unk_B7;
} UnkStruct_0229e63c;

extern unsigned char data_021fbdd8;
extern void func_ov104_0229d554(void *);
extern void func_ov104_0229d724(void *);
extern int func_ov104_0229d9bc(void *, void *, void *, int);
extern int func_ov104_0229da80(void *, int);
extern int func_ov104_0229da70(void *, int);
extern int func_ov104_0229d7bc(void *, int);
extern int func_ov104_0229d7fc(void *, int);
extern int func_ov104_0229d974(void *, int);
extern int func_ov104_0229db30(void *, int, void *);
extern void func_ov104_0229d6e8(void *, int);
extern void func_ov104_0229dd00(void *);
extern void func_ov094_022999d8(void);

void func_ov104_0229e63c(void *obj)
{
    UnkStruct_0229e63c *o;
    char *p1;
    int ret;

    func_ov104_0229d554(obj);
    func_ov104_0229d724(obj);
    o = (UnkStruct_0229e63c *) obj;
    p1 = o->unk_A8 + 8;
    ret = func_ov104_0229d9bc(obj, p1, o->unk_AC + 0x18, 0);

    if (func_ov104_0229da80(obj, ret) != 0) {
        if (func_ov104_0229da70(obj, o->unk_B7) != 0) {
            goto L69e;
        }
    }
L682:
    if (func_ov104_0229da70(obj, ret) == 0) {
        goto L6ac;
    }
    if (func_ov104_0229da80(obj, o->unk_B7) == 0) {
        goto L6ac;
    }
L69e:
    if (func_ov104_0229d7bc(obj, ret) != 0) {
        goto L6ac;
    }
    ret = 0x21;
L6ac:
    if (ret == 0x21) {
        goto L6f4;
    }
    if (data_021fbdd8 != 0) {
        goto L6ea;
    }
    if (func_ov104_0229d7fc(obj, ret) != 0) {
        goto L6d0;
    }
    if (func_ov104_0229d974(obj, ret) != 0) {
        goto L6de;
    }
L6d0:
    func_ov104_0229db30(obj, o->unk_B7, p1);
    goto exit;
L6de:
    func_ov094_022999d8();
    func_ov104_0229dd00(obj);
    goto exit;
L6ea:
    func_ov104_0229d6e8(obj, ret);
    goto exit;
L6f4:
    if (data_021fbdd8 != 0) {
        goto exit;
    }
    func_ov104_0229db30(obj, o->unk_B7, p1);
exit:
    return;
}
