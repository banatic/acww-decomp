/* func_0204b3d0 @ 0x0204b3d0, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b544(void *p);
extern int func_0204b4c4(void *p);
extern int func_0204b430(void *p);
extern int func_0204b42c(void *p);

int func_0204b3d0(void *p)
{
    int result = 0;

    if (func_0204b544(p) != 0 || func_0204b4c4(p) != 0 || func_0204b430(p) != 0) {
        result = 1;
    } else {
        int v = func_0204b42c(p);

        switch (v) {
            case 0x1a:
            case 0x1d:
            case 0x1e:
            case 0x88:
            case 0xa4:
                result = 1;
                break;
        }
    }

    return result;
}
