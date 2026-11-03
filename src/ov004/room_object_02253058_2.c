/* room_object_02253058_2: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02217c10 @ 0x02217c10, 0x2 bytes, Thumb
 * func_ov004_02217c0c @ 0x02217c0c, 0x4 bytes, Thumb
 * func_ov004_02217bdc @ 0x02217bdc, 0x30 bytes, Thumb
 * func_ov004_02217bd8 @ 0x02217bd8, 0x4 bytes, Thumb
 * func_ov004_02217bb0 @ 0x02217bb0, 0x26 bytes, Thumb
 */

struct UnkStruct_02217bdc {
    int unk_00;
    int unk_04;
};

struct UnkStruct_02217bdc_2 {
    char pad_00[0xec];
    char unk_EC[0x40];
    struct UnkStruct_02217bdc *unk_12C;
};

extern void func_0203ee08(struct UnkStruct_02217bdc_2 *obj, char *ptr);
extern int func_0203e020(struct UnkStruct_02217bdc_2 *obj);
extern int func_0204bcdc(char *self);
extern int func_02053990(char *self);

void func_ov004_02217c10(void *callbackObject) {}

int func_ov004_02217c0c(void *callbackObject)
{
    return 1;
}

void func_ov004_02217bdc(struct UnkStruct_02217bdc_2 *obj)
{
    if (obj->unk_12C && obj->unk_12C->unk_04 == 0) {
        char *p = (char *) obj;
        if (p) {
            p += 0xec;
        }
        func_0203ee08(obj, p);
        func_0203e020(obj);
    }
}

int func_ov004_02217bd8(void *callbackObject)
{
    return 1;
}

int func_ov004_02217bb0(char *self, int b)
{
    int r;
    if (b == 0 && func_0204bcdc(self) != 0 && func_02053990(self) == 5) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
