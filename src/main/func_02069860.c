/* func_02069860 @ 0x02069860, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02069860 UnkStruct_02069860;
typedef struct {
    char pad_00[0x34];
    void (*unk_34)(UnkStruct_02069860 *, int, int);
} Vt;
struct UnkStruct_02069860 {
    Vt *vt;
};

extern void func_020a86a4(void *a, unsigned char *b1, unsigned char *b2, unsigned char *b3, int *w);
extern void func_0206b964(void *self, unsigned char *b);

void func_02069860(unsigned char *self)
{
    unsigned char b[4];
    int w;
    UnkStruct_02069860 *obj;
    int mode;
    int i;

    obj = *(UnkStruct_02069860 **) (*(char **) (self + 0x24) + 0x14a8);
    obj->vt->unk_34(obj, 8, 4);
    func_020a86a4(self + 0x38, &b[1], &b[2], &b[3], &w);
    mode = *(int *) (*(char **) (self + 0x24) + 0x1a74);
    i = 0;
    if (mode == 0) {
        goto join;
    }
    if (mode == 1) {
        i = 1;
        goto join;
    }
    if (mode == 2) {
        i = 2;
        goto join;
    }
    if (mode == 3) {
        i = 3;
    }
join:
    b[0] = (&b[1])[i];
    func_0206b964(self, b);
}
