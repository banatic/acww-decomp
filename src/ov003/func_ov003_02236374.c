/* func_ov003_02236374 @ 0x02236374, 0x14c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad[0x64];
    int unk_64;
} UnkStruct_02236374;

typedef struct {
    unsigned char sec;
    unsigned char min;
    unsigned char hour;
    unsigned char day;
    unsigned char mon;
    unsigned char year;
    unsigned short pad;
} DateTime;

typedef union {
    DateTime t;
    unsigned int w[2];
} DateTimeU;

typedef struct {
    int x, y, z, w;
} Vec4;
typedef struct {
    int x, y, z;
} Vec3;

extern UnkStruct_02236374 *data_020ccf94;

extern int func_02073dd4(UnkStruct_02236374 *p, int val);
extern int func_020b6598(void);
extern Vec4 *func_020b03f8(void);
extern void func_020b0518(Vec4 *p);
extern void func_0209e474(DateTime *d);
extern void func_0209e140(DateTime *d, int n);
extern int func_020b0594(char *base, unsigned int index, int *o1, int *o2, int *o3, unsigned char *o4, unsigned char *o5,
                         unsigned char *o6);
extern int func_020b6660(void);
extern int func_020b0568(char *base);
extern int func_ov003_02235d88(void *self, void *dst, void *ref, int f);
extern int func_02003348(int chan, int slot, void *arg, int d, void *self);

extern unsigned char data_021f3b56[];

void func_ov003_02236374(void *self)
{
    unsigned char yy;
    unsigned char mm;
    unsigned char dd;
    DateTimeU now;
    int o1;
    int o2;
    int o3;
    Vec3 a;
    Vec3 b;
    unsigned int i;
    Vec4 *p;
    Vec4 *q;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 || func_020b6598() == 0) {
        func_020b0518(func_020b03f8());
        return;
    }

    for (i = 0; i < 3; i++) {
        now.w[0] = 0;
        now.w[1] = 0;
        func_0209e474(&now.t);
        if (now.t.hour < 6) {
            func_0209e140(&now.t, 1);
        }
        if (func_020b0594((char *) data_021f3b56, i, &o1, &o2, &o3, &yy, &mm, &dd) == 0) {
            continue;
        }
        if (yy != now.t.year) {
            continue;
        }
        if (mm != now.t.mon) {
            continue;
        }
        if (dd != now.t.day) {
            continue;
        }
        func_020b0518(func_020b03f8());
        return;
    }

    if (func_020b6660() == 0) {
        return;
    }
    if (func_020b0568((char *) data_021f3b56) != 0) {
        return;
    }

    if (func_020b03f8()->x != 0) {
        p = func_020b03f8();
        a.x = p->x;
        a.y = p->y;
        a.z = p->z;
    } else {
        func_ov003_02235d88(self, &a, 0, 1);
    }

    if (func_020b03f8()[1].x != 0) {
        p = func_020b03f8();
        q = &p[1];
        b.x = q->x;
        b.y = q->y;
        b.z = q->z;
    } else {
        func_ov003_02235d88(self, &b, &a, 1);
    }

    if (func_02003348(0xbd, 0, &a, 0, self) != 0) {
        p = func_020b03f8();
        p->x = a.x;
        p->y = a.y;
        p->z = a.z;
    }
    if (func_02003348(0xbd, 1, &b, 0, self) != 0) {
        p = func_020b03f8();
        p[1].x = b.x;
        p[1].y = b.y;
        p[1].z = b.z;
    }
}
