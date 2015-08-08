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
  printf("すべての子プロセスの終了を待ちます\n");
  for (i=0; i<P_MAX; i++) {  /* forループ2 */
    wait(&status);
  }
  return;
}

/* 処理の流れ
    1. 親プロセスがforループ1で子プロセスを作成
    2. 親プロセスがforループ2で子プロセスが終了することをを待つ
    3. 子プロセスが処理を開始
    4. 子プロセスが処理を終了
    5. カーネルが親プロセスにSIGCHLDシグナルを送信する
    6. 親プロセスがwait()で子プロセスの情報を受け取って子プロセスが消滅
    7. 処理終了
*/

/* fork()
  概要
    ステムコールを用いて親プロセスが自分自身を複製した子プロセスを生成するようにカーネルに依頼する
    子プロセスは親プロセスと同じプログラムコードを実行する
      -> 全てではなくfork()以下を実行

  戻り値
    親プロセスは親プロセスのPID
    子プロセスは0
*/

/* wait()
  概要
    任意の子プロセスが終了するまで待つ
    その子プロセスが終了すると&statusに終了した子プロセスの情報が入る
    -> 親プロセスに子プロセスの情報が受け渡されて子プロセスは完全に消滅する

  Linuxカーネルの挙動
    1.子プロセスが終了すると、カーネルは親プロセスにSIGCHLD(CHLD)シグナルを送信する

    2-1.親プロセスがwait()で子プロセスの終了を待っている場合
      関数wait()から抜けて引数の変数に終了した子プロセスの情報が入り、子プロセスは消滅する
    2-2.親プロセスがwait()を実行していなかった時
      子プロセスはゾンビの状態でとどまる
      親プロセスがwait()を実行したタイミングで子プロセスの情報が渡され、子プロセスは消滅する
        -> ゾンビの状態がいつも残っている場合、親プロセスに問題がある
    2-3.子プロセスが終了するより先に親プロセスが終了した場合
      /sbin/init (PID=1) が代わりの親プロセスとなり、wait()を実行する     
*/

/* waitpid()
  特定のプロセスIDの子プロセスについて終了を待ち合わせる
*/
