/* func_02069794 @ 0x02069794, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02069794 UnkStruct_02069794;
typedef struct {
    char pad_00[0x34];
    void (*unk_34)(UnkStruct_02069794 *, int, int);
} Vt;
struct UnkStruct_02069794 {
    Vt *vt;
};

extern int data_021dc7a8;

extern void func_020a86a4(void *a, unsigned char *b1, unsigned char *b2, unsigned char *b3, int *w);
extern int func_02098880(void *p);
extern void func_0206b964(void *self, unsigned char *b);

void func_02069794(unsigned char *self)
{
    unsigned char b[4];
    int w;
    UnkStruct_02069794 *obj;
    int t;
    int i;

    obj = *(UnkStruct_02069794 **) (*(char **) (self + 0x24) + 0x14a8);
    obj->vt->unk_34(obj, 10, 4);
    func_020a86a4(self + 0x38, &b[1], &b[2], &b[3], &w);
    if ((int) &data_021dc7a8 != 0) {
        t = func_02098880((void *) ((int) &data_021dc7a8 + 0x14));
    } else {
        t = 0;
    }
    i = t - 1;
    if (i < 0) {
        i = 0;
    } else if (i > 3) {
        i = 3;
    }
    b[0] = (&b[1])[i];
    func_0206b964(self, b);
}
