/* __sinit_020c52d8 @ 0x020c52d8, 0x12c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    short unk_00;
    short unk_02;
} UnkStruct_020c52d8;
extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void __register_global_object(void *, void *, void *);
extern void func_020530d4(void *);
extern UnkStruct_020c52d8 data_021c874c;
extern UnkStruct_020c52d8 data_021c8754;
extern UnkStruct_020c52d8 data_021c8758;
extern UnkStruct_020c52d8 data_021c875c;
extern UnkStruct_020c52d8 data_021c8760;
extern UnkStruct_020c52d8 data_021c876c;
extern UnkStruct_020c52d8 data_021c8770;
extern UnkStruct_020c52d8 data_021c8764;
extern UnkStruct_020c52d8 data_021c8768;
extern UnkStruct_020c52d8 data_021c87a4;
extern UnkStruct_020c52d8 data_021c87a8;
extern UnkStruct_020c52d8 data_021c87ac;
extern UnkStruct_020c52d8 data_021c87b0;
extern unsigned char data_021c89fc;
extern void func_020530b0(void);
extern void func_020534cc(void);
extern unsigned char data_021c8780;
extern unsigned char data_021c884c;
extern void func_020534ac(void);
extern unsigned char data_021c8798;
extern unsigned char data_021c87b4;
extern unsigned char data_021c878c;
extern unsigned char data_021c87fc;
extern void func_0205349c(void);
extern void func_02053498(void);
extern void func_0205347c(void);
extern unsigned char data_021c8774;

void __sinit_020c52d8(void)
{
    UnkStruct_020c52d8 *p;
    __cxa_vec_ctor((void *) &data_021c89fc, 8, 72, (void *) &func_020530d4, (void *) &func_020530b0);
    __register_global_object(0, (void *) &func_020534cc, (void *) &data_021c8780);
    __cxa_vec_ctor((void *) &data_021c884c, 6, 72, (void *) &func_020530d4, (void *) &func_020530b0);
    __register_global_object(0, (void *) &func_020534ac, (void *) &data_021c8798);
    func_020530d4((void *) &data_021c87b4);
    __register_global_object((void *) &data_021c87b4, (void *) &func_020530b0, (void *) &data_021c878c);
    __cxa_vec_ctor((void *) &data_021c87fc, 4, 20, (void *) &func_0205349c, (void *) &func_02053498);
    __register_global_object((void *) &data_021c87fc, (void *) &func_0205347c, (void *) &data_021c8774);
    data_021c874c.unk_00 = 0;
    data_021c874c.unk_02 = 0;
    data_021c8754.unk_00 = 0;
    data_021c8754.unk_02 = 0;
    p = (UnkStruct_020c52d8 *) &data_021c8758;
    p->unk_00 = 1;
    p->unk_02 = 0;
    data_021c875c.unk_00 = 0;
    data_021c875c.unk_02 = 0;
    data_021c8760.unk_00 = 0;
    data_021c8760.unk_02 = -1;
    data_021c876c.unk_00 = 0;
    data_021c876c.unk_02 = 0;
    data_021c8770.unk_00 = -1;
    data_021c8770.unk_02 = 0;
    data_021c8764.unk_00 = 0;
    data_021c8764.unk_02 = 0;
    data_021c8768.unk_00 = 0;
    data_021c8768.unk_02 = 1;
    data_021c87a4.unk_00 = 0;
    data_021c87a4.unk_02 = 0;
    data_021c87a8.unk_00 = 1;
    data_021c87a8.unk_02 = 0;
    data_021c87ac.unk_00 = 0;
    data_021c87ac.unk_02 = 1;
    data_021c87b0.unk_00 = 1;
    data_021c87b0.unk_02 = 1;
}
