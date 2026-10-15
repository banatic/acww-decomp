/* func_ov107_0229d7b0 @ 0x0229d7b0, 0x78 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(char *);
extern int func_ov002_02209044(char *, int, char *, int);
extern void func_ov002_0220a1dc(char *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov107_0229cb78(char *);
extern void func_ov107_0229cdcc(char *);
extern void func_ov107_0229cd68(char *);

struct FlagsStruct {
    unsigned short unk_00;
    unsigned short flags;
};
extern struct FlagsStruct data_021fbe40;

void func_ov107_0229d7b0(char *param)
{
    if (func_ov002_02208014(param) != 0) {
        func_ov107_0229cb78(param);
        return;
    } else {
        int v = func_ov002_02208008(param);
        if (func_ov002_02209044(param + 0x2318, v, param + 0xbd, 0) != 0) {
            func_ov107_0229cdcc(param);
            return;
        } else {
            unsigned short f = data_021fbe40.flags;
            if (f & 1) {
                func_ov002_0220a1dc(param + 0x22b4);
                func_ov002_02208098((void *) (param), 7);
                return;
            }
            if (f & 2) {
                func_ov107_0229cd68(param);
            }
        }
    }
}
