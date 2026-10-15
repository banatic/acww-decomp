/* __sinit_020c4af0 @ 0x020c4af0, 0xec bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} Three;
extern void *FX_MulFunc(int, int);
extern void __register_global_object(void *, void *, void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_02033894(void *);
extern void *func_02033c48(void *);
extern void *func_02032f94(void *);
extern void func_0203243c(void *);
extern void func_020326c0(void *);
extern void *func_020343f4(void *);
extern void func_020346fc(void *);
extern void *data_021c30d0;
extern Three data_021c317c;
extern void func_020012dc(void *);
extern unsigned char data_021c3170;
extern Three data_021c31a0;
extern unsigned char data_021c3194;
extern unsigned char data_021c31e8;
extern unsigned char data_021c31ec;
extern void *func_02034804(void *);
extern int func_02034824(void *);
extern unsigned char data_021c3bac;
extern void *func_02034790(void *);
extern unsigned char data_021c31b8;

void __sinit_020c4af0(void)
{
    void *p;
    data_021c30d0 = FX_MulFunc(0x20000, 0x800);
    data_021c317c.unk_00 = 0;
    data_021c317c.unk_04 = 0x1000;
    data_021c317c.unk_08 = 0;
    __register_global_object((void *) ((void *) (&data_021c317c)), (((void *) func_020012dc)),
                             (void *) ((void *) (&data_021c3170)));
    data_021c31a0.unk_00 = 0x1000;
    data_021c31a0.unk_04 = 0x1000;
    data_021c31a0.unk_08 = 0x1000;
    __register_global_object((void *) ((void *) (&data_021c31a0)), (((void *) func_020012dc)),
                             (void *) ((void *) (&data_021c3194)));
    p = (void *) (&data_021c31e8);
    __cxa_vec_ctor((void *) ((void *) (&data_021c31ec)), 8, 0x138, (((void (*)(void *)) func_02034824)),
                   (((void (*)(void *)) func_02034804)));
    func_02033894((void *) (&data_021c3bac));
    func_02033c48((void *) (((char *) p) + 0xe48));
    func_02032f94((void *) (((char *) p) + 0x184c));
    func_0203243c((void *) (((char *) p) + 0x1a90));
    func_020326c0((void *) (((char *) p) + 0x1a91));
    func_020343f4((void *) (((char *) p) + 0x1a94));
    func_020346fc((void *) (((char *) p) + 0x1f3c));
    __register_global_object((void *) ((void *) (&data_021c31e8)), (((void *) func_02034790)),
                             (void *) ((void *) (&data_021c31b8)));
}
