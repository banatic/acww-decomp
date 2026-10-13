/* func_0207631c @ 0x0207631c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a7880(char *);
extern void func_020736bc(void *, char *, int);
extern void func_020a7830(char *, char *, char *, char *, int *);
extern void func_020a7360(int, unsigned char, unsigned char, unsigned char, int);
extern void func_020a7870(char *);
extern void *data_020ccf94;

void func_0207631c(int p0, int p1, int p2, int p3)
{
    char buf[8];
    int temp;
    func_020a7880(&buf[3]);
    func_020736bc(data_020ccf94, &buf[3], 2);
    func_020a7830(&buf[3], buf, &buf[1], &buf[2], &temp);
    func_020a7360(p3, buf[0], buf[1], buf[2], temp);
    func_020a7870(&buf[3]);
}
