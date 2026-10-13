/* __sinit_020c5788 @ 0x020c5788, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *, int, int);
extern void __register_global_object(void *, void *, void *);
extern void MIi_CpuClearFast(int, void *, int);

extern unsigned char data_021c9854;
extern void func_0205bfcc(void);
extern unsigned char data_021c968c;
extern unsigned char data_021c9774;
extern void func_0205bfc8(void);
extern unsigned char data_021c96c8;
extern int data_021c997c[74];
extern unsigned char data_021c9a7c;
extern void func_0205bfc4(void);
extern unsigned char data_021c96a4;

void __sinit_020c5788(void)
{
    unsigned int i;
    MI_CpuFill8((void *) &data_021c9854, 0, 0x128);
    __register_global_object((void *) &data_021c9854, (void *) &func_0205bfcc, (void *) &data_021c968c);
    {
        volatile int z = 0;
        MIi_CpuClearFast(z, (void *) &data_021c9774, 0xe0);
    }
    __register_global_object((void *) &data_021c9774, (void *) &func_0205bfc8, (void *) &data_021c96c8);
    for (i = 0; i < 74; i++) {
        data_021c997c[i] = 0;
    }
    *(int *) ((char *) &data_021c9a7c + 0x28) = 0;
    __register_global_object((void *) data_021c997c, (void *) &func_0205bfc4, (void *) &data_021c96a4);
}
