template <typename T>
void merge_sort(T* a, int l, int r, int& ans, T* tmp) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    merge_sort(a, l, mid);
    merge_sort(a, mid + 1, r);
    int i = l, j = mid + 1;
    int k = l;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            ans += mid - i + 1;
        }
    }
    while (i <= mid) {
        tmp[k++] = a[i++];
    }
    while (j <= r) {
        tmp[k++] = a[j++];
    }
    for (int i = l; i <= r; i++) {
        a[i] = tmp[i];
    }
}

template <typename T> 
int merge_sort(T* a, int n) {
    auto tmp = new T[n + 10];
    int ans = 0;
    merge_sort(a, 1, n, ans, tmp);
    delete[] tmp;
    return ans;
}
