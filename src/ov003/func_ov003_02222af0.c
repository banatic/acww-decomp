/* func_ov003_02222af0 @ 0x02222af0, 0x76 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02045c84(int, int *, int);
extern int func_0204e414(void);
extern int func_0204f5e0(int, int, int, int, int, int);
extern void func_ov003_02222d8c(int, int, int *);
extern void func_02045ea8(int *, int, int);

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_02222af0;

int func_ov003_02222af0(UnkStruct_02222af0 *obj)
{
    int local_8[2];
    int local_10[2];
    int local_18[2];
    int ret1, ret2;
    int v8, vC;
    int h8, hC, l8, lC;

    if (obj->unk_10 == 1) {
        goto exit;
    }

    local_8[0] = obj->unk_08;
    local_8[1] = obj->unk_0C;
    if (func_02045c84(obj->unk_04, local_8, 0) < 0) {
        goto exit;
    }

    ret1 = func_0204e414();
    if (ret1 == 0) {
        goto exit;
    }

    v8 = obj->unk_08;
    vC = obj->unk_0C;
    h8 = v8 >> 4;
    hC = vC >> 4;
    lC = vC - (hC << 4);
    l8 = v8 - (h8 << 4);
    ret2 = func_0204f5e0(ret1, h8, hC, l8, lC, 0);
    if (ret2 == 0) {
        goto exit;
    }

    local_10[0] = obj->unk_08;
    local_10[1] = obj->unk_0C;
    func_ov003_02222d8c(ret2, obj->unk_04, local_10);

exit:
    local_18[0] = obj->unk_08;
    local_18[1] = obj->unk_0C;
    func_02045ea8(local_18, obj->unk_04, 0);
    obj->unk_00 = 0;
    return 0;
}
