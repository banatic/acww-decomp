/* func_0206026c @ 0x0206026c, 0x1bc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0206026c UnkStruct_0206026c;
typedef struct ObjVtbl {
    int pad_00[23];
    int (*method5C)(UnkStruct_0206026c *, void *);
} ObjVtbl;

struct UnkStruct_0206026c {
    ObjVtbl *vtbl;
};

typedef struct Vec3 {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_0206026c_2 {
    int unk_00;
    int unk_04;
    Vec3 vec;
    int unk_14;
    int unk_18;
    Vec3 unk_1C;
    UnkStruct_0206026c *unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
} UnkStruct_0206026c_2;

typedef struct UnkStruct_0206026c_3 {
    int pad_00[12];
    int flag;
    int pad_34;
    int pad_38;
    int something;
} UnkStruct_0206026c_3;

extern void func_02034270(void *dst, void *src, int a, int b);
extern void func_0203423c(void *obj);
extern int func_0209129c(int value);
extern int func_020912d4(int kind, int *vec, int a, int b);
extern int func_0205fbc4(int *a, int *b, int *c, int *d, int e);
extern int func_ov003_0222a784(int value);

void func_0206026c(UnkStruct_0206026c_2 *self, int param)
{
    int old;
    int vec0[3];
    UnkStruct_0206026c_3 tmp;
    int vecA7[3];
    int vecB7[3];
    int vecA8[3];
    int vecB8[3];

    if (self->unk_34 != -1) {
        func_0209129c(self->unk_34);
        self->unk_34 = -1;
    }
    if (self->unk_28 == (UnkStruct_0206026c *) 0) {
        self->unk_04 = 0;
        goto end;
    }
    old = self->unk_04;
    self->unk_04 = param;
    self->unk_30 = 0;
    func_02034270(&tmp, &self->vec, 1, 1);

    switch (param) {
        case 1:
            if (self->unk_2C != 0 && func_ov003_0222a784(self->unk_2C) != 0) {
                self->unk_2C = 0;
            }
            break;
        case 7:
            if (self->unk_28->vtbl->method5C(self->unk_28, &self->unk_1C) == 0) {
                Vec3 *src = (Vec3 *) ((char *) self->unk_28 + 0x5c);
                self->unk_1C.x = src->x;
                self->unk_1C.y = src->y;
                self->unk_1C.z = src->z;
            }
            vecA7[0] = self->unk_1C.x;
            vecA7[1] = self->unk_1C.y;
            vecA7[2] = self->unk_1C.z;
            vecB7[0] = self->vec.x;
            vecB7[1] = self->vec.y;
            vecB7[2] = self->vec.z;
            func_0205fbc4(vecA7, vecB7, &self->unk_14, &self->unk_18, 1);
            if (tmp.flag != 0) {
                vec0[0] = self->vec.x;
                vec0[1] = self->vec.y;
                vec0[2] = self->vec.z;
                vec0[1] = tmp.something;
                func_020912d4(0xd, vec0, 0, 0);
            }
            break;
        case 8:
            if (self->unk_28->vtbl->method5C(self->unk_28, &self->unk_1C) == 0) {
                Vec3 *src = (Vec3 *) ((char *) self->unk_28 + 0x5c);
                self->unk_1C.x = src->x;
                self->unk_1C.y = src->y;
                self->unk_1C.z = src->z;
            }
            vecA8[0] = self->unk_1C.x;
            vecA8[1] = self->unk_1C.y;
            vecA8[2] = self->unk_1C.z;
            vecB8[0] = self->vec.x;
            vecB8[1] = self->vec.y;
            vecB8[2] = self->vec.z;
            func_0205fbc4(vecA8, vecB8, &self->unk_14, &self->unk_18, 2);
            break;
        case 5:
            if (tmp.flag != 0) {
                vec0[0] = self->vec.x;
                vec0[1] = self->vec.y;
                vec0[2] = self->vec.z;
                vec0[1] = tmp.something;
                func_020912d4(0x10, vec0, 0, 0);
            }
            break;
        case 4:
            if (old == 6) {
                if (tmp.flag != 0) {
                    vec0[0] = self->vec.x;
                    vec0[1] = self->vec.y;
                    vec0[2] = self->vec.z;
                    vec0[1] = tmp.something;
                    func_020912d4(0xf, vec0, 0, 0);
                }
            }
            break;
        case 6:
            if (tmp.flag != 0) {
                vec0[0] = self->vec.x;
                vec0[1] = self->vec.y;
                vec0[2] = self->vec.z;
                vec0[1] = tmp.something;
                self->unk_34 = func_020912d4(0x11, vec0, 0, 0);
            }
            break;
        default:
            break;
    }

    func_0203423c(&tmp);
end:
    return;
}
