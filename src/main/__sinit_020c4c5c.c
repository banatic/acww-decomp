/* __sinit_020c4c5c @ 0x020c4c5c, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __register_global_object(void *, void *, void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern struct {
    unsigned short f0;
} data_021c5174;
extern void func_020051b0(void *);
extern unsigned char data_021c5178;
extern unsigned char data_021c519c;
extern void func_02034ce0(void *);
extern void func_02034cc0(void);
extern unsigned char data_021c5184;
extern unsigned char data_021c5204;
extern void func_02034ca0(void);
extern unsigned char data_021c5190;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c4c5c(void)
{
    data_021c5174.f0 = 65521;
    __register_global_object((void *) ((void *) &data_021c5174), (((void *) func_020051b0)),
                             (void *) ((void *) &data_021c5178));
    __cxa_vec_ctor((void *) ((void *) &data_021c519c), 51, 2, (void (*)(void *)) func_02034ce0,
                   (void (*)(void *)) func_020051b0);
    __register_global_object(0, (((void *) func_02034cc0)), (void *) &data_021c5184);
    __cxa_vec_ctor((void *) ((void *) &data_021c5204), 51, 2, (void (*)(void *)) func_02034ce0,
                   (void (*)(void *)) func_020051b0);
    __register_global_object(0, (((void *) func_02034ca0)), (void *) &data_021c5190);
}

#pragma section INIT end
