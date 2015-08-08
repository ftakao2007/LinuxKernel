#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define P_MAX 3  /* 子プロセス数の最大数*/

int main() {
  int pid[P_MAX];
  int status, i;

  for (i=0; i<P_MAX; i++) {  /* forループ1 */
    pid[i] = fork();         /* 関数fork() */
    if (pid[i] == 0) {       /* 子プロセスの処理 */
      printf("子プロセス No.%d: 開始\n", i);
      sleep(i+1);
      printf("子プロセス No.%d: 終了\n", i);
      exit(0);               /* 子プロセス処理終了 */
    } else {                 /* 親プロセスの処理 */
      printf("親プロセス: 子プロセスNo.%d(pid=%d)を開始\n", i, pid[i]);
    }
  }
  printf("すべての子プロセスはゾンビになります\n");
  return;
}
