/* __sinit_020c5d3c @ 0x020c5d3c, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    long a, b;
} UnkStruct_020c5d3c;
extern void func_020817a8(void *);
extern void __register_global_object(void *, void *, void *);
extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void func_02078d68(void *);
extern void func_02078c78(void *);
extern void func_02078bb0(void *);
extern struct {
    UnkStruct_020c5d3c f0;
    UnkStruct_020c5d3c f8;
    UnkStruct_020c5d3c f10;
    UnkStruct_020c5d3c f18;
    UnkStruct_020c5d3c f20;
} data_021d1330;
extern struct {
    UnkStruct_020c5d3c f0;
} data_020e18b8;
extern struct {
    UnkStruct_020c5d3c f0;
} data_020e18a8;
extern struct {
    UnkStruct_020c5d3c f0;
} data_020e1898;
extern struct {
    UnkStruct_020c5d3c f0;
} data_020e18b0;
extern struct {
    UnkStruct_020c5d3c f0;
} data_020e18a0;
extern unsigned char data_021d1554;
extern void func_02081710(void);
extern unsigned char data_021d1280;
extern unsigned char data_021d13e4;
extern void func_020795c8(void);
extern void func_020795a8(void);
extern void func_02082528(void);
extern unsigned char data_021d1274;
extern unsigned char data_021d12dc;
extern void func_02078d64(void);
extern unsigned char data_021d128c;
extern unsigned char data_021d1310;
extern void func_02078c74(void);
extern unsigned char data_021d1250;
extern unsigned char data_021d12a4;
extern void func_02078bac(void);
extern unsigned char data_021d1268;

void __sinit_020c5d3c(void)
{
    func_020817a8((void *) &data_021d1554);
    __register_global_object((void *) &data_021d1554, (void *) &func_02081710, (void *) &data_021d1280);
    data_021d1330.f0 = data_020e18b8.f0;
    data_021d1330.f8 = data_020e18a8.f0;
    data_021d1330.f10 = data_020e1898.f0;
    data_021d1330.f18 = data_020e18b0.f0;
    data_021d1330.f20 = data_020e18a0.f0;
    __cxa_vec_ctor((void *) &data_021d13e4, 8, 44, (void *) &func_020795c8, (void *) &func_020795a8);
    __register_global_object((void *) &data_021d13e4, (void *) &func_02082528, (void *) &data_021d1274);
    func_02078d68((void *) &data_021d12dc);
    __register_global_object((void *) &data_021d12dc, (void *) &func_02078d64, (void *) &data_021d128c);
    func_02078c78((void *) &data_021d1310);
    __register_global_object((void *) &data_021d1310, (void *) &func_02078c74, (void *) &data_021d1250);
    func_02078bb0((void *) &data_021d12a4);
    __register_global_object((void *) &data_021d12a4, (void *) &func_02078bac, (void *) &data_021d1268);
}
