/* func_020c1278 @ 0x020c1278, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec;
typedef struct {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x24];
    Vec unk_34;
    Vec unk_40;
    char pad_4C[0xc];
    int unk_58;
    char pad_5C[4];
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
} UnkStruct_020c1278;
extern int func_020644cc(int);
extern int data_020e5974;
extern int data_020d22fc[];
extern int data_020d22f0[];

void func_020c1278(UnkStruct_020c1278 *p, int mode)
{
    int z = 0;
    int k;
    int v;
    Vec *q;
    Vec *w;
    k = func_020644cc(3);
    v = (func_020644cc(0x80) * data_020e5974 + 0x80) << 12;
    data_020e5974 = data_020e5974 * ~z;
    q = &p->unk_34;
    q->x = v;
    q->y = (int) 0xfffec000;
    q->z = z;
    w = &p->unk_40;
    w->x = z;
    w->y = data_020d22fc[k];
    w->z = z;

    p->unk_60 = func_020644cc(0x300) + 0x180;
    p->unk_64 = func_020644cc(0x10000);
    p->unk_68 = k;
    p->unk_6C = v;
    p->unk_70 = func_020644cc(2) + 0x5000;
    p->unk_0C = data_020d22f0[k];
    p->unk_58 = 2;
    if (mode == 1) {
        p->unk_34.y = p->unk_34.y + (func_020644cc(0x1c1) << 12);
    }
}
