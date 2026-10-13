/* func_02070c50 @ 0x02070c50, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MTX_Copy33To43_(int a, void *b);
extern int FX_MulFunc(int a, int b);
extern void MTX_Concat43(void *a, void *b, void *c);
extern int data_021cfe68;

void func_02070c50(int param0, int *a, int *b)
{
    int mtx[13];

    MTX_Copy33To43_(param0, mtx);
    if (b == 0) {
        mtx[9] = a[0];
        mtx[10] = a[1];
        mtx[11] = a[2];
    } else {
        mtx[9] = FX_MulFunc(a[0], b[0]);
        mtx[10] = FX_MulFunc(a[1], b[1]);
        mtx[11] = FX_MulFunc(a[2], b[2]);
    }
    MTX_Concat43(mtx, &data_021cfe68, &data_021cfe68);
}
