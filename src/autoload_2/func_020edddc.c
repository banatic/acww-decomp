/* func_020edddc @ 0x020edddc, 0x84 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} Pair;
typedef struct {
    char pad_00[12];
    unsigned short unk_0C;
} Input;

extern Pair data_0213e7a4; // 0x0213e7a4
extern Pair data_0213e79c; // 0x0213e79c
extern Pair data_0213e784; // 0x0213e784

extern int func_01ffd44c(const Input *p, Pair c, Pair b, Pair a);
extern void func_020edbec(unsigned short v);

int func_020edddc(Input *p)
{
    unsigned short v = p->unk_0C;
    int result = func_01ffd44c(p, data_0213e784, data_0213e79c, data_0213e7a4);
    if (result == 1) {
        func_020edbec(v);
    }
    return result;
}
