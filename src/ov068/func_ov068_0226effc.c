/* func_ov068_0226effc @ 0x0226effc, 0xe4 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O1,s
 */

extern void *data_021c80bc;

struct Vec3 {
    int x;
    int y;
    int z;
};

extern void func_0204f818(int *px, int *pz, struct Vec3 *p);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern unsigned short func_0204bb14(int k);
extern void func_0204f538(void *ctx, unsigned short *h, int x, int z, int m);
extern void func_ov003_0221a484(unsigned short *p);
extern void func_ov003_0221a35c(void *self, int k);

struct UnkStruct_0226effc {
    char pad_00[0x5c];
    struct Vec3 pos;
    char pad_68[0x204];
    int unk_26C;
    int unk_270;
    char pad_274[0xa0];
    int unk_314;
    int unk_318;
    char pad_31C[0x5c];
    unsigned short f378_lo2 : 2;
    unsigned short f378_hi : 14;
    unsigned short pad_37A;
    int unk_37C;
    int unk_380;
    int unk_384;
    char pad_388[0x11];
    unsigned char unk_399;
    unsigned short unk_39A;
};

void func_ov068_0226effc(struct UnkStruct_0226effc *self)
{
    void *ctx;
    unsigned short *o;
    unsigned short h;
    int x;
    int z;
    int cx;
    int cz;
    struct Vec3 *p;

    self->unk_270 = self->unk_26C;
    p = &self->pos;
    self->pos.x = self->pos.x + self->unk_314;
    self->pos.y = 0;
    self->pos.z = self->pos.z + self->unk_318;
    if (self->unk_399++ < 0x10) {
        return;
    }
    self->pos.x = self->unk_37C;
    self->pos.y = self->unk_380;
    self->pos.z = self->unk_384;
    ctx = data_021c80bc;
    if (ctx != 0) {
        func_0204f818(&x, &z, p);
        {
            int xx = x, zz = z;
            cx = xx >> 4;
            cz = zz >> 4;
            o = func_0204f5e0(ctx, cx, cz, xx - (cx << 4), zz - (cz << 4), 0);
        }
        if (o != 0) {
            self->unk_39A = *o;
        }
        h = func_0204bb14(self->f378_lo2);
        func_0204f538(ctx, &h, x, z, 0);
    }
    func_ov003_0221a484(&self->unk_39A);
    func_ov003_0221a35c(self, 9);
}
