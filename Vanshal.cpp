//Name: Vanshal Singh
//Entry No. : 2019CSB1129
/* **************************************************************************
 INSTRUCTIONS:-

 ./a.out 1 will give output corresponding to ARRAY implementation of dijkstra

 ./a.out 2 will give output corresponding to BINARY HEAP implementation of dijkstra

 ./a.out 3 will give output corresponding to BINOMIAL HEAP implementation of dijkstra

 ./a.out 4 or anything else will give output corresponding to FIBONACCI HEAP implementation of dijkstra

*****************************************************************************/

#include<bits/stdc++.h>
#include<time.h>
#define INF 10000000
#define ll long long int
#define MIN -10000000
#define pp push_back
#define mp make_pair

using namespace std;
vector< pair<ll, ll> > adj[1000000];
vector<ll> dist(1000000, INF);
map <ll, ll> positions;
ll bellmanford(ll s, ll n)
{
    vector<ll> d(n + 1, INF);
    d[s] = 0;
    vector<ll> is(n + 1, 0);
    is[s] = 1;
    vector<ll> ct(n + 1, 0);

    queue<ll> q;
    q.push(s);
    while (!q.empty())
    {
        ll k = q.front();
        is[k] = 0;
        q.pop();

        for (ll x = 0; x < adj[k].size(); x++)
        {
            ll k1 = adj[k][x].first;
            ll k2 = adj[k][x].second;

            if ((d[k1]) > (d[k] + k2))
            {
                d[k1] = d[k] + k2;
                if (is[k1] == 0)
                {
                    q.push(k1);
                    is[k1] = 1;

                    if (ct[k1] >= n)
                    {
                        return 0;
                    }
                    ct[k1]++;
                }
            }
        }
    }

    for (ll i = 1; i <= n; i++)
    {
        if (d[i] > 999999)
        {
            d[i] = 999999;
        }
    }


    for (ll i = 1; i < n; i++)
    {
        for (auto it : adj[i])
        {
            it.second += d[i] - d[it.first];
        }
    }

    return 1;

}
//ARRAY
void arraydijkstra(ll s, ll n) // DIJKSTRA ALGORITHM WITH ARRAY IMPLEMENTATION
{
    vector< pair<ll, ll> > q;
    dist[s] = 0;
    q.pp(mp(0, s));
    while (q.size())
    {
        ll k1 = 0, min = INF;
        ll pos;
        ll ct = 0;
        for (auto i : q)
        {
            if (i.first < min)
            {
                k1 = i.second;
                min = i.first;
                pos = ct;
            }
            ct++;
        }
        q.erase(q.begin() + pos);
        for (auto x : adj[k1])
        {
            if ((min + x.second) < (dist[x.first]))
            {
                dist[x.first] = min + x.second;
                q.pp(mp(dist[x.first], x.first));
            }
        }
    }
}
//BINARY HEAP
struct binaryheap
{
    ll size, capacity;
    vector< pair<ll, ll> > heap;
};
void binheapify(struct binaryheap* minheap, ll n)//Heapify
{
    ll sm = n;
    ll left = (2 * n) + 1;
    ll right = (2 * n) + 2;

    if ((left < (minheap->size)) && ((minheap->heap[left].first) < minheap->heap[sm].first))
    {
        sm = left;
    }
    if ((right < (minheap->size)) && ((minheap->heap[right].first) < minheap->heap[sm].first))
    {
        sm = right;
    }
    if (sm != n)
    {
        swap(minheap->heap[n], minheap->heap[sm]);
        swap(positions[minheap->heap[n].second], positions[minheap->heap[sm].second]);
        binheapify(minheap, sm);
    }

}
void insertbinheap(struct binaryheap* minheap, pair<ll, ll> n) // insertion in binary heap
{
    minheap->size++;
    ll k = minheap->size - 1;
    minheap->heap[k] = n;
    positions[n.second] = k;
    while (k != 0 && (minheap->heap[k].first < minheap->heap[(k - 1) / 2].first))
    {
        swap(minheap->heap[(k - 1) / 2], minheap->heap[k]);
        swap(positions[minheap->heap[(k - 1) / 2].second], positions[minheap->heap[k].second]);
        k = (k - 1) / 2;
    }
}
pair<ll, ll> delbinheap(struct binaryheap* minheap) // extracting and deleting minimum element
{
    pair<ll, ll> root;
    if (minheap->size == 1)
    {
        minheap->size = 0;
        root = minheap->heap[0];
        positions.clear();
    }
    else
    {
        root = minheap->heap[0];
        swap(minheap->heap[0], minheap->heap[minheap->size - 1]);
        swap(positions[minheap->heap[0].second], positions[minheap->heap[minheap->size - 1].second]);
        minheap->size--;
        binheapify(minheap, 0);
    }
    return root;
}
void decreasekeybinary(struct binaryheap* minheap, int pos, pair<int, int> neww) // decrease key function
{
    minheap->heap[pos] = neww;
    while (pos != 0 && (minheap->heap[(pos - 1) / 2].first > minheap->heap[pos].first))
    {
        swap(minheap->heap[pos], minheap->heap[(pos - 1) / 2]);
        swap(positions[minheap->heap[pos].second], positions[minheap->heap[(pos - 1) / 2].second]);
        pos = (pos - 1) / 2;
    }
}
void binheapdijkstra(ll s, ll n) // dijkstra algorithm using binary heap
{
    struct binaryheap minheap;
    vector<pair<ll, ll> > v(1000000);
    minheap.capacity = 1000000;
    minheap.size = 0;
    minheap.heap = v;
    dist[s] = 0;
    ll vis[n + 1];
    for (ll i = 0; i <= n; i++)
    {
        vis[i] = 0;
    }

    insertbinheap(&minheap, make_pair(0, s));
    vis[s] = 1;

    while (minheap.size != 0)
    {
        pair<ll, ll> k = delbinheap(&minheap);
        vis[k.second] = 0;
        ll temp1 = k.first;
        ll temp2 = k.second;

        for (auto x : adj[temp2])
        {
            if ((x.second + temp1) < dist[x.first])
            {
                dist[x.first] = temp1 + x.second;
                if (vis[x.first] == 0)
                {
                    insertbinheap(&minheap, mp(dist[x.first], x.first));
                    vis[x.first] = 1;
                }
                else
                {
                    decreasekeybinary(&minheap, positions[x.first], mp(dist[x.first], x.first));
                }
            }
        }

    }
    positions.clear();
    for (ll i = 1; i <= n; i++)
    {
        if (dist[i] > 999999)
        {
            dist[i] = 999999;
        }
    }
}
//BINOMIAL HEAP
struct binomial
{
    pair<ll, ll> val;
    ll degree;
    struct binomial* parent, *child, *sibling;
};
map <ll, struct binomial*> pos2;
struct binomial* root = NULL;

