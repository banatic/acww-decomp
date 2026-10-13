/* func_0207af90 @ 0x0207af90, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x161];
    unsigned char unk_161;
} Res;

extern int func_0208150c(char *p);
extern int func_02003704(int x);
extern int func_0207f270(char *p);
extern int func_020794d8(int x);
extern int func_0207cc54(int a, int b, int c);
extern int func_0207f150(char *p);
extern int func_0207b3dc(char *base);
extern Res *func_02079350(void);

void func_0207af90(char *base)
{
    int ret;
    int cnt;
    char *p;
    unsigned char mask;
    int i;
    int v;

    p = base;
    mask = 0;
    cnt = 0;
    ret = 0;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(p))) {
            if (func_020794d8(func_0207f270(p)) == 0) {
                mask |= 1 << i;
                cnt++;
            }
        }
        p += 0x7ec;
    }
    v = func_0207cc54(mask, cnt, 8);
    if (v != -1) {
        ret = (unsigned char) v;
    } else {
        mask = 0;
        cnt = 0;
        p = base;
        for (i = 0; i < 8; i++) {
            if (func_02003704(func_0208150c(p))) {
                if (func_0207f150(p) == 3) {
                    if (i != func_0207b3dc(base)) {
                        mask |= 1 << i;
                        cnt++;
                    }
                }
            }
            p += 0x7ec;
        }
        v = func_0207cc54(mask, cnt, 8);
        if (v != -1) {
            ret = (unsigned char) v;
        }
    }
    func_02079350()->unk_161 = ret;
}
