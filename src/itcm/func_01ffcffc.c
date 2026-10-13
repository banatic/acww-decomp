/* func_01ffcffc @ 0x01ffcffc, 0x2c bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcfc0(int *);

int func_01ffcffc(int *p)
{
    int v;

    v = p[1];
    if (v == 0) {
        v = func_01ffcfc0(p);
    }
    return v;
}
