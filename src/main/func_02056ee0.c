/* func_02056ee0 @ 0x02056ee0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020dd174;
extern __arm void MI_CpuFill8(void *, unsigned char, unsigned int);

typedef struct {
    void *data;
    unsigned char bytes[0x24];
    unsigned char pad_28[0xc];
    int unk_34;
    int unk_38;
} TStruct;

TStruct *func_02056ee0(TStruct *this)
{
    this->data = &data_020dd174;
    MI_CpuFill8(this->bytes, 0, 0x24);
    this->unk_34 = 0;
    this->unk_38 = 0;
    return this;
}
