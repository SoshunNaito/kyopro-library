# kyopro-library
競プロで使える自作ライブラリをまとめておいておく場所

* convolution.cpp
  FFTを使った畳み込みを行う。引数が整数型の時は誤差無し畳み込みを行う(ので定数倍が遅い)。
* func.cpp
  ランレングス圧縮、グリッド、二分探索、Union-Find、xor掃き出し法が入ってるライブラリ。
* geometry.cpp
  点、直線、三角形、円のクラスと、凸包と最小包含円が入っているライブラリ。
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
* string.cpp
  文字列アルゴリズム(Z-algorithm, Rolling Hash)が入っているライブラリ。
* tree.cpp
  木の入力、根からの距離、LCA、直径と中心、木のハッシュ値に対応したライブラリ。
* memo.cpp
  STLで用意されているデータ構造の使い方をまとめたリファレンス。
