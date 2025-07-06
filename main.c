#include <stdio.h>
#include <stdlib.h>
#define linii_cadran 3

void afismat(int n, int m, int **a) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void rotatie(int n, int m, int **a, int coloana, long long rotatii) {
    int i, *v;

    v = malloc(n * sizeof(int));

    if (coloana == -1) {
        scanf("%d", &coloana);
    }

    if (rotatii == -1) {
        scanf("%lld", &rotatii);
    }

    rotatii = rotatii % n;

    for (i = 0; i < n - rotatii; i++) {
        v[i + rotatii] = a[i][coloana];
    }

    for (i = 0; i < rotatii; i++) {
        v[i] = a[n - rotatii + i][coloana];
    }

    for (i = 0; i < n; i++) {
        a[i][coloana] = v[i];
    }

    free(v);
}

void task2(int n, int m, int **a, long long *nrcomb, long long *scor) {
    int i, j, secvmax, lungsecv, valsecv, valsecvmax = 0, nrsimboluri = 0, *v;

    v = malloc(10 * sizeof(int));

    for (i = 0; i < 10; i++) {
        v[i] = 0;
    }
    for (i = 0; i < linii_cadran; i++) {
        for (j = 0; j < m; j++) {
            v[a[i][j]] = 1;
        }
    }
    for (i = 0; i <= 9; i++) {
        if (v[i] != 0) {
            nrsimboluri++;
        }
    }
    if (nrsimboluri <= 2) {
        (*scor) += 100;
    } else {
        if (nrsimboluri <= 4) {
            (*scor) += 15;
        }
    }
    free(v);

    for (i = 0; i < linii_cadran; i++) {
        secvmax = 0;
        lungsecv = 1;
        for (j = 0; j < m - 1; j++) {
            valsecv = a[i][j];
            if (a[i][j] == a[i][j + 1]) {
                lungsecv++;
            } else {
                if (lungsecv > secvmax) {
                    secvmax = lungsecv;
                    valsecvmax = valsecv;
                }
                lungsecv = 1;
            }
        }
        if (lungsecv > secvmax) {
            secvmax = lungsecv;
            valsecvmax = valsecv;
        }
        if (secvmax >= 3) {
            (*scor) += secvmax;
            if (valsecvmax == 7) {
                (*scor) += secvmax;
            }
            (*nrcomb)++;
        }
    }

    for (j = 0; j < m - 2; j++) {
        if (a[0][j] == a[1][j + 1] && a[0][j] == a[2][j + 2]) {
            (*nrcomb)++;
            if (a[0][j] == a[0][j + 2] && a[0][j] == a[2][j]) {
                (*scor) += 21;
                if (a[0][j] == 7) {
                    (*scor) += 21;
                }
            } else {
                (*scor) += 7;
                if (a[0][j] == 7) {
                    (*scor) += 7;
                }
            }
        }
        if (a[0][j + 2] == a[1][j + 1] && a[0][j + 2] == a[2][j] &&
        ((a[0][j + 2] != a[0][j]) || a[0][j + 2] != a[2][j + 2])) {
            (*scor) += 7;
            (*nrcomb)++;
            if (a[0][j + 2] == 7) {
                (*scor) += 7;
            }
        }
    }
}

void task3(int n, int m, int **a) {
    int i, t, coloana;
    long long rotatii, scor = 0, nrcomb = 0;

    scanf("%d", &t);

    for (i = 0; i < t; i++) {
        scanf("%d", &coloana);
        scanf("%lld", &rotatii);

        rotatie(n, m, a, coloana, rotatii);

        task2(n, m, a, &nrcomb, &scor);
    }

    printf("%lld\n", scor);
}

void task4(int n, int m, int **a) {
    int i, j, k, val;
    long long scor = 0, nrcomb = 0, scormax = 0;
    for (i = 0; i < linii_cadran; i++) {
        for (j = 0; j < m; j++) {
            val = a[i][j];

            for (k = 0; k <= 9; k++) {
                scor = 0;
                nrcomb = 0;
                a[i][j] = k;
                task2(n, m, a, &nrcomb, &scor);

                if (scor > scormax) {
                    scormax = scor;
                }
            }

            a[i][j] = val;
        }
    }
    printf("%lld\n", scormax);
}

void task5(int n, int m, int **a) {
    int i, j, k, t, scormax = 0;
    long long nrcomb = 0, scor = 0;
    for (i = 0; i < m - 1; i++) {
        for (j = i + 1; j < m; j++) {
            for (k = 0; k < n; k++) {
                for (t = 0; t < n; t++) {
                    rotatie(n, m, a, i, k);
                    rotatie(n, m, a, j, t);

                    scor = 0;
                    nrcomb = 0;

                    task2(n, m, a, &nrcomb, &scor);

                    if (scor > scormax) {
                        scormax = scor;
                    }

                    rotatie(n, m, a, i, n - k);
                    rotatie(n, m, a, j, n - t);
                }
            }
        }
    }

    printf("%d\n", scormax);
}

int interior(int l, int c, int n, int m) {
    return (0 <= l && l < n && 0 <= c && c < m);
}

void task6(int n, int m, int **a) {
    struct element {
        int l, c;
    };

    struct element *q;

    int dl[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    int l, c, ll, cc, val, i, j, st, dr, **b;

    q = (struct element *)malloc(2 * n * m * sizeof(struct element));
    b = malloc(n * sizeof(int *));

    for (i = 0; i < n; i++) {
        b[i] = malloc(m * sizeof(int));
    }

    val = a[0][0];
    for (i = 0; i < linii_cadran; i++) {
        for (j = 0; j < m; j++) {
            a[i][j] = abs(a[i][j] - val);
            b[i][j] = -1;
        }
    }

    st = dr = 0;

    q[st].l = 0;
    q[st].c = 0;
    b[0][0] = 0;

    while (st <= dr) {
        l = q[st].l;
        c = q[st].c;

        for (i = 0; i < 4; i++) {
            ll = l + dl[i];
            cc = c + dc[i];
            if (interior(ll, cc, linii_cadran, m) && (b[l][c] + a[ll][cc] < b[ll][cc] || b[ll][cc] == -1)) {
                dr++;
                b[ll][cc] = b[l][c] + a[ll][cc];
                q[dr].l = ll;
                q[dr].c = cc;
            }
        }

        st++;
    }

    printf("%d\n", b[linii_cadran - 1][m - 1]);

    for (i = 0; i < n; i++) {
        free(b[i]);
    }
    free(b);
    free(q);
}

int main() {
    int task, n, m, **a, i, j;
    scanf("%d", &task);
    scanf("%d", &n);
    scanf("%d", &m);

    a = malloc(n * sizeof(int *));

    for (i = 0; i < n; i++) {
        a[i] = malloc(m * sizeof(int));
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    switch (task) {
    case 1:
        rotatie(n, m, a, -1, -1);
        afismat(n, m, a);
        break;
    case 2: {
        long long scor = 0, nrcomb = 0;
        task2(n, m, a, &nrcomb, &scor);
        printf("%lld\n", nrcomb);
        printf("%lld\n", scor);
        break;
    }
    case 3:
        task3(n, m, a);
        break;
    case 4:
        task4(n, m, a);
        break;
    case 5:
        task5(n, m, a);
        break;
    case 6:
        task6(n, m, a);
        break;
    default:
        break;
    }

    for (i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);

    return 0;
}
