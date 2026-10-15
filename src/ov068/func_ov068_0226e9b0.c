/* func_ov068_0226e9b0 @ 0x0226e9b0, 0xfc bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov068_0227861c;
extern unsigned short data_ov068_02278620[4];

extern void func_020051b0(void *object);
extern void __register_global_object(void *object, void *destructor, void *node);
extern int func_0202edc8(void *);
extern int func_020af028(int);
extern void func_0201c400(void *, unsigned short *);
extern void func_0201c280(void *, void *);
extern void func_ov068_0226e598(void *, void *);
extern void func_0201af28(void *, int, int, int, int);

extern unsigned char data_ov068_02278628[];
extern unsigned char data_ov068_02278634[];
extern unsigned char data_ov068_02278640[];
extern unsigned char data_ov068_0227864c[];

extern unsigned char data_021f395c[];

#define DestroyGlobal_020051b0 ((void *) &func_020051b0)

int func_ov068_0226e9b0(void *arg)
{
    int idx;

    if ((data_ov068_0227861c & 1) == 0) {
        data_ov068_02278620[0] = 0xd019;
        __register_global_object(&data_ov068_02278620[0], DestroyGlobal_020051b0, (void *) data_ov068_0227864c);

        data_ov068_02278620[1] = 0xd01a;
        __register_global_object(&data_ov068_02278620[1], DestroyGlobal_020051b0, (void *) data_ov068_02278640);

        data_ov068_02278620[2] = 0xd01b;
        __register_global_object(&data_ov068_02278620[2], DestroyGlobal_020051b0, (void *) data_ov068_02278628);

        data_ov068_02278620[3] = 0xd01c;
        __register_global_object(&data_ov068_02278620[3], DestroyGlobal_020051b0, (void *) data_ov068_02278634);

        data_ov068_0227861c |= 1;
    }

    if (func_0202edc8(arg) == 0) {
        return 0;
    }

    idx = func_020af028((unsigned int) data_021f395c);
    func_0201c400(arg, &data_ov068_02278620[idx]);

    func_0201c280(arg, (void *) ((char *) arg + 0x658));
    func_ov068_0226e598((void *) ((char *) arg + 0x658), arg);
    func_0201af28((void *) ((char *) arg + 0x350), 2, 0x399, 0x133, 0x199);

    return 1;
}

#undef DestroyGlobal_020051b0
