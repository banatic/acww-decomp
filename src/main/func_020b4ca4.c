/* func_020b4ca4 @ 0x020b4ca4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a9484(void *);

typedef struct {
    volatile unsigned int unk_00;
    char pad_04[0x20];
    volatile int unk_24;
    volatile int unk_28;
    volatile int unk_2C;
    volatile int unk_30;
    volatile unsigned char unk_34;
    char pad_35[3];
    volatile int unk_38;
    volatile int unk_3C;
} UnkStruct_020b4ca4;

extern unsigned char data_020e3e68[];
extern unsigned char data_020e5254[];

UnkStruct_020b4ca4 *func_020b4ca4(UnkStruct_020b4ca4 *this)
{
    func_020a9484(this);
    this->unk_00 = (unsigned int) data_020e3e68;
    this->unk_00 = (unsigned int) data_020e5254;
    this->unk_24 = 0;
    this->unk_28 = 0;
    this->unk_2C = 0;
    this->unk_30 = 0;
    this->unk_34 = 0;
    this->unk_38 = 0;
    this->unk_3C = 0;
    return this;
}
