/* func_02058be0 @ 0x02058be0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02059674(void *, int);
extern void func_0205967c(void *, void *);
extern void func_020eaca0(void *, void *, void *);

typedef struct {
    char pad_00[12];
    int a;
    int b;
    int c;
} UnkStruct_02058be0;

typedef struct {
    char pad_00[0x60];
    char src[0x24];
    int unk_84;
    int unk_88;
    int unk_8C;
    char pad_90[0x44];
    char d4;
    char pad_D5;
    short d6;
} UnkStruct_02058be0_2;

void func_02058be0(UnkStruct_02058be0_2 *self)
{
    UnkStruct_02058be0 tmp;
    func_02059674(self, 1);
    func_0205967c(self, &tmp);
    func_020eaca0(&tmp.a, self->src, &tmp);
    self->unk_84 = tmp.a;
    self->unk_88 = tmp.b;
    self->unk_8C = tmp.c;
    self->d6 = 0;
    self->d4 = 0;
}
