/* text_draw: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02050ef4 @ 0x02050ef4, 0x18 bytes, Thumb
 * func_02050edc @ 0x02050edc, 0x18 bytes, Thumb
 * func_02050ea8 @ 0x02050ea8, 0x32 bytes, Thumb
 * func_02050e74 @ 0x02050e74, 0x32 bytes, Thumb
 * func_02050e68 @ 0x02050e68, 0xc bytes, Thumb
 */

struct UnkStruct_02050ef4 {
    unsigned char pad_00[0x40];
    unsigned int a;
    unsigned int b;
    unsigned char pad_48[0x30];
    unsigned int c;
};

typedef struct {
    unsigned char unk_00[0x38];
    unsigned char unk_38;
    unsigned char pad_39;
    unsigned char unk_3A;
    unsigned char pad_3B;
    unsigned char unk_3C;
} UnkStruct_02050ea8;

extern void func_02051400(int arg);

int func_02050ef4(struct UnkStruct_02050ef4 *s)
{
    int result = 0;
    if (s->c >= s->a && s->c < s->a + s->b) {
        result = 1;
    }
    return result;
}

int func_02050edc(void *self)
{
    int result;
    unsigned int field_48;
    unsigned int field_78;
    unsigned int field_4c;

    result = 0;
    field_48 = *(unsigned int *) ((char *) self + 0x48);
    field_78 = *(unsigned int *) ((char *) self + 0x78);
    if (field_78 >= field_48) {
        field_4c = *(unsigned int *) ((char *) self + 0x4c);
        if (field_78 < field_48 + field_4c) {
            result = 1;
        }
    }
    return result;
}

unsigned char func_02050ea8(UnkStruct_02050ea8 *s)
{
    unsigned char result;

    result = s->unk_38;
    if (func_02050ef4((struct UnkStruct_02050ef4 *) s)) {
        result = s->unk_3A;
    } else {
        if (func_02050edc(s)) {
            result = s->unk_3C;
        }
    }
    return result;
}

unsigned char func_02050e74(void *arg0)
{
    unsigned char r5;
    void *r4 = arg0;
    r5 = *(unsigned char *) ((char *) r4 + 0x39);
    if (func_02050ef4((struct UnkStruct_02050ef4 *) r4)) {
        r4 = (char *) r4 + 0x3b;
        r5 = *(unsigned char *) r4;
    } else {
        if (func_02050edc(r4)) {
            r4 = (char *) r4 + 0x3d;
            r5 = *(unsigned char *) r4;
        }
    }
    return r5;
}

void func_02050e68(void)
{
    func_02051400(0);
}
