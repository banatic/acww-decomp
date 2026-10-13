/* func_020ee470 @ 0x020ee470, 0x5c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#pragma optimize_for_speed

typedef struct UnkStruct_020ee470 UnkStruct_020ee470;
typedef void (*ObjMethod)(UnkStruct_020ee470 *);

typedef struct ObjVtbl {
    unsigned char pad[0x30];
    ObjMethod method;
} ObjVtbl;

struct UnkStruct_020ee470 {
    ObjVtbl *vtbl;
    unsigned char pad[10];
    unsigned char unk_0E;
    unsigned char unk_0F;
};

void func_020ee470(UnkStruct_020ee470 *self)
{
    unsigned int flag;

    if (self->unk_0F != 0) {
        return;
    }

    flag = (self->unk_0E == 2) ? 1 : 0;
    if (flag != 0) {
        return;
    }

    self->unk_0F = 1;
    self->vtbl->method(self);
}
