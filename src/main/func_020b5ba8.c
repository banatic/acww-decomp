/* func_020b5ba8 @ 0x020b5ba8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} ObjType;

typedef struct {
    char pad_00[0x50];
    int unk_50;
} ParamType;

extern ObjType *data_020ccf94;
extern int func_02073dd4(ObjType *obj, int val);
extern void func_0200471c(void);
extern void func_020b68f8(void);
extern void func_02003108(void);
extern void func_0208f930(void);

int func_020b5ba8(ParamType *param)
{
    ObjType *obj = data_020ccf94;

    if (func_02073dd4(obj, obj->unk_64) != 0) {
        param->unk_50 = 0;
    } else {
        param->unk_50 = 1;
    }

    func_0200471c();
    func_020b68f8();
    func_02003108();
    func_0208f930();

    return 1;
}
