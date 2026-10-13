/* func_02097ad0 @ 0x02097ad0, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(void);
extern int func_0209985c(void);
extern void *func_02098090(void *, int);
extern int func_02065ec0(void *);

typedef struct {
    char pad_00[0x0a04];
} BigStruct;

extern BigStruct data_021ef8ec[];

int func_02097ad0(int a)
{
    BigStruct *p;
    int i;

    if (a == -1) {
        func_020984e8();
        a = func_0209985c();
    }

    p = func_02098090(&data_021ef8ec[a], 0);

    for (i = 0; i < 10; i++) {
        if (func_02065ec0(p) == 0) {
            return 0;
        }
        p = (BigStruct *) ((char *) p + 0x100);
    }

    return 1;
}