struct binomial* newnode(pair<ll, ll> n) // making new node for binomial
{
    struct binomial* temp = (struct binomial*)malloc(sizeof(struct binomial));
    temp->val.first = n.first;
    temp->val.second = n.second;
    temp->parent = NULL;
    temp->child = NULL;
    temp->sibling = NULL;
    temp->degree = 0;
    pos2[temp->val.second] = temp;
    return temp;
}
void linkbinomial(struct binomial* b1, struct binomial* b2)//linking two heaps
{
    b1->parent = b2;
    b1->sibling = b2->child;
    b2->child = b1;
    b2->degree = b2->degree + 1;
}
struct binomial* mergeheaps(struct binomial* b1, struct binomial* b2)//merging two heaps
{
    if (b1 == NULL)
    {
        return b2;
    }
    if (b2 == NULL)
    {
        return b1;
    }

    struct binomial* temp1 = NULL;
    struct binomial* temp2 = NULL;

    if (b1->degree <= b2->degree)
    {
        temp2 = b1;
        b1 = b1->sibling;
        temp2->sibling = NULL;
    }
    else
    {
        temp2 = b2;
        b2 = b2->sibling;
        temp2->sibling = NULL;
    }

    temp1 = temp2;
    while (b1 != NULL && b2 != NULL)
    {
        if (b1->degree > b2->degree)
        {
            temp2->sibling = b2;
            b2 = b2->sibling;
            temp2 = temp2->sibling;
            temp2->sibling = NULL;
        }
        else
        {
            temp2->sibling = b1;
            b1 = b1->sibling;
            temp2 = temp2->sibling;
            temp2->sibling = NULL;
        }

    }
    while (b1 != NULL)
    {
        temp2->sibling = b1;
        b1 = b1->sibling;
        temp2 = temp2->sibling;
        temp2->sibling = NULL;
    }
    while (b2 != NULL)
    {
        temp2->sibling = b2;
        b2 = b2->sibling;
        temp2 = temp2->sibling;
        temp2->sibling = NULL;
    }
    return temp1;
}
struct binomial* unionheaps(struct binomial* b1, struct binomial* b2) // union of two heaps
{
    if (b1 == NULL && b2 == NULL)
    {
        return NULL;
    }
    struct binomial* temp = mergeheaps(b1, b2);
    if (temp == NULL)
    {
        return temp;
    }

