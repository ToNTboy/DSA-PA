#include <cstdio>

/*
Ax+By+C=0
A=y2-y1; 　　B=x1-x2;　　C=x2*y1-x1*y2;
D=A*xp+B*yp+C
D < 0 : left
D > 0 : right
*/

struct P {
    long long x;
    long long y;
};

P *alarms;
P *points;

long long judgeLR(P & point, P & alarm) {
    long long d = alarm.y * point.x + alarm.x * point.y - alarm.x * alarm.y;
    return d;
}

/* return -1 ~ n */
int binSearch(P & point, int lo, int hi) {
    int mi;
    while (1 < hi - lo) {
        mi = (lo + hi) >> 1;
        if (judgeLR(point, alarms[mi]) < 0) {
            hi = mi;
        } else {
            lo = mi;
        }
    }
    return judgeLR(point, alarms[lo]) < 0? lo - 1 : lo;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    alarms = new P[n];
    points = new P[m];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &alarms[i].x, &alarms[i].y);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    for (int i = 0; i < m; i++) {
        printf("%d\n", binSearch(points[i], 0, n) + 1);
    }

    return 0;
}