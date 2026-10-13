/* func_02030580 @ 0x02030580, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct ObjA {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} ObjA;

typedef struct ObjB {
    int unk_00;
    int unk_04;
} ObjB;

typedef struct ObjC {
    int unk_00;
    int unk_04;
} ObjC;

extern int func_020306a4(ObjA *a, ObjB *b);

int func_02030580(ObjA *a, ObjB *b, ObjC *c)
{
    int sum = a->unk_04 + a->unk_10;
    if (c->unk_04 >= sum && b->unk_04 < sum && func_020306a4(a, b)) {
        b->unk_04 = sum;
        return 1;
    }
    return 0;
}
