study-linuxkernel
=================
Linuxカーネルにつての勉強用。ダウンロードしたものについて勉強する


## ダウンロード
https://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/commit/?id=9a3c4145af32125c5ee39c0272662b47307a8323  
```
git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
```

## 階層構造
勉強するについてれ書き足していく  

- linux
  - init       <- いまここ1
    + Kconfig
    + Makefile
    + calibrate.c
    + do_mounts.c
    + do_mounts.h
    + do_mounts_initrd.c
    + do_mounts_md.c
    + do_mounts_rd.c
    + init_task.c
    + initramfs.c
    + main.c
    + noinitramfs.c
    + version.c
  - kernel
    + fork.c  <- いまここ2


## コミッタとコミット日時の表示
```
git blame kernel/fork.c
```

行頭はコミットIDでその行を追加したパッチを特定する。

## コミットIDからパッチの内容を確認
```
git show c6a7f572
```

### Reviewed-by
パッチをレビューして問題無いと確認した人の署名

### Signed-off-by
パッチの作成者、および、メンテナがこのパッチを制式採用することに同意したことを示す署名。
一番下が最終的に同意した人。


## リンク
- [はじめてのカーネル・ソース 目次](http://itpro.nikkeibp.co.jp/article/COLUMN/20071023/285284/)
- [Linuxカーネルの設定パラメータ](http://itpro.nikkeibp.co.jp/article/COLUMN/20071025/285507/?ST=oss)

