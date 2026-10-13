/* func_ov004_0221b0c4 @ 0x0221b0c4, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov004_0225328c;
extern char data_ov004_022532f4;
extern void func_020b7f60(void *p);
extern void func_02066994(void **p);
extern void func_0203f080(void *p);
extern __arm void func_020edf54(void *p);

typedef struct UnkStruct_0221b0c4 {
    void *vt0;
    unsigned char pad_04[0xec - 4];
    void *unk_EC;
    unsigned char pad_F0[0x138 - 0xec - 4];
    unsigned char unk_138[1];
} UnkStruct_0221b0c4;

struct UnkStruct_0221b0c4 *func_ov004_0221b0c4(struct UnkStruct_0221b0c4 *this)
{
    this->vt0 = &data_ov004_0225328c;
    this->unk_EC = &data_ov004_022532f4;
    func_020b7f60(&this->unk_138);
    func_02066994(&this->unk_EC);
    func_0203f080(this);
    func_020edf54(this);
    return this;
}
