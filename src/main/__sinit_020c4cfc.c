/* __sinit_020c4cfc @ 0x020c4cfc, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02038acc(void *);
extern void __register_global_object(void *, void *, void *);
extern int func_02038d30(void *);
extern void *func_02038ccc(void *);
extern unsigned char data_021c5c4c;
extern void *func_02038a90(void *);
extern unsigned char data_021c5940;
extern unsigned char data_021c5a24;
extern void *func_02038d18(void *);
extern unsigned char data_021c594c;
extern unsigned char data_021c59d0;
extern void *func_02038cb4(void *);
extern unsigned char data_021c5958;
extern unsigned char data_021c5b38;
extern unsigned char data_021c5964;

void __sinit_020c4cfc(void)
{
    func_02038acc((void *) &data_021c5c4c);
    __register_global_object((void *) ((void *) &data_021c5c4c), (((void *) func_02038a90)),
                             (void *) ((void *) &data_021c5940));
    func_02038d30((void *) &data_021c5a24);
    __register_global_object((void *) ((void *) &data_021c5a24), (((void *) func_02038d18)),
                             (void *) ((void *) &data_021c594c));
    func_02038ccc((void *) &data_021c59d0);
    __register_global_object((void *) ((void *) &data_021c59d0), (((void *) func_02038cb4)),
                             (void *) ((void *) &data_021c5958));
    func_02038d30((void *) &data_021c5b38);
    __register_global_object((void *) ((void *) &data_021c5b38), (((void *) func_02038d18)),
                             (void *) ((void *) &data_021c5964));
}
