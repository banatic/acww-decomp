/* func_ov003_0222250c @ 0x0222250c, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f794(void *, int, int);
extern int func_0204eda8(int, int, int);
extern void func_ov003_02224140(int, int, long long);

typedef struct {
    int unk_00;
    int unk_04;
} OtherStruct;

typedef struct {
    char pad_00[8];
    unsigned short status;
    char pad_0A[14];
    int sub;
    char pad_1C[20];
    int v0;
    int v1;
    int v2;
    int v3;
    int v4;
    int v5;
} UnkStruct_0222250c;

void func_ov003_0222250c(UnkStruct_0222250c *obj, OtherStruct *src, int arg2)
{
    func_0204f794(&obj->sub, src->unk_00, src->unk_04);
    if (func_0204eda8(arg2, src->unk_00, src->unk_04) == 0) {
        obj->status = 0xfc;
    } else {
        obj->status = 0xfd;
    }
    obj->v3 = 0x1000;
    obj->v4 = 0x1000;
    obj->v5 = 0x1000;
    obj->v0 = 0;
    obj->v1 = 0;
    obj->v2 = 0;
    func_ov003_02224140(src->unk_00, src->unk_04, 0xfff1);
}
