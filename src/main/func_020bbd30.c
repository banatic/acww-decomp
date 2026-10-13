/* func_020bbd30 @ 0x020bbd30, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021f75b0[];
extern int data_021f8af4[];
extern int data_021f8b04[];
extern int data_020e5fe0[];
extern int data_021fbe94;

extern int func_02064b2c(int, int, int, int *);
extern void func_02064af4(int, int, int, int);

int func_020bbd30(void)
{
    int j0 = 0;
    int i, j;
    int neg4 = -4;

    for (i = 0; i < 2; i++) {
        for (j = j0; j < 2; j++) {
            char *pA = data_021f75b0 + i * 8;
            int *pB = (int *) ((char *) data_021f8af4 + i * 8);
            int *pC = (int *) ((char *) data_021f8b04 + i * 8);
            int *pD = (int *) ((char *) data_020e5fe0 + i * 8);
            int val = *(int *) (pA + j * 4 + 0x1544);
            if (val == 0) {
                int res = func_02064b2c(pD[j], data_021fbe94, neg4, &pC[j]);
                pB[j] = res;
                if (pB[j] == 0) {
                    return 0;
                }
            } else {
                func_02064af4(pD[j], val, *(int *) (pA + j * 4 + 0x1554), 0x1554);
            }
        }
    }
    return 1;
}
