/* func_0207323c @ 0x0207323c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct ArcadeStruct {
    char pad_00[0x128];
    unsigned short unk_128[1];
} ArcadeStruct;

extern ArcadeStruct *data_020ccf94;
extern int func_02073dd4(ArcadeStruct *p, int i);
extern int func_02073918(ArcadeStruct *p, int i);
extern int func_02077b58(int i);
extern unsigned int func_02073220(ArcadeStruct *p, int i);
extern int func_02077a64(void);

void func_0207323c(ArcadeStruct *arr)
{
    int i;
    ArcadeStruct *obj;
    int v;
    unsigned int x;

    i = 3;
    obj = data_020ccf94;
    do {
        if (func_02073dd4(obj, i) != 0 && func_02073918(obj, i) == 0) {
            v = func_02077b58(i);
            x = func_02073220(obj, i);
            func_02077a64();
            if (x <= 0x258) {
                arr->unk_128[v]++;
            }
        }
        --i;
    } while (i >= 0);
}
