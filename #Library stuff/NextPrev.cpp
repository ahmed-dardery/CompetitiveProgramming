// comparison in while is opposite of needed
// for example: <= opposite of >
void next_gt() {
    stack<int> stck;
    stck.push(n);
    for (int i = n-1; ~i; --i) {
        while (stck.top() != n && a[stck.top()] <= a[i])
            stck.pop();

        af[i] = stck.top();
        stck.push(i);
    }
}
void prev_gte(){
    stack<int> stck;
    stck.push(-1);
    for (int i = 0; i < n; ++i) {
        while (stck.top() != -1 && a[stck.top()] < a[i])
            stck.pop();

        bf[i] = stck.top();
        stck.push(i);
    }
}
