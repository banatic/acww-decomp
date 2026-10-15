/* func_ov009_022653fc @ 0x022653fc, 0x64 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209d340(void *);
extern void *func_ov009_02262f74(void *);
extern void *func_020b33b8(void *);
extern void *func_020551e0(void *);
extern void *func_02066994(void *);
extern void *func_0203f080(void *);
extern void func_020edf54(void *);

struct UnkStruct_022653fc {
    unsigned int unk_00;
    unsigned char pad_04[0xE8];
    unsigned int unk_EC;
    unsigned char pad_F0[0x4C];
    unsigned int unk_13C;
    unsigned char pad_140[0xB4];
    unsigned int unk_1F4;
    unsigned char pad_1F8[0x40];
    unsigned int unk_238;
    unsigned char pad_23C[0x56];
    unsigned char unk_292[4];
};

extern unsigned char data_ov009_022658dc[];
extern unsigned char data_ov009_022659a0[];

struct UnkStruct_022653fc *func_ov009_022653fc(struct UnkStruct_022653fc *p)
{
    p->unk_00 = (unsigned int) (unsigned int) data_ov009_022658dc;
    p->unk_EC = (unsigned int) (unsigned int) data_ov009_022659a0;
    func_0209d340((void *) &p->unk_292);
    func_ov009_02262f74((void *) &p->unk_238);
    func_020b33b8((void *) &p->unk_1F4);
    func_020551e0((void *) &p->unk_13C);
    func_02066994((void *) &p->unk_EC);
    func_0203f080((void *) p);
    func_020edf54((void *) p);
    return p;
}
