/* func_02054b64 @ 0x02054b64, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020dd0ac;
extern unsigned char data_020dd0bc;
extern unsigned char data_020dd0cc;

extern void func_02056ed4(void *p);
extern void func_02057078(void *p);
extern void func_02054d9c(void *p);

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x98];
    void *unk_9C;
    unsigned char pad_A0[0x18];
    void *unk_B8;
    unsigned char pad_BC[0x3c];
    unsigned char unk_F8[0x18];
    unsigned char unk_110[0x1];
} UnkStruct_02054b64;

UnkStruct_02054b64 *func_02054b64(UnkStruct_02054b64 *p)
{
    p->unk_00 = (void *) &data_020dd0ac;
    p->unk_9C = (void *) &data_020dd0bc;
    p->unk_B8 = (void *) &data_020dd0cc;
    func_02056ed4(p->unk_110);
    func_02057078(p->unk_F8);
    func_02054d9c(p);
    return p;
}
