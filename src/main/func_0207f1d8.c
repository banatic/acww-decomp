/* func_0207f1d8 @ 0x0207f1d8, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0207f1d8 {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0207f1d8;

extern UnkStruct_0207f1d8 *data_020ccf94;

extern void func_0208150c(void *);
extern int func_02003704(void);
extern int func_0207f270(void *);
extern int func_02073dd4(UnkStruct_0207f1d8 *, int);
extern int func_020794d8(int);
extern int func_02079544(int);

int func_0207f1d8(void *a)
{
    int r = 0;

    func_0208150c(a);
    if (func_02003704()) {
        r = func_0207f270(a);
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64)) {
            if (func_020794d8(r) == 2) {
                r = 2;
            } else {
                r = 1;
            }
        } else {
            switch (func_02079544(r)) {
                case 0:
                    if (func_020794d8(r) == 2) {
                        r = 2;
                    } else {
                        r = 1;
                    }
                    break;
                case 2:
                    r = 3;
                    break;
                case 3:
                    r = 4;
                    break;
                case 5:
                    r = 6;
                    break;
                case 6:
                    r = 7;
                    break;
                case 4:
                    r = 5;
                    break;
                case 1:
                default:
                    r = 0;
                    break;
            }
        }
    }
    return r;
}
