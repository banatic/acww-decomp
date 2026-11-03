/* star_view_input_4: 10 functions, module ov128
 * mwccarm 1.2/base -O4,s
 * func_ov128_0229bea8 @ 0x0229bea8, 0x34 bytes, Thumb
 * func_ov128_0229be78 @ 0x0229be78, 0x30 bytes, Thumb
 * func_ov128_0229be5c @ 0x0229be5c, 0x1c bytes, Thumb
 * func_ov128_0229be44 @ 0x0229be44, 0x16 bytes, Thumb
 * func_ov128_0229be20 @ 0x0229be20, 0x24 bytes, Thumb
 * func_ov128_0229be00 @ 0x0229be00, 0x20 bytes, Thumb
 * func_ov128_0229bdd4 @ 0x0229bdd4, 0x2c bytes, Thumb
 * func_ov128_0229bd68 @ 0x0229bd68, 0x6c bytes, Thumb
 * func_ov128_0229bd38 @ 0x0229bd38, 0x30 bytes, Thumb
 * func_ov128_0229bd08 @ 0x0229bd08, 0x30 bytes, Thumb
 */

typedef struct {
    char pad_00[0x110];
    char unk_110;
    char pad_111[0x2d6c - 0x111];
    unsigned char unk_2D6C;
} Obj_t;

extern int func_0208e484(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov128_0229bbe4(void *);
extern void func_ov128_0229bc30(void *p);
extern int func_ov002_0220b168(void *);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov128_0229bce4(void *unused0);
extern void func_ov128_0229b7cc(void *, int);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);
extern void func_ov002_02208090(int param1, int param2);
extern void func_ov128_0229b8bc(int param1);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a374(void *p, int a);
extern int func_ov128_0229b7ec(int a, int b);
extern unsigned char data_ov128_0229c8c4[];
extern unsigned char data_ov128_0229c8c0[];

void func_ov128_0229bd68(Obj_t *obj);
int func_ov128_0229bd38(int a);
int func_ov128_0229bd08(int param1);

void func_ov128_0229bea8(void *r0)
{
    if (func_0208e484((char *) r0 + 0x110)) {
        if (func_ov128_0229b7ec((int) r0, 2)) {
            func_ov002_02208098((void *) (r0), 3);
            func_ov128_0229bbe4(r0);
        }
    }
}

void func_ov128_0229be78(unsigned char *param)
{
    if (func_0208e484(param + 0x110) != 0) {
        func_ov128_0229bc30(param);
        func_ov002_02208098((void *) (param), param[0x2d6a]);
    }
}

void func_ov128_0229be5c(void *param)
{
    if (func_ov002_0220b168((char *) param + 0x94) == 0) {
        func_ov002_022080a0((void *) (param), 1);
    }
}

void func_ov128_0229be44(void *p)
{
    func_ov128_0229bce4(p);
    func_ov002_02208098((void *) (p), 0);
}

void func_ov128_0229be20(void *param)
{
    func_ov128_0229b7cc(param, 2);
    func_ov002_02208098((void *) (param), 4);
    func_ov128_0229bd68((Obj_t *) param);
    func_ov002_02207fc0(param);
}

void func_ov128_0229be00(int r0)
{
    if (func_0206fe60() != 0) {
        func_ov128_0229be44((void *) r0);
    } else {
        func_ov128_0229be20((void *) r0);
    }
}

void func_ov128_0229bdd4(int param1)
{
    func_ov002_02208090(param1, 2);
    func_ov002_02208098((void *) (param1), 10);
    func_ov128_0229b7cc((void *) param1, 4);
    func_ov128_0229b8bc(param1);
    func_ov128_0229bce4((void *) param1);
}

void func_ov128_0229bd68(Obj_t *obj)
{
    int a = func_ov128_0229bd38((int) obj);
    int b = func_ov128_0229bd08((int) obj);
    func_ov002_0220a0b4(&obj->unk_110, a, b);
    if (func_ov128_0229b7ec((int) obj, 2)) {
        func_ov002_0220a374(&obj->unk_110, 1);
    } else {
        if (obj->unk_2D6C == 3) {
            func_ov002_0220a374(&obj->unk_110, 0xD);
        } else {
            func_ov002_0220a374(&obj->unk_110, 1);
        }
    }
    func_ov128_0229bc30((void *) obj);
}

int func_ov128_0229bd38(int a)
{
    int r4 = a;
    if (func_ov128_0229b7ec(r4, 2) != 0) {
        return *(int *) ((char *) r4 + 0x2d48);
    } else {
        return data_ov128_0229c8c4[*(unsigned char *) ((char *) r4 + 0x2d6c)];
    }
}

int func_ov128_0229bd08(int param1)
{
    int r4;
    unsigned char r1;
    unsigned char r0;

    r4 = param1;
    if (func_ov128_0229b7ec(r4, 2) != 0) {
        return *(int *) ((char *) r4 + 0x2d4c);
    }
    r1 = *(unsigned char *) ((char *) r4 + 0x2d6c);
    r0 = data_ov128_0229c8c0[r1];
    return r0;
}
