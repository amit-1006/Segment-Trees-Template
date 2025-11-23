//codestorywithMIK

// n - number of elements in the original array
int segTree[4*n], arr[n], lazy[4*n];

// i - index of tree array, which always starts with 0
// l - start point from which "i" has the values(call with 0)
// r - end point till which "i" has the values(call with n-1)
// Time complexity - O(2*n) ~ O(n)
void buildTree(int i, int l, int r){
  if(l==r){
    segTree[i]=arr[l];
    return;
  }
  int mid = l+(r-l)/2;
  buildTree(2*i+1, l, mid);
  buildTree(2*i+2, mid+1, r);
  // considering range sum
  segTree[i]=segTree[2*i+1]+segTree[2*i+2];
}

// idx - index which has to be updated
// val - value with which "idx" has to be updated
// Time complexity - O(log n)
void updateNode(int i, int l, int r, int idx, int val){
  if(l==r){
    segTree[i]=val;
    arr[idx]=val; // this can be done separately also
    return;
  }
  int mid = l+(r-l)/2;
  if(idx<=mid){
    updatedNode(2*i+1, l, mid, idx, val);
  } else {
    updateNode(2*i+2, mid+1, r, idx, val);
  }
  segTree[i]=segTree[2*i+1]+segTree[2*i+2];
}

// start - starting point of range query
// end - end point of the range query
// Time complexity = O(log n)
int query(int i, int l, int r, int start, int end){
  
  // if segTree node range does not contain any index between start and end
  if(r<start || l>end) return 0;

  // if segTree node range completely covers the range [start,end]
  if(start<=l && end>=r) return segTree[i];

  // else we will have to check at both the children
  int mid = l +(r-l)/2;
  int left=query(2*i+1, l, mid, start, end);
  int right=query(2*i+2, mid+1, r, start, end);
  return left+right;
}


// Range updates - "LAZY PROAPAGATION"
// add val to all the elements of array between indices [start, end]
// Time complexity = O(log n)
void updateRange(int i, int l, int r, int start, int end, int val){
  // first update the lazy tree values
  if(lazy[i]!=0){
    segTree[i]=(r-l+1)*lazy[i];
    // the node is not a leaf code of segTree
    if(l!=r){
      lazy[2*i+1]+=lazy[i];
      lazy[2*i+2]+=lazy[i];
    }
    // reset the lazyTree value
    lazy[i]=0;
  }
  if(end<l || start>r || l>r) return;
  if(l>=start && r<=end){
    segTree[i]+=(r-l+1)*val;
    if(l!=r){
      lazy[2*i+1]+=val;
      lazy[2*i+2]+=val;
    }
    return;
  }
  int mid=l+(r-l)/2;
  updateRange(2*i+1, l, mid, start, end, val);
  updateRange(2*i+2, mid+1, r, start, end, val);
  segTree[i]=segTree[2*i+1]+segTree[2*i+2];
}
