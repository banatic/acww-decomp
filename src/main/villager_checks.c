/* villager_checks: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207dd84 @ 0x0207dd84, 0x4c bytes, Thumb
 * func_0207dd60 @ 0x0207dd60, 0x24 bytes, Thumb
 * func_0207dd1c @ 0x0207dd1c, 0x44 bytes, Thumb
 */

typedef struct {
    char pad_00[0x160];
    signed char unk_160;
} UnkStruct_0207dd60;

extern int func_02079350(void);
extern int func_0208150c(int);
extern int func_0207cf14(int *, int);
extern int func_02003704(int);
extern unsigned char data_021e5a2c[];

int func_0207dd84(int a)
{
    int r4 = *(signed char *) ((char *) func_02079350() + 0x160);
    int r1 = func_0208150c(a);
    int r6 = func_0207cf14(((int *) data_021e5a2c), r1);
    int cond1 = func_02003704(func_0208150c(a));
    if (cond1 != 0 && r4 != -1 && r6 == r4) {
        return 1;
    } else {
        return 0;
    }
}

void func_0207dd60(int argument0)
{
    void *p;
    UnkStruct_0207dd60 *q;
    p = (void *) func_0207dd84((int) argument0);
    if (p) {
        q = (UnkStruct_0207dd60 *) func_02079350();
        q->unk_160 = -1;
    }
}

int func_0207dd1c(int param)
{
    int r4;
    int r6;
    int r0;
    int r1;
    int r5 = param;
    r0 = func_02079350();
    r4 = ((signed char *) r0)[0x161];
    r0 = func_0208150c(r5);
    r1 = r0;
    r0 = func_0207cf14((int *) ((unsigned int) data_021e5a2c), r1);
    r6 = r0;
    r0 = func_0208150c(r5);
    r0 = func_02003704(r0);
    if (r0 != 0) {
        if (r6 == r4) {
            return 1;
        }
    }
    return 0;
}
