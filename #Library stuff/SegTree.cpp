typedef long long ll;

const int N = 1e5;

ll segTree[N];
ll events[N];
int n, q;
char c;  int d, v;


ll query(int qs, int qe, int si = 0, int ss = 0, int se = n - 1) {
	if (qs <= ss && qe >= se)		//if segment is fully inside query
		return segTree[si];
	if (qs > se || qe < ss)			//if query is fully outside segment
		return 0;

	int mid = (ss + se) / 2;

	return query(qs, qe, 2 * si + 1, ss, mid) + query(qs, qe, 2 * si + 2, mid + 1, se);
}
void update(int qi, ll val, int si = 0, int ss = 0, int se = n - 1) {
	if (qi < ss || qi > se)
		return;

	if (ss == se) {
		segTree[si] = val;
		events[qi] = val;
	}
	else {
		int mid = (ss + se) / 2;
		update(qi, val, 2 * si + 1, ss, mid);
		update(qi, val, 2 * si + 2, mid + 1, se);
		segTree[si] = segTree[2 * si + 1] + segTree[2 * si + 2];
	}
}
ll construct(int si = 0, int ss = 0, int se = n - 1) {
	if (ss == se) {
		return segTree[si] = events[ss];
	}

	int mid = (ss + se) / 2;

	return segTree[si] = construct(2 * si + 1, ss, mid) + construct(2 * si + 2, mid + 1, se);
}

void updateRangeUtil(int si, int ss, int se, int us, 
                     int ue, int diff) 
{ 
    // If lazy value is non-zero for current node of segment 
    // tree, then there are some pending updates. So we need 
    // to make sure that the pending updates are done before 
    // making new updates. Because this value may be used by 
    // parent after recursive calls (See last line of this 
    // function) 
    if (lazy[si] != 0) 
    { 
        // Make pending updates using value stored in lazy 
        // nodes 
        tree[si] += (se-ss+1)*lazy[si]; 
  
        // checking if it is not leaf node because if 
        // it is leaf node then we cannot go further 
        if (ss != se) 
        { 
            // We can postpone updating children we don't 
            // need their new values now. 
            // Since we are not yet updating children of si, 
            // we need to set lazy flags for the children 
            lazy[si*2 + 1]   += lazy[si]; 
            lazy[si*2 + 2]   += lazy[si]; 
        } 
  
        // Set the lazy value for current node as 0 as it 
        // has been updated 
        lazy[si] = 0; 
    } 
  
    // out of range 
    if (ss>se || ss>ue || se<us) 
        return ; 
  
    // Current segment is fully in range 
    if (ss>=us && se<=ue) 
    { 
        // Add the difference to current node 
        tree[si] += (se-ss+1)*diff; 
  
        // same logic for checking leaf node or not 
        if (ss != se) 
        { 
            // This is where we store values in lazy nodes, 
            // rather than updating the segment tree itelf 
            // Since we don't need these updated values now 
            // we postpone updates by storing values in lazy[] 
            lazy[si*2 + 1]   += diff; 
            lazy[si*2 + 2]   += diff; 
        } 
        return; 
    } 
  
    // If not completely in rang, but overlaps, recur for 
    // children, 
    int mid = (ss+se)/2; 
    updateRangeUtil(si*2+1, ss, mid, us, ue, diff); 
    updateRangeUtil(si*2+2, mid+1, se, us, ue, diff); 
  
    // And use the result of children calls to update this 
    // node 
    tree[si] = tree[si*2+1] + tree[si*2+2]; 
} 