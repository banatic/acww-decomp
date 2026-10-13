/* func_ov107_0229cf90 @ 0x0229cf90, 0x54 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

typedef struct SomeObj {
    unsigned char pad_before[0xb7];
    unsigned char unk_B7;
    unsigned char unk_B8;
    unsigned char pad_after[0x21cd - 0xb9];
} SomeObj;

extern int func_ov107_0229d388(SomeObj *obj, unsigned char val);
extern int func_ov107_0229d128(SomeObj *obj, unsigned char val);
extern void func_ov002_02207cf0(void *addr);
extern void func_ov002_02207cf8(void *addr);

void func_ov107_0229cf90(SomeObj *obj)
{
    if (func_ov107_0229d388(obj, obj->unk_B8)) {
        if (func_ov107_0229d128(obj, obj->unk_B8)) {
            func_ov002_02207cf0((char *) obj + 0x21cc);
        } else {
            obj->unk_B7 = obj->unk_B8;
            func_ov002_02207cf8((char *) obj + 0x21cc);
        }
    } else {
        func_ov002_02207cf0((char *) obj + 0x21cc);
    }
}
