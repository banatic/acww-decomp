/* func_ov003_0220c220 @ 0x0220c220, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_02238010;
extern char data_ov003_02238078;
extern int func_020b7f60(void *p);
extern void *func_02066994(void **p);
extern void *func_0203f080(void *p);
extern void func_020edf54(void *p);

typedef struct UnkStruct_0220c220 {
    void *vt0;
    unsigned char pad_04[0xec - 4];
    void *unk_EC;
    unsigned char pad_F0[0x138 - 0xec - 4];
    unsigned char unk_138[1];
} UnkStruct_0220c220;

struct UnkStruct_0220c220 *func_ov003_0220c220(struct UnkStruct_0220c220 *this)
{
    this->vt0 = &data_ov003_02238010;
    this->unk_EC = &data_ov003_02238078;
    func_020b7f60(&this->unk_138);
    func_02066994(&this->unk_EC);
    func_0203f080(this);
    func_020edf54(this);
    return this;
}
