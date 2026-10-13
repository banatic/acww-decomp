/* func_ov003_02219930 @ 0x02219930, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int arg);
extern int func_020e8ed8(int a, int b);
extern int func_02008dc0(void *obj, int a, int b, int c);

typedef struct {
    int unk_00;
    int pad;
    int unk_08;
} UnkStruct_02219930;

typedef struct {
    char pad[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
} ObjStruct;

int func_ov003_02219930(UnkStruct_02219930 *self)
{
    ObjStruct *obj = func_02096718(4);
    if (obj) {
        int a = self->unk_00 - obj->unk_5C;
        int b = self->unk_08 - obj->unk_64;
        int c = func_020e8ed8(a, b);
        return func_02008dc0(obj, c, 6, -1);
    }
    return 0;
}
