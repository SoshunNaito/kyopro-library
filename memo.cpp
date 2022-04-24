/*
/////////////         小数の表示
	double x = 1.0 / 7;
	cout << fixed << setprecision(15) << x << endl;	// これで小数点以下15桁まで出力できる





/////////////         STLの使い方メモ

ソート
	vector<int> v;	// 宣言
	sort(v.begin(), v.end());	// 昇順ソート
	sort(v.begin(), v.end(), greater<int>());	// 降順ソート





可変長配列 vector
	vector<int> v;	// 宣言

	v.clear();		// 全消去
	v.size();		// サイズ取得
	v[i];			// i番目の要素を取得

	v.push_back(int n);		// 後ろに要素nを追加する
	v.pop_back();			// 最後尾の要素を消去する

	for(auto itr = v.begin(); itr != v.end(); itr++){
		itr			// 操作するデータへのイテレータ
		*itr		// データ本体
	}





連結リスト list
	list<int> lst;		// 宣言

	lst.clear();		// 全消去
	lst.size();			// サイズ取得

	lst.push_back(int n);		// 後ろに要素nを追加する
	lst.pop_back();				// 最後尾の要素を消去する
	lst.push_front(int n);		// 先頭に要素nを追加する
	lst.pop_front();			// 先頭の要素を消去する

	lst.unique();				// 連続した重複を消す
	lst.sort();					// 昇順ソート
	lst.sort(greater<int>());	// 降順ソート

	for(auto itr = lst.begin(); itr != lst.end(); itr++){
		itr			// 操作するデータへのイテレータ
		*itr		// データ本体

		itr2 = lst.insert(itr, n);		// itrが指す部分の直前にnを挿入し、nを指すイテレータを返す。
	}





双方向キュー deque
	deque<int> deq;		// 宣言

	deq.clear();		// 全消去
	deq.size();			// サイズ取得
	deq[i];				// i番目の要素を取得

	deq.push_back(int n);		// 後ろに要素nを追加する
	deq.pop_back();				// 最後尾の要素を消去する
	deq.push_front(int n);		// 先頭に要素nを追加する
	deq.pop_front();			// 先頭の要素を消去する

	for(auto itr = deq.begin(); itr != deq.end(); itr++){
		itr			// 操作するデータへのイテレータ
		*itr		// データ本体
	}





データの重複を "許さない" 集合 set
	set<int> st;					// 昇順ソートで管理するときの宣言
	set<int, greater<int>> st;		// 降順ソートで管理するときの宣言

	st.clear();		// 全消去
	st.size();		// サイズ取得

	auto p = st.insert(int n);			// 集合にnを追加する。pの第一成分はnを指すイテレータ、第二成分は追加できたかのフラグ。
	auto itr = st.find(int n);			// 要素nを検索し、見つかった要素を指すイテレータを返す。itr == st.end() のとき検索失敗。

	st.erase(int n);		// 要素nを消去する
	st.erase(itr);			// itrが指す要素を消去する

	auto itr = st.lower_bound(int n);		// n以上(以下)となる要素のうち、最も小さい(大きい)ものを指すイテレータを返す。
	auto itr = st.upper_bound(int n);		// nよりも大きい(小さい)要素のうち、最も小さい(大きい)ものを指すイテレータを返す。

	for (auto itr = st.begin(); itr != st.end(); itr++) {
		itr			// 操作するデータへのイテレータ
		*itr		// データ本体
	}





データの重複を "許す" 集合 multiset
	multiset<int> mset;						// 昇順ソートで管理するときの宣言
	multiset<int, greater<int>> mset;		// 降順ソートで管理するときの宣言

	mset.clear();		// 全消去
	mset.size();		// サイズ取得

	auto p = mset.insert(int n);		// 集合にnを追加する。pの第一成分はnを指すイテレータ、第二成分は追加できたかのフラグ。
	auto itr = mset.find(int n);		// 要素nを検索し、見つかった要素を指すイテレータを返す。itr == st.end() のとき検索失敗。

	mset.erase(int n);		// 要素nを "すべて" 消去する
	mset.erase(itr);		// itrが指す要素を消去する

	auto itr = mset.lower_bound(int n);		// n以上(以下)となる要素のうち、最も小さい(大きい)ものを指すイテレータを返す。
	auto itr = mset.upper_bound(int n);		// nよりも大きい(小さい)要素のうち、最も小さい(大きい)ものを指すイテレータを返す。

	for (auto itr = mset.begin(); itr != mset.end(); itr++) {
		itr			// 操作するデータへのイテレータ
		*itr		// データ本体
	}





キーの重複を "許さない" 連想配列 map
	map<int, int> mp;					// keyについて昇順ソートで管理するときの宣言
	map<int, int, greater<int>> mp;		// keyについて降順ソートで管理するときの宣言

	mp.clear();			// 全消去
	mp.size();			// サイズ取得
	mp[int n];			// key = nとなる要素を得る。無い場合は0を返す。

	auto p = mp.insert(make_pair(int key, int value));		// データを追加する。pの第一成分はデータを指すイテレータ、第二成分は追加できたかのフラグ。

	auto itr = mp.find(int n);		// key = nとなるを検索し、見つかった要素を指すイテレータを返す。itr == mp.end() のとき検索失敗。
	mp.erase(int n);				// key = nとなる要素を消去する。

	auto itr = mp.lower_bound(int n);		// keyがn以上(以下)となる要素のうち、最も小さい(大きい)ものを指すイテレータを返す。
	auto itr = mp.upper_bound(int n);		// keyがnよりも大きい(小さい)要素のうち、最も小さい(大きい)ものを指すイテレータを返す。

	for (auto itr = mp.begin(); itr != mp.end(); itr++) {
		itr				// 操作するデータへのイテレータ
		*itr			// データ本体
	}





キーの重複を "許す" 連想配列 multimap
	multimap<int, int> mmap;					// keyについて昇順ソートで管理するときの宣言
	multimap<int, int, greater<int>> mmap;		// keyについて降順ソートで管理するときの宣言

	mmap.clear();		// 全消去
	mmap.size();		// サイズ取得
	mmap[int n];		// key = nとなる要素を得る。無い場合は0を返す。

	auto p = mmap.insert(make_pair(int key, int value));		// データを追加する。pの第一成分はデータを指すイテレータ、第二成分は追加できたかのフラグ。

	auto itr = mmap.find(int n);	// key = nとなるを検索し、見つかった要素を指すイテレータを返す。itr == st.end() のとき検索失敗。
	mmap.erase(int n);				// key = nとなる要素を消去する。

	auto itr = mmap.lower_bound(int n);		// keyがn以上(以下)となる要素のうち、最も小さい(大きい)ものを指すイテレータを返す。
	auto itr = mmap.upper_bound(int n);		// keyがnよりも大きい(小さい)要素のうち、最も小さい(大きい)ものを指すイテレータを返す。

	for (auto itr = mmap.begin(); itr != mmap.end(); itr++) {
		itr				// 操作するデータへのイテレータ
		*itr			// データ本体
	}





優先度付きキュー priority_queue
	priority_queue<int> que;	// 降順に出力
	priority_queue<int, vector<int>, greater<int>> que;		// 昇順に出力

	que.size();			// サイズを取得する

	que.push(int n);	// 要素を追加する
	que.top();			// 最大値(最小値)を見る
	que.pop();			// 最大値(最小値)を消去する





ビット演算を高速にできる bitset
	bitset<32> bset;

	bset.any();			// 1が立っているビットがあればtrue
	bset.all();			// 全て1ならばtrue
	bset.none();		// 全て0ならばtrue

	bset.count();		// 1が立っているフラグの個数を返す

	bset.flip();		// ビットの順序を反転させる
*/