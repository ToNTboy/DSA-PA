#include <cstdio>
#include <cstring>

#define Parent(i) ((i - 1) >> 1)
#define LChild(i) ((i << 1) + 1)
#define RChild(i) ((i + 1) << 1)

struct Task {
    long long priority;
    char name[9];
};

long long LIMIT = 0x100000000LL;
int n, m;
Task *tasks;

class ComplHeap {
public:
    ComplHeap(Task *tasks, int size) {
        _size = size;
        _heap = tasks;
        heapify();
    }

    void heapify() {
    	for (int i = Parent(_size - 1); -1 < i; i--) {
    		percolateDown(_size, i);
    	}
    }

    Task fetchMin() {
    	Task min = _heap[0];
    	_heap[0].priority = _heap[0].priority << 1;
    	percolateDown(_size, 0);
        return min;
    }

private:
	int minIn(int a, int b) {
		if (b < 0 || _size <= b) {
			return a;
		} else if (a < 0 || _size <= a) {
			return b;
		} else {
			if (_heap[a].priority < _heap[b].priority) {
				return a;
			} else if (_heap[b].priority < _heap[a].priority){
				return b;
			} else {
				if (strcmp(_heap[a].name, _heap[b].name) < 0) {
					return a;
				} else {
					return b;
				}
			}
		}
	}
	
    void percolateUp(int i) {
    	int p;
		while (-1 < Parent(i)) {
			p = Parent(i);
			if (i != minIn(i, p)) break;
    	    Task t = _heap[i];
			_heap[i] = _heap[p];
            _heap[p] = t;
            i = p;
		}
    }

    void percolateDown(int hi, int i) {
		int j;
		while (i != (j = minIn(i, minIn(LChild(i), RChild(i))))) {
            Task t = _heap[i];
			_heap[i] = _heap[j];
            _heap[j] = t;
			i = j;
		}
    }

    Task *_heap;
    int _size;
};

int main(void) {
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
    
    scanf("%d %d\n", &n, &m);
    tasks = new Task[n];
    
    for (int i = 0; i < n; i++) {
    	scanf("%lld %s\n", &tasks[i].priority, tasks[i].name);
    }
    
    ComplHeap *heap = new ComplHeap(tasks, n);
    for (int i = 0; i < m; i++) {
    	Task task = heap->fetchMin();
    	if (LIMIT <= task.priority) break;
    	printf("%s\n", task.name);
    }
    
    return 0;
}