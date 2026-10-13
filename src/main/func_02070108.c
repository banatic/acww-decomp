/* func_02070108 @ 0x02070108, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020df328[2];
extern int *data_020df5ec[];
extern void func_0204f934(int);
extern void func_0206ff98(int);

int func_02070108(void)
{
    int *arr;
    int i;

    if (data_020df328[0] != 2) {
        return 0;
    }
    arr = data_020df5ec[data_020df328[1]];
    for (i = 0; arr[i] != -1; i++) {
        func_0204f934(arr[i]);
    }
    data_020df328[0] = 3;
    func_0206ff98(data_020df328[1]);
    return 1;
}
