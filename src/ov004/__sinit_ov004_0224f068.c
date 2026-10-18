/* __sinit_ov004_0224f068 @ 0x0224f068, 0xfc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

// Stand-in symbol names. FX_Mul written out as a 64-bit multiply with rounding.
typedef struct {
    long unk_00, unk_04, unk_08;
} UnkStruct_0224f068;

extern void func_0209d2b8(void *);
extern int func_ov004_0223ce74(void *);
extern int func_ov004_0223cf00(void *);
extern void *func_ov004_0223d2f8(void *);
extern int func_ov004_0223cd40(void *);
extern void *func_ov004_0223c7f4(void *);
extern void func_0209d2b4(void *arg0);
extern void func_ov004_0223ce70(void *object);
extern void func_ov004_0223cefc(void *object);
extern void *func_ov004_0223d2d4(void *);
extern void func_ov004_0223cd3c(void *object);
extern void *func_ov004_0223c7d8(void *);
extern void func_020012dc(void *arg0);
extern void __register_global_object(void *, void *destructor, void *);

extern char data_ov004_02259698, data_ov004_02259714, data_ov004_022595c4, data_ov004_022596b0, data_ov004_02259804,
    data_ov004_02259784;
extern char data_ov004_02259634, data_ov004_022595e0, data_ov004_022595ec, data_ov004_022595f8, data_ov004_02259604,
    data_ov004_02259610, data_ov004_02259670;
extern long data_020ca0e8;
extern long data_ov004_022595d8;
extern UnkStruct_0224f068 data_ov004_0225967c;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov004_0224f068(void)
{
    func_0209d2b8((void *) &data_ov004_02259698);
    __register_global_object((void *) &data_ov004_02259698, ((void *) &func_0209d2b4), (void *) &data_ov004_02259634);
    func_ov004_0223ce74((void *) &data_ov004_02259714);
    __register_global_object((void *) &data_ov004_02259714, ((void *) &func_ov004_0223ce70), (void *) &data_ov004_022595e0);
    func_ov004_0223cf00((void *) &data_ov004_022595c4);
    __register_global_object((void *) &data_ov004_022595c4, ((void *) &func_ov004_0223cefc), (void *) &data_ov004_022595ec);
    func_ov004_0223d2f8((void *) &data_ov004_022596b0);
    __register_global_object((void *) &data_ov004_022596b0, ((void *) &func_ov004_0223d2d4), (void *) &data_ov004_022595f8);
    func_ov004_0223cd40((void *) &data_ov004_02259804);
    __register_global_object((void *) &data_ov004_02259804, ((void *) &func_ov004_0223cd3c), (void *) &data_ov004_02259604);
    func_ov004_0223c7f4((void *) &data_ov004_02259784);
    __register_global_object((void *) &data_ov004_02259784, ((void *) &func_ov004_0223c7d8), (void *) &data_ov004_02259610);

    data_ov004_022595d8 = (long) ((((long long) data_020ca0e8 * (long long) data_020ca0e8) + 0x800) >> 12);
    data_ov004_0225967c.unk_00 = 0;
    data_ov004_0225967c.unk_04 = 0;
    data_ov004_0225967c.unk_08 = 0;
    __register_global_object((void *) &data_ov004_0225967c, ((void *) &func_020012dc), (void *) &data_ov004_02259670);
}

#pragma section INIT end
