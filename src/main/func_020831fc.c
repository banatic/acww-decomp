/* func_020831fc @ 0x020831fc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __arm __cxa_vec_cleanup(void *, int, int, void (*)(void));
extern void func_02083c78(void *);
extern void func_02083294(void);

typedef struct {
    void *unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_020831fc;

extern unsigned char data_020e1b00[];

UnkStruct_020831fc *func_020831fc(UnkStruct_020831fc *p)
{
    p->unk_00 = (void *) data_020e1b00;
    __cxa_vec_cleanup(&p->unk_08, 5, 0x6c, func_02083294);
    func_02083c78(p);
    return p;
}