    struct binomial* pre = NULL;
    struct binomial* cur = temp;
    struct binomial* next = cur->sibling;

    while (next != NULL)
    {
        if ((cur->degree != next->degree) || ((next->sibling != NULL) && ((next->sibling)->degree == cur->degree)))
        {
            pre = cur;
            cur = next;
        }
        else
        {
            if (cur->val.first <= next->val.first)
            {
                cur->sibling = next->sibling;
                linkbinomial(next, cur);
            }
            else
            {
                if (pre == NULL)
                    temp = next;
                else
                    pre->sibling = next;
                linkbinomial(cur, next);
                cur = next;
            }
        }
        next = cur->sibling;
    }
    return temp;
}
void insertbinomial(pair<ll, ll> n) // inserting newnode in binomial heap
{
    root = unionheaps(root, newnode(n));
}
struct binomial* findmin(struct binomial* b)// finding minimum node in binomial heap
{
    ll mini = INF;

    struct binomial* temp = NULL;
    struct binomial* cur = b;

    while (cur != NULL)
    {
        if (cur->val.first < mini)
        {
            mini = cur->val.first;
            temp = cur;
        }
        cur = cur->sibling;
    }
    return temp;
}
struct binomial* extractmin(struct binomial* b)//extracting and deleting minimum element in binomial heap
{
    if (b == NULL)
    {
        return NULL;
    }

    struct binomial* pre_min = NULL;
    struct binomial* min = b;
    struct binomial* cur = b;

    struct binomial* k1 = NULL;
    struct binomial* k2 = NULL;
    struct binomial* k3 = NULL;

    ll temp = b->val.first;

    while (cur->sibling != NULL)
    {
        if ((cur->sibling)->val.first < temp)
        {
            temp = (cur->sibling)->val.first;
            pre_min = cur;
            min = cur->sibling;
        }
        cur = cur->sibling;
    }

    if (pre_min == NULL && min->sibling == NULL)
    {
        b = NULL;
    }
    else if (pre_min == NULL)
    {
        b = min->sibling;
    }
    else
    {
        pre_min->sibling = min->sibling;
    }

    if (min->child != NULL)
    {
        k1 = min->child;
        while (k1 != NULL)
        {
            k2 = k1;
            k1 = k1->sibling;
            k2->sibling = k3;
            k3 = k2;
        }
        min->sibling = NULL;
        delete(min);
    }

    return unionheaps(b, k3);
}
void decreasekeybinomial(struct binomial* temp, int n) //Decrease key function in binomial heap
{
    while ((temp->parent != NULL) && (temp->val.first < temp->parent->val.first))
    {
        struct binomial *p1 = temp;
        struct binomial *p2 = temp->parent;

        ll f1 = p1->val.second, f2 = p2->val.second;
        ll s1 = p1->val.first, s2 = p2->val.first;

        pos2[f1] = p2;
        pos2[f2] = p1;
        p1->val.second = f2;
        p1->val.first = s2;
        p2->val.second = f1;
        p2->val.first = s1;
        temp = p2;
    }
}
void binomialdijkstra(ll s, ll n) // DIJKSTRA ALGORITHM WITH BINOMIAL HEAP IMPLEMENTATION
{
    dist[s] = 0;

    ll vis[n + 1];
    for (ll i = 0; i <= n; i++)
    {
        vis[i] = 0;
    }
    insertbinomial(mp(0, s));
    vis[s] = 1;
    while (root != NULL)
    {
        struct binomial* temp = findmin(root);
        pair<ll, ll> ans = temp->val;
        vis[ans.second] = 0;
        root = extractmin(root);

        for (auto x : adj[ans.second])
        {
            if ((ans.first + x.second) < dist[x.first])
            {
                dist[x.first] = (ans.first) + (x.second);
                if (vis[x.first] == 0)
                {
                    insertbinomial(mp(dist[x.first], x.first));
                }
                else
                {
                    decreasekeybinomial(pos2[x.first], dist[x.first]);
                }
            }
        }
    }
    pos2.clear();
}
//FIBONACCI HEAP
struct fibonacci
{
    pair<ll, ll> val;
    ll degree;
    struct fibonacci* parent, *child, *left, *right;
};

