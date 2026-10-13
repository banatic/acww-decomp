/* func_ov076_02278f5c @ 0x02278f5c, 0x4c bytes, Thumb, module ov076
 * mwccarm 1.2/base -O1,s
 */

struct Pair {
    int a;
    int b;
};
extern int data_ov076_02279880;
extern struct Pair data_ov076_02279884[];
extern struct Pair data_ov076_02279688;

void func_ov076_02278f5c(void *obj, int idx)
{
    struct Pair *p;
    struct Pair *t;
    int off;
    int va;
    int vb;
    if ((data_ov076_02279880 & 1) == 0) {
        data_ov076_02279884[0] = data_ov076_02279688;
        data_ov076_02279880 |= 1;
    }
    off = idx * 8;
    t = data_ov076_02279884;
    p = (struct Pair *) ((char *) t + off);
    va = p->a;
    vb = p->b;
    ((int *) obj)[47] = va;
    ((int *) obj)[48] = vb;
}
