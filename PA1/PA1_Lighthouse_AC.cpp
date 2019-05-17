#include<cstdio>

#define MAXSIZE 4000000
typedef long long ll;
struct Point {
	ll x, y;
}points[MAXSIZE];
Point *bs = new Point[MAXSIZE];
ll *b = new ll[MAXSIZE];
ll y[MAXSIZE], count = 0;

void MergeStruct(Point *elem, int lo, int mi, int hi) {
	Point *a = elem + lo, *c = elem + mi;
	int lb = mi - lo, lc = hi - mi;
    for (int i = 0; i < lb; bs[i] = a[i++]);
    for (int i = 0, j = 0, k = 0; j < lb; )
	{
        if (k < lc && c[k].x < bs[j].x) a[i++] = c[k++];
        if (lc <= k || bs[j].x <= c[k].x) {
            a[i++] = bs[j++];
        }
    }
}

void MergeSort_X(Point *elem, int lo, int hi)
{
	if (hi - lo < 2)return;
	int mi = (hi + lo) >> 1;
	MergeSort_X(elem, lo, mi);
	MergeSort_X(elem, mi, hi);
	MergeStruct(elem, lo, mi, hi);
}

void Mergell(ll *elem, int lo, int mi, int hi) {
	ll *a = elem + lo, *c = elem + mi;
	int lb = mi - lo, lc = hi - mi;
	for (int i = 0; i < lb; b[i] = a[i++]);
	for (int i = 0, j = 0, k = 0; j < lb;)
	{
		if (lc <= k || b[j] < c[k]) {
			a[i++] = b[j++];
			if (k < lc) count += lc - k;
		}
		if (k < lc&&c[k] <= b[j]) a[i++] = c[k++];
	}
}

void MergeSort_Y(ll *elem, int lo, int hi)
{
	if (hi - lo < 2)return;
	int mi = (hi + lo) >> 1;
	MergeSort_Y(elem, lo, mi);
	MergeSort_Y(elem, mi, hi);
	Mergell(elem, lo, mi, hi);
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lld %lld", &points[i].x, &points[i].y);
	MergeSort_X(points, 0, n);
	for (int i = 0; i < n; i++)
		y[i] = points[i].y;
	MergeSort_Y(y, 0, n);
	printf("%lld\n", count);
	return 0;
}

