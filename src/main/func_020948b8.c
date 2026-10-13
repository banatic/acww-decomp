/* func_020948b8 @ 0x020948b8, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Key {
    unsigned char b[4];
} Key;

typedef struct Entry {
    unsigned char pad_00[14];
    short s;
    int pad_10;
    int unk_14;
    int unk_18;
} Entry;

typedef struct UnkStruct_020948b8 {
    int pad_00;
    int pad_04;
    int pad_08;
    int unk_0C;
} UnkStruct_020948b8;

typedef struct UnkStruct_020948b8_2 {
    int pad_00;
    Key key;
    int pad_08;
    UnkStruct_020948b8 *inner;
} UnkStruct_020948b8_2;

extern Entry data_021d52d8[];
extern int func_02094a4c(void *inner, int a, int b, int c, int d, int e, int f, int g, int h);
extern void func_020914dc(void *e);

int func_020948b8(UnkStruct_020948b8_2 *obj, int a, int b, int c, int d, int e, int f, int g, int h)
{
    Key tmp;
    int result;
    int saved_c = c;
    Entry *cur;

    tmp = obj->key;
    cur = &data_021d52d8[tmp.b[0]];
    result = 0;
    if (cur->unk_14 == (-1)) {
        goto end;
    }
    if (cur->s == (-1)) {
        if (obj->inner->unk_0C > 0) {
            cur->s = 0;
        }
        result = 1;
    }
    if (cur->s != 0) {
        goto end;
    }
    result = func_02094a4c(obj->inner, a, b, saved_c, d, e, f, g, h);
end:
    if (result == 0) {
        func_020914dc(cur);
    }

    return result;
}
