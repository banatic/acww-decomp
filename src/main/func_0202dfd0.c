/* func_0202dfd0 @ 0x0202dfd0, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02082e90(char *);
extern void func_0205d3d4(void *, void *, int, int, int);
extern void *func_02081500(int);
extern void func_0205d36c(void *, void *);
extern int func_0205d25c(void *);
extern int func_0203cfa8(unsigned int *);

typedef struct {
    unsigned short val;
} UnkStruct_0202dfd0;

typedef struct {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0202dfd0_2;

int func_0202dfd0(char *a, UnkStruct_0202dfd0_2 *b, UnkStruct_0202dfd0 *c)
{
    void *p;
    int flag;
    int v;
    int result;

    p = func_02082e90(a + 0x2c);
    result = 0;
    if (p != 0) {
        flag = result;
        if (c->val >= 0x11a8 && c->val <= 0x12a7) {
            flag = 1;
        }
        if (flag == 1) {
            func_0205d3d4(p, c, 0, 1, 1);
        } else {
            if (b->unk_830 != 0) {
                func_0205d36c(p, func_02081500(b->unk_830));
            } else {
                func_0205d3d4(p, c, 0, 1, 1);
            }
        }
        v = func_0205d25c(p);
        if (v != 0) {
            result = func_0203cfa8((unsigned int *) v);
        }
    }
    return result;
}
