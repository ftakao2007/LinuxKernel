#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/signal.h>

int main() {
  int status; /* wait関数用 */
  /* equivalent to fork() : ヘルパー関数fork()を使わずにcloneシステムコールを呼び出す */
  int pid = syscall(SYS_clone, SIGCHLD, 0, 0, 0, 0);
  /* 関数syscall()の中でCPUのsyscall命令を発行している)

  if (pid == 0) {            /* 子プロセスの処理 */
      int cpid = getpid();
      printf("Child, child pid = %d\n", cpid);
  } else if (pid == -1) {    /* エラー処理 */
      perror("SYS_clone: ");
  } else {                   /* 親プロセスの処理 */
    printf("Parent, my pid = %d\n", pid);
  }
  wait(&status);  
  return;
}




/* syscall()
  概要
    ヘルパー関数を呼び出さず指定のシステムコールを直接実行できる
    厳密にはsyscall()もヘルパー関数の一種
    -> syscall命令を発行するための必要最小限の処理に限っている
    
  引数
    1. システムコールの番号
      SYS_loneはシステムコールの番号を表すマクロでヘッダファイルの中で
      Cloneシステムコールに対応する「56」が定義されている

    2. フラグ
      メモリ空間を共有したり、スレッドを生成するなどのオプションを指定できる
      ここでは子プロセスが終了した時に親プロセスにSIGCHILDシグナルを送ることのみ指定

    3以降. スレッドに関する指定
      スレッドを利用する際に指定
      ここでは使っていない

  戻り値
*/

/* 参考プログラムとの違い
  wait(&status); を追加して子プロセスが終了するまで待つように変更

  waitがない場合は実行すると以下のようになる

  [vagrant@vagrant-centos65 c]$ ./a.out
  Parent, child pid = 3255
  [vagrant@vagrant-centos65 c]$ Child, my pid = 3255
    
  子プロセスが終わる前に親プロセスが終了し。プロンプトが戻るので
  プロンプト上に子プロセスの出力結果が出てしまう。
  waitを追加すると以下のようになる

  [vagrant@vagrant-centos65 c]$ ./a.out
  Parent, child pid = 3268
  Child, my pid = 3268
  [vagrant@vagrant-centos65 c]$
*/
