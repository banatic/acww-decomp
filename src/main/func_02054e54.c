/* func_02054e54 @ 0x02054e54, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055260(void *self);
extern void func_02056f04(void *self);
extern char data_020dd0dc[];
extern char data_020dd0ec[];
extern char data_020dd0fc[];

typedef struct UnkStruct_02054e54 {
    void *unk_00;
    unsigned char pad_04[0x98];
    void *unk_9C;
    unsigned char pad_A0[0x18];
    void *unk_B8;
} UnkStruct_02054e54;

UnkStruct_02054e54 *func_02054e54(UnkStruct_02054e54 *this)
{
    func_02055260(this);
    func_02056f04((void *) &this->unk_B8);
    this->unk_00 = data_020dd0dc;
    this->unk_9C = data_020dd0ec;
    this->unk_B8 = data_020dd0fc;
    return this;
}
