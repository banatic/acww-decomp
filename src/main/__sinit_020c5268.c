/* __sinit_020c5268 @ 0x020c5268, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051820(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021c8230;
extern int func_02051810(void *);
extern unsigned char data_021c8198;
extern unsigned char data_021c828c;
extern unsigned char data_021c81a4;
extern unsigned char data_021c82e8;
extern unsigned char data_021c81b0;
extern unsigned char data_021c81d4;
extern unsigned char data_021c81c8;

void __sinit_020c5268(void)
{
    func_02051820((void *) &data_021c8230);
    __register_global_object((void *) ((void *) &data_021c8230), (((void *) func_02051810)),
                             (void *) ((void *) &data_021c8198));
    func_02051820((void *) &data_021c828c);
    __register_global_object((void *) ((void *) &data_021c828c), (((void *) func_02051810)),
                             (void *) ((void *) &data_021c81a4));
    func_02051820((void *) &data_021c82e8);
    __register_global_object((void *) ((void *) &data_021c82e8), (((void *) func_02051810)),
                             (void *) ((void *) &data_021c81b0));
    func_02051820((void *) &data_021c81d4);
    __register_global_object((void *) ((void *) &data_021c81d4), (((void *) func_02051810)),
                             (void *) ((void *) &data_021c81c8));
}
