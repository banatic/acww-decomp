/* func_020761fc @ 0x020761fc, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020736bc(int, char *, int);
extern void func_0205fa84(char *);

extern int data_020ccf94;

void func_020761fc(unsigned int param)
{
    char buffer[12];
    unsigned int i = 0;
    int data = data_020ccf94;
    while (i < param) {
        func_020736bc(data, buffer, 5);
        func_0205fa84(buffer);
        i += 5;
    }
}
