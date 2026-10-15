/* __sinit_020c64e8 @ 0x020c64e8, 0x1f8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021dc7a8[];
extern char data_021dc7aa[];
extern char data_021dc7bc[];
extern char data_021dc764[];
extern void func_020642fc(void *);
extern void *func_02098904(void *);
extern void *func_0207d080(void *);
extern void *func_0204ead0(void *);
extern void func_020871c8(void *);
extern void func_02087168(void *);
extern void *func_02061144(void *);
extern void *func_02072b38(void *);
extern void *func_020901d8(void *);
extern int func_020781fc(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_020980a4(void *);
extern int func_020980c4(void *);
extern int func_02098024(void *);
extern int func_020b19e4(void *);
extern void func_0203a68c(void *);
extern void func_0203a690(void *);
extern int func_02088274(void *);
extern void *func_020b3830(void *);
extern unsigned int func_02097f28(void *);
extern void *func_02090030(void *);
extern void *func_02071490(void *);
extern void *func_020afc2c(void *);
extern void func_02041298(void *);
extern void func_0204cf10(void *);
extern void func_0203a670(void *);
extern void func_0203a504(void *);
extern void *func_020868c0(void *);
extern void *func_0208725c(void *);
extern void func_02087850(void *);
extern void func_020c181c(void *);
extern void *func_020ae410(void *);
extern int func_020aea5c(void *);
extern void *func_020b0838(void *);
extern void func_0205bfc0(void *);
extern void *func_02063ef0(void *);
extern void func_0209fae8(void *);
extern int func_02088460(void *);
extern void func_0209fb70(void *);
extern void __register_global_object(void *, void *, void *);
extern void *func_0209f1a8(void *);

void __sinit_020c64e8(void)
{
    int b = (int) data_021dc7a8;
    func_020642fc(data_021dc7aa);
    func_02098904(data_021dc7bc);
    func_0207d080((void *) (b + 0x9284));
    func_0204ead0((void *) (b + 0xd304));
    func_020871c8((void *) (b + 0xf52a));
    func_02087168((void *) (b + 0xf52b));
    func_02061144((void *) (b + 0xf52c));
    func_02072b38((void *) (b + 0x10ad0));
    func_020901d8((void *) (b + 0x11c70));
    func_020781fc((void *) (b + 0x125c0));
    __cxa_vec_ctor((void *) ((void *) (b + 0x13144)), 4, 0xa04, (((void (*)(void *)) func_020980c4)),
                   (((void (*)(void *)) func_020980a4)));
    func_02098024((void *) (b + 0x15954));
    func_020b19e4((void *) (b + 0x1635c));
    __cxa_vec_ctor((void *) ((void *) (b + 0x16800)), 4, 0xb4, (void (*)(void *)) func_0203a690,
                   (void (*)(void *)) func_0203a68c);
    func_02088274((void *) (b + 0x16ad0));
    func_020b3830((void *) (b + 0x16d08));
    func_02097f28((void *) (b + 0x16f44));
    func_02090030((void *) (b + 0x1704c));
    func_02071490((void *) (b + 0x17150));
    func_020afc2c((void *) (b + 0x171b4));
    func_02041298((void *) (b + 0x17218));
    func_0204cf10((void *) (b + 0x17254));
    func_0203a670((void *) (b + 0x172c0));
    func_0203a504((void *) (b + 0x172de));
    func_020868c0((void *) (b + 0x172fc));
    func_0208725c((void *) (b + 0x17344));
    func_02087850((void *) (b + 0x17364));
    func_020c181c((void *) (b + 0x1737e));
    func_020ae410((void *) (b + 0x17388));
    func_020aea5c((void *) (b + 0x1739c));
    func_020b0838((void *) (b + 0x173ae));
    func_0205bfc0((void *) (b + 0x173c8));
    func_02063ef0((void *) (b + 0x173d4));
    func_0209fae8((void *) (b + 0x173dd));
    func_02088460((void *) (b + 0x173e2));
    func_0209fb70((void *) (b + 0x173f8));
    __register_global_object((void *) (data_021dc7a8), (((void *) func_0209f1a8)), (void *) (data_021dc764));
}
