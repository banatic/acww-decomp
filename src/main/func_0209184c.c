/* func_0209184c @ 0x0209184c, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0209184c {
    char pad_00[0x18];
    int **unk_18;
    int pad_1C;
    int unk_20;
    int unk_24;
    int unk_28;
} UnkStruct_0209184c;

typedef struct Key {
    unsigned char b[4];
} Key;

typedef struct Param {
    int pad_00;
    Key key;
    int pad_08;
    UnkStruct_0209184c *obj;
} Param;

typedef struct Elem {
    int unk_00;
    int unk_04;
    int unk_08;
    short unk_0C;
    short unk_0E;
    int unk_10;
    int unk_14;
    int unk_18;
} Elem;

extern Elem data_021d52d8[];
extern void func_020914dc(void *);

int func_0209184c(Param *p)
{
    Key tmp;
    Elem *e;
    int result;
    UnkStruct_0209184c *obj;

    tmp = p->key;
    e = &data_021d52d8[tmp.b[0]];
    result = 0;
    if ((e->unk_14 != (-1)) && (e->unk_0E != 0)) {
        obj = p->obj;
        obj->unk_20 = e->unk_00 + (*obj->unk_18)[1];
        obj->unk_24 = e->unk_04 + (*obj->unk_18)[2];
        obj->unk_28 = e->unk_08 + (*obj->unk_18)[3];
        if (e->unk_0E > 0) {
            ((unsigned char *) p->obj)[0x69] = (unsigned char) (6 * e->unk_0E);
            e->unk_0E--;
        }
        result = 1;
    }
    if (result == 0) {
        func_020914dc(e);
    }
    return result;
}
