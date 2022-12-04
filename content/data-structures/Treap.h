/**
 * Author: Bikmetov Shakir
 * License: CC0
 * Description: Cartesian tree
 * Time: O(log N) merge, and split
 */

typedef int OpT; // some user type
const OpT NEUTRAL = 0;
OpT combine(const OpT &l, const OpT &r) {
    return l + r;
}
inline OpT to_op_val(int val) {
    return val;
}

struct Node;

int get_sz(Node*);
OpT get_op_val(Node*);

struct Node {
    int val;
    int p;
    int sz{1};
    OpT op_val{NEUTRAL};
    Node* L{nullptr};
    Node* R{nullptr};

    Node() { upd(); }
    Node(int val_, int p_): Node() {
        val = val_;
        p = p_;
    }
    void upd() {
        sz = 1 + get_sz(L) + get_sz(R);
        op_val = combine(get_op_val(L), to_op_val(val));
        op_val = combine(op_val, get_op_val(R));
    }
};

int get_sz(Node* v) {
    if (v == nullptr)
        return 0;
    return v->sz;
}

OpT get_op_val(Node* v) {
    if (v == nullptr)
        return NEUTRAL;
    return v->op_val;
}

typedef pair<Node*, Node*> split_t;

// split it so that ans.first.sz == pos
split_t split(Node* t, int pos) {
    if (t == nullptr) {
        return {nullptr, nullptr};
    }

    int sz = get_sz(t->L) + 1;
    if (sz <= pos) {
        split_t v = split(t->R, pos - sz);
        t->R = v.first;
        t->upd();
        return {t, v.second};
    } else {
        split_t v = split(t->L, pos);
        t->L = v.second;
        t->upd();
        return {v.first, t};
    }
}

Node* merge(Node* L, Node* R) {
    if (L == nullptr) return R;
    if (R == nullptr) return L;

    if (L->p < R->p) {
        L->R = merge(L->R, R);
        L->upd();
        return L;
    } else {
        R->L = merge(L, R->L);
        R->upd();
        return R;
    }
}