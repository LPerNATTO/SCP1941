# SCP-1941-Ω素因数探索プログラム
タイトルの通りです．<br>
[フェルマーの小定理](https://ja.wikipedia.org/wiki/%E3%83%95%E3%82%A7%E3%83%AB%E3%83%9E%E3%83%BC%E3%81%AE%E5%B0%8F%E5%AE%9A%E7%90%86)と[Left-to-right binary method](https://en.wikipedia.org/wiki/Modular_exponentiation#Left-to-right_binary_method)を用いて[SCP-1941-Ω](http://scp-jp.wikidot.com/scp-1941)の因数であるかを計算します．<br>
現在はあまり大きくない数までしか探索できていないため素数判定も行っておりますが，10^12以上の数では使えない方法(10^6までの素数による試し割り)ですので，そのうち因数判定のみを行い別個に素数判定を行う必要があるかもしれません．<br>
<br>
なおソフトの起動時にexeと同階層にtemp.txtがある場合は末尾の数字列を読み込み，その値から計算を再開します(存在しない場合は11から計算を開始します)．逆にソフト終了時にはtemp.txtの末尾に計算を行った時間とそのとき計算していた値を数字列として書き加えます．<br>
本当であればDBとPHPなどで既に計算されていない区間を割り振って分散処理のように計算することも考えていましたが，現段階ではPHPとSQLで大きな数を扱う手段が思いつかなかったため保留しております．
<br>
## SCP-1941について
著者: Requitefahrenheit様<br>
タイトル: SCP-1941 - Lunar Von Neumann Catastrophe<br>
URL: [http://scp-wiki.wikidot.com/scp-1941](http://scp-wiki.wikidot.com/scp-1941)<br>
CC BY-SA 3.0