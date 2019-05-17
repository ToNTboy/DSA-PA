#include <cstdio>
#include <cstring>

class clist {
public:
	clist() {
		_elems = new char[10001];
		_size = 0;
	};
	void remove(const int begin, const int end) {
		for (int i = end; i < _size; i++) {
			_elems[begin + i - end] = _elems[i];
		}
		_size -= (end - begin);
	};
	void insert(int pos, char e) {
		for (int i = _size; i > pos; i--) {
			_elems[i] = _elems[i - 1];
		}
		_elems[pos] = e;
		_size++;
	}
	void append(char e) {
		_elems[_size++] = e;
	};
	char find(const int pos) { return _elems[pos]; };
	int size() { return _size; };

	char* _elems;
	int _size;
};

void eliminate(clist & v, int pos) {
	if (pos < 0 || v.size() <= pos) {
		return;
	}

	int ll = pos; int rl = pos;
	while (ll != 0 && v.find(ll - 1) == v.find(ll)) {
		ll--;
	}
	while (rl != (v.size() - 1) && v.find(rl + 1) == v.find(rl)) {
		rl++;
	}

	if ((rl - ll) < 2) {
		return;
	}
	else {
		v.remove(ll, rl + 1);
		eliminate(v, ll);
	}
}

int main() {
	// accept input
	clist beads = clist();
	int oprs;
	int *insPos;
	char *insChar;

	char tmp;
	while (true) {
		tmp = getchar();
		if (tmp < 'A' || 'Z' < tmp) {
			break;
		}
		beads.append(tmp);
	}

	scanf("%d", &oprs);
	insPos = new int[oprs];
	insChar = new char[oprs];
	for (int i = 0; i < oprs; i++) {
		scanf("%d %c", &insPos[i], &insChar[i]);
	}

	// desolve opration sequence
	for (int i = 0; i < oprs; i++) {
		beads.insert(insPos[i], insChar[i]);
		eliminate(beads, insPos[i]);
		if (beads.size() == 0) {
			printf("-\n");
		}
		else {
			for (int j = 0; j < beads.size(); j++) {
				printf("%c", beads.find(j));
			}
			printf("\n");
		}
	}

	return 0;
}