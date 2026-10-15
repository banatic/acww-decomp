/* func_0206bffc @ 0x0206bffc, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a9484(void *);

typedef struct UnkStruct_0206bffc {
    void *unk_00;
    char pad_04[0x20];
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    char byte1;
    char byte2;
} UnkStruct_0206bffc;

extern unsigned char data_020def9c[];
extern unsigned char data_020e3e68[];

UnkStruct_0206bffc *func_0206bffc(UnkStruct_0206bffc *this, int a, int b)
{
    func_020a9484(this);
    this->unk_00 = (void *) data_020e3e68;
    this->unk_00 = (void *) data_020def9c;
    this->unk_24 = a;
    this->unk_28 = b;
    this->unk_2C = 0;
    this->unk_30 = 0;
    this->unk_34 = 0;
    this->byte1 = 0;
    this->byte2 = 0;
    return this;
}
