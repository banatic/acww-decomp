/* func_020ba13c @ 0x020ba13c, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct ObjStruct ObjStruct;
struct ObjStruct {
    int pad_00;
    int unk_04;
};

typedef struct {
    int pad_00;
    ObjStruct *ptr;
} UnkStruct_020ba13c;

extern void DC_FlushRange(ObjStruct *obj, int arg);
extern void NNS_G3dTexLoad(ObjStruct *obj, int arg);
extern void NNS_G3dPlttLoad(ObjStruct *obj, int arg);

void func_020ba13c(UnkStruct_020ba13c *param)
{
    ObjStruct *obj = param->ptr;
    DC_FlushRange(obj, obj->unk_04);
    NNS_G3dTexLoad(obj, 1);
    NNS_G3dPlttLoad(obj, 1);
}
