/* func_02009534 @ 0x02009534, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020113e0(short *, short);
extern void func_020110a0(void *, short *);

typedef struct {
    short unk_00;
    short unk_02;
} UnkStruct_02009534;

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x744];
    UnkStruct_02009534 sub;
} UnkStruct_02009534_2;

void func_02009534(UnkStruct_02009534_2 *self)
{
    short tmp;
    UnkStruct_02009534 *sub;

    sub = &self->sub;
    tmp = self->unk_8E;
    sub->unk_02 = tmp;
    func_020113e0(&tmp, sub->unk_00);
    func_020110a0(self, &tmp);
}
