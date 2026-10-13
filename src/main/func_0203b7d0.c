/* func_0203b7d0 @ 0x0203b7d0, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1f4];
    unsigned char flag;
    unsigned char pad_1F5[0xf];
    int unk_204;
    int unk_208;
    int unk_20C;
    int unk_210;
    int unk_214;
    int unk_218;
} UnkStruct_0203b7d0;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} GlobStruct;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0203b7d0_2;

extern GlobStruct *data_021f6948;
extern void func_0203caa4(UnkStruct_0203b7d0 *self, int a, int b);
extern void func_0203c99c(UnkStruct_0203b7d0 *self, int a);
extern void func_0203ad68(void);
extern void func_0203ad58(void);
extern void func_01ffcbb0(int *local, UnkStruct_0203b7d0 *self);
extern UnkStruct_0203b7d0_2 *func_0203c59c(UnkStruct_0203b7d0 *self);

int func_0203b7d0(UnkStruct_0203b7d0 *self)
{
    int local[3];
    UnkStruct_0203b7d0_2 *p;

    if (self->flag == 0) {
        func_01ffcbb0(local, self);
        self->unk_204 = local[0];
        self->unk_208 = local[1];
        self->unk_20C = local[2];
        p = func_0203c59c(self);
        self->unk_210 = p->a;
        self->unk_214 = p->b;
        self->unk_218 = p->c;
        func_0203ad68();
    } else {
        if (data_021f6948->unk_04 == 0) {
            func_0203caa4(self, 0xf, 0);
        } else {
            func_0203caa4(self, 0xe, 0);
        }
        func_0203c99c(self, 1);
        func_0203ad58();
    }
    return 1;
}
