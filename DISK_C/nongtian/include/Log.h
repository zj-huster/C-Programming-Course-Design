#ifndef LOG_H
#define LOG_H

void input_string(int x, int y, KeyIn* word, int size, int mode);
void input_line(int x, int y, KeyIn* word, int size);
int judge_account(char* account);
int judge_password(char* account, char* password);

#endif