struct fibonacci* mini = NULL;
ll totnodes = 0;

void insertfibonacci(pair<int, int> val) // Insertion in fibonacci heaps
{
    struct fibonacci* temp = (struct fibonacci*)malloc(sizeof(struct fibonacci));
    temp->val = val;
    temp->degree = 0;
    temp->left = temp;
    temp->right = temp;
    temp->parent = NULL;
    temp->child = NULL;


    if (mini != NULL)
    {
        (mini->left)->right = temp;
        temp->right = mini;
        temp->left = mini->left;
        mini->left = temp;

        if (temp->val.first < mini->val.first)
        {
            mini = temp;
        }
    }
    else
    {
        mini = temp;
    }
    totnodes++;
}

void linkfibonacci(struct fibonacci* b1, struct fibonacci* b2)//Linking fibonacci heaps
{
    (b2->left)->right = b2->right;
    (b2->right)->left = b2->left;

    if (b1->right == b1)
    {
        mini = b1;
    }
    b2->left = b2;
    b2->right = b2;
    b2->parent = b1;
    if (b1->child == NULL)
    {
        b1->child = b2;
    }
    b2->right = b1->child;
    b2->left = (b1->child)->left;
    (b1->child->left)->right = b2;
    b1->child->left = b2;

    if (b2->val.first < (b1->child)->val.first)
    {
        b1->child = b2;
    }
    b1->degree = b1->degree + 1;
}
void consolidate()//consolidating
{
    ll k1;
    float k2 = (log(totnodes)) / (log(2));

    ll k3 = k2;
    struct fibonacci* ar[k3];

    for (int i = 0; i <= k3; i++)
    {
        ar[i] = NULL;
    }
    struct fibonacci* p1 = mini;
    struct fibonacci* p2, *p3, *p4 = p1;
    do {
        p4 = p4->right;
        k1 = p1->degree;
        while (ar[k1] != NULL)
        {
            p2 = ar[k1];
            if (p1->val.first > p2->val.first)
            {
                p3 = p1;
                p1 = p2;
                p2 = p3;
            }
            if (p2 == mini)
            {
                mini = p1;
            }
            linkfibonacci(p2, p1);
            if (p1->right == p1)
            {
                mini = p1;
            }
            ar[k1] = NULL;
            k1++;
        }
        ar[k1] = p1;
        p1 = p1->right;
    } while (p1 != mini);

    mini = NULL;

    for (int j = 0; j <= k3; j++)
    {
        if (ar[j] != NULL)
        {
            ar[j]->left = ar[j];
            ar[j]->right = ar[j];

            if (mini != NULL)
            {
                mini->left->right = ar[j];
                ar[j]->right = mini;
                ar[j]->left = mini->left;
                mini->left = ar[j];

                if (ar[j]->val.first < mini->val.first)
                {
                    mini = ar[j];
                }
            }
            else
            {
                mini = ar[j];
            }
        }
    }
}
pair<ll, ll> extractminfibonacci() //extracting minimum from fibonacci heap
{
    struct fibonacci* temp = mini;
    pair<ll, ll> ans = mini->val;
    struct fibonacci* ptr;
    ptr = temp;
    struct fibonacci* temp2 = NULL;

    if (temp->child != NULL)
    {
        ptr = temp->child;
        do {
            ptr = temp2->right;
            mini->left->right = temp2;
            temp2->right = mini;
            temp2->left = mini->left;
            mini->left = temp2;

            if (temp2->val.first < mini->val.first)
            {
                mini = temp2;
            }
            temp2->parent = NULL;
            temp2 = ptr;
        } while (ptr != temp->child);
    }
    temp->left->right = temp->right;
    temp->right->left = temp->left;
    mini = temp->right;

    if (temp == temp->right && temp->child == NULL)
    {
        mini = NULL;
    }
    else
    {
        mini = temp->right;
        consolidate();
    }
    totnodes--;
    return ans;

}
void fibonaccidijkstra(int s, int n) // DIJKSTRA IMPLEMENTATION USING FIBONACCI HEAP
{
    dist[s] = 0;
    insertfibonacci(mp(0, s));
    while (mini != NULL)
    {
        pair<ll, ll> ans = extractminfibonacci();
        int temp1 = ans.first;
        int temp2 = ans.second;

        for (auto x : adj[temp2])
        {
            if (x.second + temp1 < dist[x.first])
            {
                dist[x.first] = x.second + temp1;
                insertfibonacci(mp(dist[x.first], x.first));
            }
        }
    }
}
int main(int argc, char*argv[])// Main function
{
    ll t;
    clock_t time;
    cin >> t;
    vector<double> timearray;
    while (t--)
    {
        int ch = -1;
        if (argc != 1)
        {
            ch = atoi(argv[1]);
        }
        time = clock();
        root = NULL;
        mini = NULL;
        ll n, d;
        cin >> n >> d;

        for (ll i = 1; i <= n; i++)
        {
            adj[0].pp(mp(i, 0));
            for (ll j = 1; j <= n; j++)
            {
                ll x;
                cin >> x;
                if (x != 999999 && i != j)
                {
                    adj[i].pp(mp(j, x));
                }
            }
        }

        ll k = bellmanford(0, n + 1);
        adj[0].clear();
        for (ll i = 0; i <= n; i++)
        {
            dist[i] = INF;
        }
        if (k)
        {
            if (argc == 1 || *argv[1] == '4')
            {
                for (ll i = 1; i <= n; i++)
                {
                    fibonaccidijkstra(i, n);
                    for (ll j = 1; j <= n; j++)
                    {
                        if (dist[j] > 999999)
                        {
                            dist[j] = 999999;
                        }
                        cout << dist[j] << " ";
                        dist[j] = INF;
                    }
                    cout << endl;
                }

            }
            else if (ch == 1)
            {

                for (ll i = 1; i <= n; i++)
                {
                    arraydijkstra(i, n);
                    for (ll j = 1; j <= n; j++)
                    {
                        if (dist[j] > 999999)
                        {
                            dist[j] = 999999;
                        }
                        cout << dist[j] << " ";
                        dist[j] = INF;
                    }
                    cout << endl;
                }


            }
            else if (ch == 2)
            {

                for (ll i = 1; i <= n; i++)
                {
                    binheapdijkstra(i, n);
                    for (ll j = 1; j <= n; j++)
                    {
                        if (dist[j] > 999999)
                        {
                            dist[j] = 999999;
                        }
                        cout << dist[j] << " ";
                        dist[j] = INF;
                    }
                    cout << endl;
                }

            }
            else if (ch == 3)
            {

                for (ll i = 1; i <= n; i++)
                {
                    binomialdijkstra(i, n);
                    for (ll j = 1; j <= n; j++)
                    {
                        if (dist[j] > 999999)
                        {
                            dist[j] = 999999;
                        }
                        cout << dist[j] << " ";
                        dist[j] = INF;
                    }
                    cout << endl;
                }

            }

            else
            {
                cout << "ONLY ./a.out 1,2,3,AND 4 WILL GIVE OUTPUTS/n" << endl;
            }
        }
        else
        {
            cout << "-1" << endl;
        }
        for (ll i = 1; i <= n; i++)
        {
            adj[i].clear();
        }
        positions.clear();
        time = clock() - time;
        timearray.pp(((double)time) / CLOCKS_PER_SEC);
    }
    for (ll i = 0; i < timearray.size(); i++)
    {
        cout << timearray[i] << " ";
    }
    cout << endl;
}

