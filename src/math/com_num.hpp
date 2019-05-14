const int MAXC = 50;

int C[MAXC][MAXC];

void init_cnum() {
    for (int i = 0; i < MAXC; i++) {
        C[i][0] = 1;
        for (int j = 1; j < MAXC; j++) {
            C[i][j] = C[i - 1][j] + C[i][j - 1];
        }
    }
    return;
}