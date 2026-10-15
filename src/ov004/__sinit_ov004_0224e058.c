/* __sinit_ov004_0224e058 @ 0x0224e058, 0x110 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;

extern Vec data_ov004_022572c4;
extern Vec data_ov004_022572d0;
extern Vec data_ov004_022572dc;
extern Vec data_ov004_022572e8;
extern Vec data_ov004_02257100;
extern Vec data_ov004_022572f4;
extern Vec data_ov004_02257300;
extern unsigned short data_ov004_02256fec;

extern int data_ov004_022570c4;
extern int data_ov004_022570d0;
extern int data_ov004_022570dc;
extern int data_ov004_022570e8;
extern int data_ov004_022570f4;
extern int data_ov004_0225710c;
extern int data_ov004_02257118;
extern int data_ov004_022570b8;

extern void func_020012dc(void *object);
extern void func_020051b0(void *object);
extern void __register_global_object(void *, void *destructor, void *);

void __sinit_ov004_0224e058(void)
{
    data_ov004_022572c4.x = 8192;
    data_ov004_022572c4.y = 0;
    data_ov004_022572c4.z = 8192;
    __register_global_object(&data_ov004_022572c4, ((void *) &func_020012dc), &data_ov004_022570c4);

    {
        Vec *p = (Vec *) &data_ov004_022572d0;
        p->x = 8192;
        p->y = 0;
        p->z = -8192;
        __register_global_object(p, ((void *) &func_020012dc), &data_ov004_022570d0);
    }

    data_ov004_022572dc.x = 4096;
    data_ov004_022572dc.y = 0;
    data_ov004_022572dc.z = 12288;
    __register_global_object(&data_ov004_022572dc, ((void *) &func_020012dc), &data_ov004_022570dc);

    {
        Vec *p = (Vec *) &data_ov004_022572e8;
        p->x = 4096;
        p->y = 0;
        p->z = -12288;
        __register_global_object(p, ((void *) &func_020012dc), &data_ov004_022570e8);
    }

    data_ov004_02257100.x = 0;
    data_ov004_02257100.y = 0;
    data_ov004_02257100.z = 0;
    __register_global_object(&data_ov004_02257100, ((void *) &func_020012dc), &data_ov004_022570f4);

    data_ov004_022572f4.x = -4096;
    data_ov004_022572f4.y = 0;
    data_ov004_022572f4.z = -4096;
    __register_global_object(&data_ov004_022572f4, ((void *) &func_020012dc), &data_ov004_0225710c);

    {
        Vec *p = (Vec *) &data_ov004_02257300;
        p->x = -4096;
        p->y = 0;
        p->z = 4096;
        __register_global_object(p, ((void *) &func_020012dc), &data_ov004_02257118);
    }

    data_ov004_02256fec = 0xfff1;
    __register_global_object(&data_ov004_02256fec, ((void *) &func_020051b0), &data_ov004_022570b8);
}
