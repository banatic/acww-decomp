/* func_ov003_02224384 @ 0x02224384, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223cf70;
int func_ov003_022243d0(void *a, int *p);
void func_ov003_02223680(void *base, void *a, int *p, void *c, int k);

void func_ov003_02224384(void *a, int *p, void *c)
{
    int t[2];
    int u[2];
    t[0] = p[0];
    t[1] = p[1];
    if (func_ov003_022243d0(a, t) != 0) {
        u[0] = p[0];
        u[1] = p[1];
        func_ov003_02223680((char *) data_ov003_0223cf70 + 0x4b20, a, u, c, 0);
    }
}
