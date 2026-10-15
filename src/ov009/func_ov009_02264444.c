/* func_ov009_02264444 @ 0x02264444, 0x13c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b3b50(void *);
extern unsigned char func_020b3d90(void *argument0);
extern void *func_020e9948(void *, int);
extern int func_ov003_02220150(void *);
extern int func_020b3d04(void *, void *, void *, void *, int);
extern void func_ov009_02265660(void *, void *, void *);
extern void func_01ffd070(void *, void *, void *);
extern void *func_020b8038(void *);
extern int func_020b6590(void);
extern int func_020b7cf4(int, void *, void *, void *, void *, int, int);
extern void *func_ov009_02264370(void *);
extern int func_ov009_02264c90(void *);
extern void func_020326c4(void *, void *, void *, void *, int);
extern int func_02032694(void *);
extern void *data_021c9b1c;

typedef struct {
    unsigned char pad_00[0x5c];
    char unk_5C[0x136 - 0x5c];
    char unk_136[1];
    unsigned char pad_137[0x288 - (0x136 + 1)];
    void *unk_288;
    void *unk_28C;
    unsigned char unk_290;
} UnkStruct_02264444;

typedef struct {
    unsigned char pad_00[0x4c];
    void *unk_4C;
    int unk_50;
} UnkStruct_02264444_2;

typedef struct {
    unsigned char pad_00[0x44];
} UnkStruct_02264444_3;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

void func_ov009_02264444(UnkStruct_02264444 *self, void *arg2)
{
    void *ptr0;
    unsigned char counter;
    Vec3 local0, local1, local2;
    Vec3 out0, out1, out2;
    Vec3 out20, out21, out22;
    UnkStruct_02264444_2 *r4;
    UnkStruct_02264444_3 *r6;
    unsigned int i;
    int tmp;

    self->unk_290 = 0;

    ptr0 = func_020b3b50(&self->unk_136);
    if (ptr0 == 0) {
        return;
    }

    self->unk_290 = func_020b3d90(ptr0);
    if (self->unk_290 == 0) {
        return;
    }

    self->unk_288 = func_020e9948(data_021c9b1c, self->unk_290 * 0x44);
    self->unk_28C = func_020e9948(data_021c9b1c, self->unk_290 * 0x54);

    r4 = self->unk_28C;
    r6 = self->unk_288;

    counter = (unsigned char) func_ov003_02220150(self);

    for (i = 0; i < self->unk_290; i++) {
        if (func_020b3d04(ptr0, &local0, &local1, &local2, i) != 0) {
            func_ov009_02265660(&out0, &local0, arg2);
            func_ov009_02265660(&out1, &local1, arg2);
            func_ov009_02265660(&out2, &local2, arg2);
            func_01ffd070(&out20, self->unk_5C, &local0);
            func_01ffd070(&out21, self->unk_5C, &local1);
            func_01ffd070(&out22, self->unk_5C, &local2);
            if (r6 != 0) {
                r6 = (UnkStruct_02264444_3 *) func_020b8038((void *) r6);
            }
            tmp = func_020b6590();
            func_020b7cf4(tmp, (void *) r6, &out0, &out1, &out2, 7, counter);
            if (r4 != 0) {
                r4 = (UnkStruct_02264444_2 *) func_ov009_02264370((void *) r4);
            }
            r4->unk_4C = self;
            r4->unk_50 = func_ov009_02264c90(self);
            func_020326c4(r4, &out20, &out21, &out22, 0x3000);
            func_02032694(r4);
        }
        r4++;
        r6++;
    }
}
