# kyopro-library
競プロで使える自作ライブラリをまとめておいておく場所

* convolution.cpp
  FFTを使った畳み込みを行う。引数が整数型の時は誤差無し畳み込みを行う(ので定数倍が遅い)。
* func.cpp
  最大最小、二分探索、Union-Find、xor掃き出し法が入ってるライブラリ。
* graph.cpp
  グラフの入力・解析をするライブラリ。
* math_func.cpp
  gcd、lcm、sqrt、isPrime、素因数分解が入ってるライブラリ。
* mod.cpp
  modの演算をまとめたライブラリ。
* modlong.cpp
  modの計算を勝手にやってくれる整数型。機能的にはmod.cppと一緒だが、コードが簡潔になるかも...? (added on 6/1/2019 by shugo)
* qsort_wrap.cpp
  qsortをラッピングして使いやすくしたライブラリ。
* segtree.cpp
  セグメント木とBITの基本動作をしてくれるライブラリ。
* memo.cpp
  STLで用意されているデータ構造の使い方をまとめたリファレンス。
