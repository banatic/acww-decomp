/* func_02054e18 @ 0x02054e18, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02054e18 {
    void *unk_00;
    char pad_04[0x98];
    void *unk_9C;
    char pad_A0[0x18];
    void *unk_B8;
};

void func_02056eb0(void *p);
void func_0205517c(void *p);

extern unsigned char data_020dd0dc[];
extern unsigned char data_020dd0ec[];
extern unsigned char data_020dd0fc[];

void *func_02054e18(struct UnkStruct_02054e18 *self)
{
    self->unk_00 = (void *) data_020dd0dc;
    self->unk_9C = (void *) data_020dd0ec;
    self->unk_B8 = (void *) data_020dd0fc;
    func_02056eb0(&self->unk_B8);
    func_0205517c(self);
    return self;
}
