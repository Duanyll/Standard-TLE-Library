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

template<typename T, size_t N>
struct lucas_t {
   private:
	T pow(T a, T b, T mod) {
    	T res = 1;
    	while (b) {
        	if (b & 1) res = res * a % mod;
        	a = a * a % mod;
        	b /= 2;
    	}
    	return res;
	}
   	
   public:
   	T c(T n, T m, T mod) {
   		if (n < m) {
   			return 0;
   		} else if (m > n - m) {
   			m = n - m;
   		}
   		T a = 1, b = 1;
   		for (int i = 0; i < m; i++) {
   			a = a * (n - i) % mod;
   			b = b * (i + 1) % mod;
   		}
   		return a * pow(b, mod - 2, mod) % mod;
   	}
   	
	T operator()(T n, T m, T mod) {
		if (m == 0) {
			return 1;
		} else if (m > n) {
			return 0;
		}	
		return (*this)(n / mod, m / mod, mod) * c(n % mod, m % mod, mod) % mod;
	} 	
};
