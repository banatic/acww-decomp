/* func_020350a4 @ 0x020350a4, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00;
    unsigned short unk_04;
    unsigned char pad_06[2];
    int unk_08;
    unsigned char pad_0C[7];
    unsigned char unk_13;
    unsigned char pad_14[8];
} UnkStruct_020350a4;
typedef struct {
    int pad_00[2];
    int unk_08;
} UnkStruct_020350a4_2;
typedef struct {
    UnkStruct_020350a4 arr[0x18];
    unsigned char pad_2A0[0x14];
    int unk_2B4;
} UnkStruct_020350a4_3;

extern int func_02034f44(UnkStruct_020350a4_3 *);
extern UnkStruct_020350a4_2 *func_02034ebc(UnkStruct_020350a4_3 *, int);
extern void func_02035fe4(int *, int);

void func_020350a4(UnkStruct_020350a4_3 *self)
{
    int idx;
    UnkStruct_020350a4 *e;
    UnkStruct_020350a4_2 *r;
    int done;

    idx = func_02034f44(self);
    if (idx < 0) {
        return;
    }
    e = &self->arr[idx];
    if (e->unk_04 == 0xffff) {
        return;
    }
    done = 0;
    if (idx > 0) {
        r = func_02034ebc(self, idx);
        if (r != 0) {
            func_02035fe4(&self->unk_2B4, r->unk_08);
            done = 1;
        }
    }
    if (done == 0) {
        if (e->unk_13 != 0) {
            func_02035fe4(&self->unk_2B4, e->unk_08);
        }
    }
}
