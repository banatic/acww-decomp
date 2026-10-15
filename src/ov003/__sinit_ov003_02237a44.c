/* __sinit_ov003_02237a44 @ 0x02237a44, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221fe94(void *);
extern void __register_global_object(void *object, void *destructor, void *node);
extern int func_ov003_02220110(void *);
extern int func_ov003_0221ff9c(void *);
extern unsigned char data_ov003_0223ce58;
extern void func_ov003_0221fe90(void);
extern unsigned char data_ov003_0223ce5c;
extern unsigned char data_ov003_0223cea0;
extern void func_ov003_0222010c(void);
extern unsigned char data_ov003_0223ce68;
extern unsigned char data_ov003_0223ce80;
extern void func_ov003_0221ff98(void);
extern unsigned char data_ov003_0223ce74;

#define DestroyGlobal_ov003_0221fe90 ((void *) &func_ov003_0221fe90)
#define DestroyGlobal_ov003_0222010c ((void *) &func_ov003_0222010c)
#define DestroyGlobal_ov003_0221ff98 ((void *) &func_ov003_0221ff98)

void __sinit_ov003_02237a44(void)
{
    func_ov003_0221fe94((void *) &data_ov003_0223ce58);
    __register_global_object((void *) &data_ov003_0223ce58, DestroyGlobal_ov003_0221fe90, (void *) &data_ov003_0223ce5c);
    func_ov003_02220110((void *) &data_ov003_0223cea0);
    __register_global_object((void *) &data_ov003_0223cea0, DestroyGlobal_ov003_0222010c, (void *) &data_ov003_0223ce68);
    func_ov003_0221ff9c((void *) &data_ov003_0223ce80);
    __register_global_object((void *) &data_ov003_0223ce80, DestroyGlobal_ov003_0221ff98, (void *) &data_ov003_0223ce74);
}

#undef DestroyGlobal_ov003_0221fe90
#undef DestroyGlobal_ov003_0222010c
#undef DestroyGlobal_ov003_0221ff98
