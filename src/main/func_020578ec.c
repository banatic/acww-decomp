/* func_020578ec @ 0x020578ec, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ba01c(void *p);

typedef struct {
    char data[0x1c];
} Struct1C;

Struct1C *func_020578ec(Struct1C *param)
{
    Struct1C *p;
    Struct1C *end;

    p = param;
    end = param + 2;
    do {
        func_020ba01c(p);
        p++;
    } while (p != end);
    return param;
}
