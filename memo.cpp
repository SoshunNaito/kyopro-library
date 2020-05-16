/*
/////////////         �����̕\��
	ll x = 1.0 / 7;
	cout << fixed << setprecision(15) << x << endl;	// ����ŏ����_�ȉ�15���܂ŏo�͂ł���





/////////////         STL�̎g��������

�\�[�g
	vector<int> v;	// �錾
	sort(v.begin(), v.end());	// �����\�[�g
	sort(v.begin(), v.end(), greater<int>());	// �~���\�[�g





�ϒ��z�� vector
	vector<int> v;	// �錾

	v.clear();		// �S����
	v.size();		// �T�C�Y�擾
	v[i];			// i�Ԗڂ̗v�f���擾

	v.push_back(int n);		// ���ɗv�fn��ǉ�����
	v.pop_back();			// �Ō���̗v�f����������

	for(auto itr = v.begin(); itr != v.end(); itr++){
		itr			// ���삷��f�[�^�ւ̃C�e���[�^
		*itr		// �f�[�^�{��
	}





�A�����X�g list
	list<int> lst;		// �錾

	lst.clear();		// �S����
	lst.size();			// �T�C�Y�擾

	lst.push_back(int n);		// ���ɗv�fn��ǉ�����
	lst.pop_back();				// �Ō���̗v�f����������
	lst.push_front(int n);		// �擪�ɗv�fn��ǉ�����
	lst.pop_front();			// �擪�̗v�f����������

	lst.unique();				// �A�������d��������
	lst.sort();					// �����\�[�g
	lst.sort(greater<int>());	// �~���\�[�g

	for(auto itr = lst.begin(); itr != lst.end(); itr++){
		itr			// ���삷��f�[�^�ւ̃C�e���[�^
		*itr		// �f�[�^�{��

		itr2 = lst.insert(itr, n);		// itr���w�������̒��O��n��}�����An���w���C�e���[�^��Ԃ��B
	}





�o�����L���[ deque
	deque<int> deq;		// �錾

	deq.clear();		// �S����
	deq.size();			// �T�C�Y�擾
	deq[i];				// i�Ԗڂ̗v�f���擾

	deq.push_back(int n);		// ���ɗv�fn��ǉ�����
	deq.pop_back();				// �Ō���̗v�f����������
	deq.push_front(int n);		// �擪�ɗv�fn��ǉ�����
	deq.pop_front();			// �擪�̗v�f����������

	for(auto itr = deq.begin(); itr != deq.end(); itr++){
		itr			// ���삷��f�[�^�ւ̃C�e���[�^
		*itr		// �f�[�^�{��
	}

	intnm1



�f�[�^�̏d���� "�����Ȃ�" �W�� set
	set<int> st;					// �����\�[�g�ŊǗ�����Ƃ��̐錾
	set<int, greater<int>> st;		// �~���\�[�g�ŊǗ�����Ƃ��̐錾

	st.clear();		// �S����
	st.size();		// �T�C�Y�擾

	auto p = st.insert(int n);			// �W����n��ǉ�����Bp�̑�ꐬ����n���w���C�e���[�^�A��񐬕��͒ǉ��ł������̃t���O�B
	auto itr = st.find(int n);			// �v�fn���������A���������v�f���w���C�e���[�^��Ԃ��Bitr == st.end() �̂Ƃ��������s�B
	
	st.erase(int n);		// �v�fn����������
	st.erase(itr);			// itr���w���v�f����������

	auto itr = st.lower_bound(int n);		// n�ȏ�(�ȉ�)�ƂȂ�v�f�̂����A�ł�������(�傫��)���̂��w���C�e���[�^��Ԃ��B
	auto itr = st.upper_bound(int n);		// n�����傫��(������)�v�f�̂����A�ł�������(�傫��)���̂��w���C�e���[�^��Ԃ��B

	for (auto itr = st.begin(); itr != st.end(); itr++) {
		itr			// ���삷��f�[�^�ւ̃C�e���[�^
		*itr		// �f�[�^�{��
	}





�f�[�^�̏d���� "����" �W�� multiset
	multiset<int> mset;						// �����\�[�g�ŊǗ�����Ƃ��̐錾
	multiset<int, greater<int>> mset;		// �~���\�[�g�ŊǗ�����Ƃ��̐錾

	mset.clear();		// �S����
	mset.size();		// �T�C�Y�擾

	auto p = mset.insert(int n);		// �W����n��ǉ�����Bp�̑�ꐬ����n���w���C�e���[�^�A��񐬕��͒ǉ��ł������̃t���O�B
	auto itr = mset.find(int n);		// �v�fn���������A���������v�f���w���C�e���[�^��Ԃ��Bitr == st.end() �̂Ƃ��������s�B
	
	mset.erase(int n);		// �v�fn�� "���ׂ�" ��������
	mset.erase(itr);		// itr���w���v�f����������

	auto itr = mset.lower_bound(int n);		// n�ȏ�(�ȉ�)�ƂȂ�v�f�̂����A�ł�������(�傫��)���̂��w���C�e���[�^��Ԃ��B
	auto itr = mset.upper_bound(int n);		// n�����傫��(������)�v�f�̂����A�ł�������(�傫��)���̂��w���C�e���[�^��Ԃ��B

	for (auto itr = mset.begin(); itr != mset.end(); itr++) {
		itr			// ���삷��f�[�^�ւ̃C�e���[�^
		*itr		// �f�[�^�{��
	}





�L�[�̏d���� "�����Ȃ�" �A�z�z�� map
	map<int, int> mp;					// key�ɂ��ď����\�[�g�ŊǗ�����Ƃ��̐錾
	map<int, int, greater<int>> mp;		// key�ɂ��č~���\�[�g�ŊǗ�����Ƃ��̐錾

	mp.clear();			// �S����
	mp.size();			// �T�C�Y�擾
	mp[int n];			// key = n�ƂȂ�v�f�𓾂�B�����ꍇ��0��Ԃ��B

	auto p = mp.insert(make_pair(int key, int value));		// �f�[�^��ǉ�����Bp�̑�ꐬ���̓f�[�^���w���C�e���[�^�A��񐬕��͒ǉ��ł������̃t���O�B
	
	auto itr = mp.find(int n);		// key = n�ƂȂ���������A���������v�f���w���C�e���[�^��Ԃ��Bitr == mp.end() �̂Ƃ��������s�B
	mp.erase(int n);				// key = n�ƂȂ�v�f����������B

	auto itr = mp.lower_bound(int n);		// key��n�ȏ�(�ȉ�)�ƂȂ�v�f�̂����A�ł�������(�傫��)���̂��w���C�e���[�^��Ԃ��B
	auto itr = mp.upper_bound(int n);		// key��n�����傫��(������)�v�f�̂����A�ł�������(�傫��)���̂��w���C�e���[�^��Ԃ��B

	for (auto itr = mp.begin(); itr != mp.end(); itr++) {
		itr				// ���삷��f�[�^�ւ̃C�e���[�^
		*itr			// �f�[�^�{��
	}





�L�[�̏d���� "����" �A�z�z�� multimap
	multimap<int, int> mmap;					// key�ɂ��ď����\�[�g�ŊǗ�����Ƃ��̐錾
	multimap<int, int, greater<int>> mmap;		// key�ɂ��č~���\�[�g�ŊǗ�����Ƃ��̐錾

	mmap.clear();		// �S����
	mmap.size();		// �T�C�Y�擾
	mmap[int n];		// key = n�ƂȂ�v�f�𓾂�B�����ꍇ��0��Ԃ��B

	auto p = mmap.insert(make_pair(int key, int value));		// �f�[�^��ǉ�����Bp�̑�ꐬ���̓f�[�^���w���C�e���[�^�A��񐬕��͒ǉ��ł������̃t���O�B

	auto itr = mmap.find(int n);	// key = n�ƂȂ���������A���������v�f���w���C�e���[�^��Ԃ��Bitr == st.end() �̂Ƃ��������s�B
	mmap.erase(int n);				// key = n�ƂȂ�v�f����������B

	auto itr = mmap.lower_bound(int n);		// key��n�ȏ�(�ȉ�)�ƂȂ�v�f�̂����A�ł�������(�傫��)���̂��w���C�e���[�^��Ԃ��B
	auto itr = mmap.upper_bound(int n);		// key��n�����傫��(������)�v�f�̂����A�ł�������(�傫��)���̂��w���C�e���[�^��Ԃ��B

	for (auto itr = mmap.begin(); itr != mmap.end(); itr++) {
		itr				// ���삷��f�[�^�ւ̃C�e���[�^
		*itr			// �f�[�^�{��
	}





�D��x�t���L���[ priority_queue
	priority_queue<int> que;	// �~���ɏo��
	priority_queue<int, vector<int>, greater<int>> que;		// �����ɏo��

	que.size();			// �T�C�Y���擾����

	que.push(int n);	// �v�f��ǉ�����
	que.top();			// �ő�l(�ŏ��l)������
	que.pop();			// �ő�l(�ŏ��l)����������





�r�b�g���Z�������ɂł��� bitset
	bitset<32> bset;

	bset.any();			// 1�������Ă���r�b�g�������true
	bset.all();			// �S��1�Ȃ��true
	bset.none();		// �S��0�Ȃ��true

	bset.count();		// 1�������Ă���t���O�̌���Ԃ�

	bset.flip();		// �r�b�g�̏����𔽓]������


*/