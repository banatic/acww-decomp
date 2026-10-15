/* func_ov004_02234810 @ 0x02234810, 0x13c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209d238(void *, void *);
extern char data_ov004_02255f04[], data_ov004_02255f20[];
extern int func_02064328(char *, char *, ...);
extern int func_0209d0ac(void *, void *, char *);
extern short func_ov004_02239474(int, int);
extern int func_0209d088(void *);
extern int func_02055f2c(void *, int, int);
extern int func_0209d324(void *);
extern void func_ov004_02235374(char *, int);
extern void *NNS_G3dGetJntAnmSet(void *);
extern int func_02107b44(void *, int);
extern int func_02055140(void *, int);
extern void func_02055060(void *, int, int, int, unsigned short, unsigned short);
extern void func_02055050(void *);
extern int func_02055478(void *, int);
extern void func_ov004_022347b8(char *, char **);
typedef void (*Method)(char *);
int func_ov004_02234810(char *self, char **slot, int which)
{
    int result, id;
    void *resource, *animation, *model;
    int value, track, group;
    char name[24];
    result = 0;
    id = *(int *) (*slot + 0x15c);
    resource = func_0209d238(self + 0x7f8, *slot + 0x166);
    animation = *slot + 0x168;
    group = id / 10 + 10;
    if (id < 10) {
        func_02064328(name, data_ov004_02255f04, group, id);
    } else {
        func_02064328(name, data_ov004_02255f20, group, id);
    }
    if (func_0209d0ac(animation, resource, name)) {
        *(short *) (*slot + 0x1c0) = func_ov004_02239474(0x168, 0);
        *(short *) (*slot + 0x1c2) = *(short *) (*slot + 0x1c0);
        (*(Method **) *slot)[0](*slot);
        model = *slot + 0x64;
        func_02055f2c(model, func_0209d088(animation), 0);
        value = func_0209d324(resource);
        if (!*(void **) (*slot + 0x54)) {
            func_ov004_02235374(self, which);
            return 0;
        }
        track = func_02107b44(NNS_G3dGetJntAnmSet(*(void **) (*slot + 0x54)), 0);
        if (func_02055140(model, value)) {
            func_02055060(model, track, 0, 0x1000, 1, 0);
            func_02055050(model);
            func_02055478(model, func_0209d324(resource));
            *(int *) (*slot + 0x160) = 2;
            (*slot)[0x1e8] = *(int *) (*slot + 0x15c);
            func_ov004_022347b8(self, slot);
            result = 1;
        }
    }
    return result;
}
