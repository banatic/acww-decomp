/* __sinit_ov004_0224de7c @ 0x0224de7c, 0x1dc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern unsigned char data_ov004_02256c4c[4];
extern unsigned char data_ov004_02256c6c[4];
extern unsigned char data_ov004_02256c7c[4];
extern unsigned char data_ov004_02256c48[4];
extern unsigned char data_ov004_02256c5c[4];
extern unsigned char data_ov004_02256c58[4];
extern Vec data_ov004_02256ecc;
extern Vec data_ov004_02256ed8;
extern Vec data_ov004_02256ee4;
extern Vec data_ov004_02256ef0;
extern Vec data_ov004_02256efc;
extern Vec data_ov004_02256f08;
extern Vec data_ov004_02256f14;
extern Vec data_ov004_02256f20;
extern Vec data_ov004_02256f2c;
extern Vec data_ov004_02256f38;
extern Vec data_ov004_02256f44;
extern Vec data_ov004_02256f50;
extern int data_ov004_02256cfc;
extern int data_ov004_02256d20;
extern int data_ov004_02256d50;
extern int data_ov004_02256d2c;
extern int data_ov004_02256d38;
extern int data_ov004_02256d44;
extern int data_ov004_02256ce4;
extern int data_ov004_02256cf0;
extern int data_ov004_02256d74;
extern int data_ov004_02256d80;
extern int data_ov004_02256d8c;
extern int data_ov004_02256d98;
extern void func_020012dc(void *object);
extern void __register_global_object(Vec *, void *destructor, void *);

void __sinit_ov004_0224de7c(void)
{
    data_ov004_02256c4c[0] = 31;
    data_ov004_02256c4c[1] = 20;
    data_ov004_02256c4c[2] = 20;
    data_ov004_02256c4c[3] = 31;
    data_ov004_02256c6c[0] = 20;
    data_ov004_02256c6c[1] = 20;
    data_ov004_02256c6c[2] = 31;
    data_ov004_02256c6c[3] = 31;
    data_ov004_02256c7c[0] = 31;
    data_ov004_02256c7c[1] = 31;
    data_ov004_02256c7c[2] = 20;
    data_ov004_02256c7c[3] = 31;
    data_ov004_02256c48[0] = 20;
    data_ov004_02256c48[1] = 31;
    data_ov004_02256c48[2] = 20;
    data_ov004_02256c48[3] = 31;
    data_ov004_02256c5c[0] = 20;
    data_ov004_02256c5c[1] = 31;
    data_ov004_02256c5c[2] = 31;
    data_ov004_02256c5c[3] = 31;
    data_ov004_02256c58[0] = 20;
    data_ov004_02256c58[1] = 24;
    data_ov004_02256c58[2] = 24;
    data_ov004_02256c58[3] = 31;
    data_ov004_02256ecc.x = -4096;
    data_ov004_02256ecc.y = 0;
    data_ov004_02256ecc.z = -4096;
    __register_global_object(&data_ov004_02256ecc, ((void *) &func_020012dc), &data_ov004_02256cfc);
    {
        Vec *p = (Vec *) &data_ov004_02256ed8;
        p->x = -4096;
        p->y = 0;
        p->z = 4096;
        __register_global_object(p, ((void *) &func_020012dc), &data_ov004_02256d20);
    }
    {
        Vec *p = (Vec *) &data_ov004_02256ee4;
        p->x = 4096;
        p->y = 0;
        p->z = 4096;
        __register_global_object(p, ((void *) &func_020012dc), &data_ov004_02256d50);
    }
    {
        Vec *p = (Vec *) &data_ov004_02256ef0;
        p->x = 4096;
        p->y = 0;
        p->z = -4096;
        __register_global_object(p, ((void *) &func_020012dc), &data_ov004_02256d2c);
    }
    data_ov004_02256efc.x = -4096;
    data_ov004_02256efc.y = 0;
    data_ov004_02256efc.z = -4096;
    __register_global_object(&data_ov004_02256efc, ((void *) &func_020012dc), &data_ov004_02256d38);
    {
        Vec *p = (Vec *) &data_ov004_02256f08;
        p->x = -4096;
        p->y = 0;
        p->z = 4096;
        __register_global_object(p, ((void *) &func_020012dc), &data_ov004_02256d44);
    }
    {
        Vec *p = (Vec *) &data_ov004_02256f14;
        p->x = 12288;
        p->y = 0;
        p->z = 4096;
        __register_global_object(p, ((void *) &func_020012dc), &data_ov004_02256ce4);
    }
    {
        Vec *p = (Vec *) &data_ov004_02256f20;
        p->x = 12288;
        p->y = 0;
        p->z = -4096;
        __register_global_object(p, ((void *) &func_020012dc), &data_ov004_02256cf0);
    }
    data_ov004_02256f2c.x = -8192;
    data_ov004_02256f2c.y = 0;
    data_ov004_02256f2c.z = -8192;
    __register_global_object(&data_ov004_02256f2c, ((void *) &func_020012dc), &data_ov004_02256d74);
    {
        Vec *p = (Vec *) &data_ov004_02256f38;
        p->x = -8192;
        p->y = 0;
        p->z = 8192;
        __register_global_object(p, ((void *) &func_020012dc), &data_ov004_02256d80);
    }
    {
        Vec *p = (Vec *) &data_ov004_02256f44;
        p->x = 8192;
        p->y = 0;
        p->z = 8192;
        __register_global_object(p, ((void *) &func_020012dc), &data_ov004_02256d8c);
    }
    {
        Vec *p = (Vec *) &data_ov004_02256f50;
        p->x = 8192;
        p->y = 0;
        p->z = -8192;
        __register_global_object(p, ((void *) &func_020012dc), &data_ov004_02256d98);
    }
}
