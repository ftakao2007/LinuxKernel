#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  int status, pid;

  
  pid = fork();         /* 関数fork() */

  if (pid == 0) {       /* 子プロセスの処理 */
    printf("子プロセス No.%d: 3秒後にpwdが走ります\n", pid);
    sleep(3);
    execl("/bin/pwd", "/bin/pwd", NULL);
    /* execl("/usr/bin/yes", "プロセスm9(^Д^)ﾌﾟｷﾞｬｰ", NULL); */
    printf("子プロセスは上で終了するのでこの処理は実行されません");
  } else {              /* 親プロセスの処理 */
    printf("親プロセス: 子プロセス pid=%d の終了を待ちます\n",  pid);
    wait(&status);
    printf("親プロセス: 終了\n");
  }
  return;
}


/* execl()
  概要
    別プログラムを実行する
    lは引数が可変長引数

  Kernelとの関係
    子プロセスがシステムコールによってプロセスの中身を/bin/pwdに入れ替えている
    下のprintfは実行されず、pwdが終了次第子プロセスは終了する
     -> 親プロセスとの親子関係は失われないので子プロセスが完了次第SIGCHLDシグナルは送信される

  引数
    1. 実行するプログラムのPATH
    2. プロセス名の指定 (任意の文字列)
*/
