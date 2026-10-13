/* func_02055260 @ 0x02055260, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020557a0(void *);
extern char data_020dd184;
extern char data_020dd05c;
extern char data_020dd06c;

typedef struct {
    void *unk_00;
    char pad_04[0x9c - 4];
    void *unk_9C;
    char pad_A0[0xa4 - (0x9c + 4)];
    unsigned int unk_A4;
    unsigned int unk_A8;
    unsigned int unk_AC;
    char pad_B0[0xb4 - (0xac + 4)];
    unsigned int unk_B4;
} UnkStruct_02055260;

void *func_02055260(void *arg)
{
    UnkStruct_02055260 *obj;
    obj = (UnkStruct_02055260 *) arg;
    func_020557a0(arg);
    obj->unk_9C = &data_020dd184;
    obj->unk_A4 = 0;
    obj->unk_A8 = 0;
    obj->unk_AC = 0x1000;
    obj->unk_00 = &data_020dd05c;
    obj->unk_9C = &data_020dd06c;
    obj->unk_B4 = 0;
    return arg;
}
