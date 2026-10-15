/* func_02099d08 @ 0x02099d08, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003704(void *);
extern int func_02064294(void *);
extern int func_020644cc(int);
extern void func_02063ccc(void *, void *, int);
extern void func_020638d4(void *, void *, int, int, int, int, int);
extern void func_02063cc8(void *);
extern int func_02099df4(void *);
extern void func_02099dcc(void *, void *, int, void *, void *);
extern void *data_020d19c4[];

int func_02099d08(void *a1, void *a2, int a3, void *a4)
{
    unsigned short localA[2];
    unsigned int localB[2];
    unsigned int localC[2];

    if (func_02003704(a2) != 0 && func_02064294(a4) != 0) {
        localA[0] = 0xfff1;

        if (func_020644cc(4) == 0) {
            int res = func_020644cc(3);
            func_02063ccc(localB, data_020d19c4[res], 0);
            localC[0] = localB[0];
            localC[1] = localB[1];
            func_020638d4(&localA[1], localC, 0, 0, 1, 1, 0);
            localA[0] = localA[1];
            func_02063cc8(localC);
            func_02063cc8(localB);
        }

        if (func_02099df4(a1) != 0) {
            if (a3 >= (signed char) ((char *) a1)[0x20]) {
                func_02099dcc(a1, a2, a3, a4, localA);
                return 1;
            }
        } else {
            func_02099dcc(a1, a2, a3, a4, localA);
            return 1;
        }
    }
    return 0;
}
